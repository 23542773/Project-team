#include "SimpleStaffWindow.h"
#include "../Plant.h"
#include "../Events.h"
#include "../StaffService.h"
#include "../CustomerService.h"
#include "../Message.h"
#include "../Customer.h"
#include "../Staff.h"
#include "../Restock.h"
#include "../Greenhouse.h"
#include "../Water.h"
#include "../Fertilize.h"
#include "../Spray.h"
#include "../MacroCommand.h"
#include "../Iterator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QTreeView>
#include <QIntValidator>
#include <QScrollBar>
#include <QSet>
#include <QTimer>
#include <QListWidget>
#include <QDateTime>
#include <QComboBox>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>

SimpleStaffWindow::SimpleStaffWindow(NurseryFacade* f, QString uid, QWidget* parent): QMainWindow(parent), facade(f), userId(uid)
{
    setWindowTitle(QString("Staff View - %1").arg(userId));
    
    auto* container = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(container);
    
    auto* topBar = new QHBoxLayout();
    btnLogout = new QPushButton("Logout", this);
    topBar->addStretch();
    topBar->addWidget(btnLogout);
    mainLayout->addLayout(topBar);
    
    connect(btnLogout, &QPushButton::clicked, this, [this]() 
    {
        emit logoutRequested();
        this->close();
    });
    
    tabs = new QTabWidget(this);
    mainLayout->addWidget(tabs);
    
    tabGreenhouse = new QWidget(this);
    auto* root = new QVBoxLayout(tabGreenhouse);
    
    auto* ctrl = new QHBoxLayout();
    btnMorningRoutine = new QPushButton("Morning Routine", this);
    btnNightRoutine = new QPushButton("Night Routine", this);
    btnUrgentCare = new QPushButton("Urgent Care", this);
    btnQueueWater = new QPushButton("Queue Water", this);
    btnQueueFertilize = new QPushButton("Queue Fertilize", this);
    btnQueueSpray = new QPushButton("Queue Insecticide", this);
    btnRunNextCare = new QPushButton("Run Next", this);

    ctrl->addWidget(btnMorningRoutine);
    ctrl->addWidget(btnNightRoutine);
    ctrl->addWidget(btnUrgentCare);
    ctrl->addSpacing(16);
    ctrl->addWidget(btnQueueWater);
    ctrl->addWidget(btnQueueFertilize);
    ctrl->addWidget(btnQueueSpray);
    ctrl->addWidget(btnRunNextCare);
    ctrl->addStretch();

    connect(btnMorningRoutine, &QPushButton::clicked, this, &SimpleStaffWindow::onMorningRoutine);
    connect(btnNightRoutine, &QPushButton::clicked, this, &SimpleStaffWindow::onNightRoutine);
    connect(btnQueueWater, &QPushButton::clicked, this, &SimpleStaffWindow::onQueueWater);
    connect(btnUrgentCare, &QPushButton::clicked, this, &SimpleStaffWindow::onUrgentCare);
    connect(btnQueueFertilize, &QPushButton::clicked, this, &SimpleStaffWindow::onQueueFertilize);
    connect(btnQueueSpray, &QPushButton::clicked, this, &SimpleStaffWindow::onQueueSpray);
    connect(btnRunNextCare, &QPushButton::clicked, this, &SimpleStaffWindow::onRunNextGreenhouse);
    
    root->addLayout(ctrl);
    
    plantTable = new QTableView(this);
    plantModel = new QStandardItemModel(0, 9, this);
    plantModel->setHorizontalHeaderLabels({
        "ID", "Species", "Colour", "State", "Biome",
        "Age (days)", "Water Level", "Insecticide Level", "Health"
    });
    
    plantTable->setModel(plantModel);
    plantTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    plantTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    plantTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    plantTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    
    root->addWidget(plantTable);
    
    tabStock = new QWidget(this);
    auto* stockLayout = new QVBoxLayout(tabStock);
    
    stockModel = new QStandardItemModel(0, 5, this);
    stockModel->setHorizontalHeaderLabels({"Species SKU", "Species", "Biome", "Base Price (R)", "Quantity"});
    
    stockTable = new QTableView(this);
    stockTable->setModel(stockModel);
    stockTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    stockTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    stockTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    stockLayout->addWidget(stockTable);
    
    auto* stockCtrl = new QHBoxLayout();
    txtQty = new QLineEdit(this);
    txtQty->setPlaceholderText("Enter quantity");
    txtQty->setValidator(new QIntValidator(1, 49, this));
    btnRestock = new QPushButton("Restock Selected", this);
    btnUndoRestock = new QPushButton("Undo Last Restock", this);
    stockCtrl->addWidget(new QLabel("Quantity:"));
    stockCtrl->addWidget(txtQty);
    stockCtrl->addWidget(btnRestock);
    stockCtrl->addWidget(btnUndoRestock);
    stockLayout->addLayout(stockCtrl);

    connect(btnRestock, &QPushButton::clicked, this, &SimpleStaffWindow::onRestock);
    connect(btnUndoRestock, &QPushButton::clicked, this, &SimpleStaffWindow::onUndoLastRestock);
    
    tabStaff = new QWidget(this);
    auto* staffLayout = new QVBoxLayout(tabStaff);
    
    staffModel = new QStandardItemModel(0, 4, this);
    staffModel->setHorizontalHeaderLabels({"Staff ID", "Name", "Assigned Orders", "Available"});
    
    staffTable = new QTableView(this);
    staffTable->setModel(staffModel);
    staffTable->horizontalHeader()->setStretchLastSection(true);
    staffTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    staffTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    staffTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    btnRefreshStaff = new QPushButton("Refresh", this);
    staffLayout->addWidget(btnRefreshStaff);
    staffLayout->addWidget(staffTable);

    connect(btnRefreshStaff, &QPushButton::clicked, this, &SimpleStaffWindow::refreshStaff);
    
    tabOrders = new QWidget(this);
    auto* ordersLayout = new QVBoxLayout(tabOrders);
    
    btnCompleteOrder = new QPushButton("Complete Selected Order", this);
    ordersLayout->addWidget(btnCompleteOrder);
    connect(btnCompleteOrder, &QPushButton::clicked, this, &SimpleStaffWindow::onCompleteOrder);
    
    ordersModel = new QStandardItemModel(0, 3, this);
    ordersModel->setHorizontalHeaderLabels({"Order ID", "Status", "Total Cost (R)"});
    ordersTree = new QTreeView(this);
    ordersTree->setModel(ordersModel);
    ordersTree->setHeaderHidden(false);
    ordersTree->setRootIsDecorated(true);
    ordersTree->setSelectionBehavior(QAbstractItemView::SelectRows);
    ordersTree->setSelectionMode(QAbstractItemView::SingleSelection);
    ordersTree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ordersTree->setIndentation(20);
    ordersTree->setAlternatingRowColors(true);
    ordersTree->header()->setStretchLastSection(true);
    ordersLayout->addWidget(new QLabel("My Orders", this));
    ordersLayout->addWidget(ordersTree);
    
    tabMessages = new QWidget(this);
    {
        auto* msgLayout = new QVBoxLayout(tabMessages);
        auto* row = new QHBoxLayout();
        row->addWidget(new QLabel("To:", this));
        cmbRecipient = new QComboBox(this);
        row->addWidget(cmbRecipient, 1);
        msgLayout->addLayout(row);
        messagesList = new QListWidget(this);
        messagesList->setAlternatingRowColors(true);
        msgLayout->addWidget(messagesList, 1);
        auto* msgBottom = new QHBoxLayout();
        messageInput = new QLineEdit(this);
        messageInput->setPlaceholderText("Type a message...");
        btnSendMessage = new QPushButton("Send", this);
        msgBottom->addWidget(messageInput, 1);
        msgBottom->addWidget(btnSendMessage);
        msgLayout->addLayout(msgBottom);
    }
    
    refreshRecipients();

    connect(cmbRecipient, &QComboBox::currentTextChanged, this, [this](const QString&)
    {
        QString peerId = cmbRecipient->currentData().toString();
        if (!peerId.isEmpty()) loadConversation(peerId);
    });

    connect(btnSendMessage, &QPushButton::clicked, this, [this]() 
    {
        const QString text = messageInput->text().trimmed();
        const QString peerId = cmbRecipient->currentData().toString();
        if (text.isEmpty() || peerId.isEmpty()) return;
        
        Staff* staff = facade->getStaff(userId.toStdString());
        if (staff) 
        {
            Colleague* recipient = facade->getStaff(peerId.toStdString());
            if (!recipient) 
            {
                recipient = facade->getCustomer(peerId.toStdString());
            }
            
            if (recipient) 
            {
                staff->sendMessage(recipient, text.toStdString());
            }
        }
        
        messageInput->clear();
        loadConversation(peerId);
    });

    tabCommandLog = new QWidget(this);
    {
        auto* logLayout = new QVBoxLayout(tabCommandLog);
        
        btnRefreshLog = new QPushButton("Refresh Log", this);
        logLayout->addWidget(btnRefreshLog);
        
        txtCommandLog = new QTextEdit(this);
        txtCommandLog->setReadOnly(true);
        txtCommandLog->setFont(QFont("Courier", 9));
        logLayout->addWidget(txtCommandLog);
        
        connect(btnRefreshLog, &QPushButton::clicked, this, &SimpleStaffWindow::refreshCommandLog);
    }

    tabs->addTab(tabGreenhouse, tr("Greenhouse"));
    tabs->addTab(tabStock, tr("Stock"));
    tabs->addTab(tabStaff, tr("Staff"));
    tabs->addTab(tabOrders, tr("My Orders"));
    tabs->addTab(tabMessages, tr("Messages"));
    tabs->addTab(tabCommandLog, tr("Command Log"));
    
    Staff* currentStaff = facade->getStaff(userId.toStdString());
    if (currentStaff) 
    {
        StaffRole role = currentStaff->getRole();
        
        if (role == StaffRole::PlantCare) 
        {
            tabs->removeTab(tabs->indexOf(tabStock));
            tabs->removeTab(tabs->indexOf(tabStaff));
            tabs->removeTab(tabs->indexOf(tabOrders));
        } 

        else if (role == StaffRole::Inventory) 
        {
            tabs->removeTab(tabs->indexOf(tabGreenhouse));
            tabs->removeTab(tabs->indexOf(tabStaff));
            tabs->removeTab(tabs->indexOf(tabOrders));
        } 
        
        else if (role == StaffRole::Sales) 
        {
            tabs->removeTab(tabs->indexOf(tabGreenhouse));
            tabs->removeTab(tabs->indexOf(tabStock));
        }
    }
    
    setCentralWidget(container);
    auto* greenhouseRefreshTimer = new QTimer(this);
    greenhouseRefreshTimer->setInterval(2000);
    connect(greenhouseRefreshTimer, &QTimer::timeout, this, &SimpleStaffWindow::refreshGreenhouse);
    greenhouseRefreshTimer->start();
    
    refreshGreenhouse();
    refreshStock();
    refreshStaff();
    refreshMyOrders();

    if (cmbRecipient && cmbRecipient->count() > 0) 
    {
        QString peerId = cmbRecipient->currentData().toString();
        if (!peerId.isEmpty()) loadConversation(peerId);
    }
}

void SimpleStaffWindow::refreshRecipients()
{
    if (!facade || !cmbRecipient) return;
    cmbRecipient->clear();
    
    Staff* currentStaff = facade->getStaff(userId.toStdString());
    if (!currentStaff) return;
    
    StaffRole myRole = currentStaff->getRole();
    
    auto staffList = facade->listAllStaff();
    for (const auto& s : staffList) 
    {
        if (s.getId() == userId.toStdString()) continue; 
        
        Staff* otherStaff = facade->getStaff(s.getId());
        if (!otherStaff) continue;
        
        StaffRole otherRole = otherStaff->getRole();
        
        if (myRole == StaffRole::Sales) 
        {
            if (otherRole == StaffRole::Sales || otherRole == StaffRole::Inventory) 
            {
                QString display = QString::fromStdString("Staff ") + QString::fromStdString(s.getId() + " - " + s.name);
                cmbRecipient->addItem(display, QString::fromStdString(s.getId()));
            }
        }

        else if (myRole == StaffRole::PlantCare) 
        {
            if (otherRole == StaffRole::PlantCare || otherRole == StaffRole::Inventory) 
            {
                QString display = QString::fromStdString("Staff ") + QString::fromStdString(s.getId() + " - " + s.name);
                cmbRecipient->addItem(display, QString::fromStdString(s.getId()));
            }
        }

        else if (myRole == StaffRole::Inventory) 
        {
            if (otherRole == StaffRole::Inventory || otherRole == StaffRole::PlantCare || otherRole == StaffRole::Sales) 
            {
                QString display = QString::fromStdString("Staff ") + QString::fromStdString(s.getId() + " - " + s.name);
                cmbRecipient->addItem(display, QString::fromStdString(s.getId()));
            }
        }
    }
    
    if (myRole == StaffRole::Sales) 
    {
        auto customers = facade->listAllCustomers();
        for (const auto& c : customers) 
        {
            QString display = QString::fromStdString("Customer ") + QString::fromStdString(c.getId() + " - " + c.name);
            cmbRecipient->addItem(display, QString::fromStdString(c.getId()));
        }
    }
}

void SimpleStaffWindow::loadConversation(const QString& peerId)
{
    if (!facade) return;
    messagesList->clear();
    auto conv = facade->getConversation(userId.toStdString(), peerId.toStdString());

    for (const auto& m : conv) 
    {
        QString ts = QDateTime::fromSecsSinceEpoch(m.timestamp).toString("[hh:mm:ss] ");
        QString who = (QString::fromStdString(m.fromUser) == userId) ? "You" : QString::fromStdString(m.fromUser);
        messagesList->addItem(ts + who + ": " + QString::fromStdString(m.text));
    }
}

void SimpleStaffWindow::refreshGreenhouse()
{
    if (!facade) return;
    
    QSet<QString> selectedIds;
    if (plantTable->selectionModel()) 
    {
        QModelIndexList sel = plantTable->selectionModel()->selectedRows();
        for (const auto& idx : sel) 
        {
            QString id = plantModel->item(idx.row(), 0)->text();
            selectedIds.insert(id);
        }
    }
    int scrollPos = plantTable->verticalScrollBar() ? plantTable->verticalScrollBar()->value() : 0;
    
    plantModel->removeRows(0, plantModel->rowCount());

    auto allPlants = facade->listAllPlants();
    for (auto* p : allPlants) 
    {
        if (!p) continue;
        QString id      = QString::fromStdString(p->id());
        QString species = QString::fromStdString(p->getSpeciesFly()->getName());
        QString colour  = QString::fromStdString(p->getColour());
        QString state   = QString::fromStdString(p->getPlantState()->name());
        QString biome   = QString::fromStdString(p->getSpeciesFly()->getBiome());
        QString age     = QString::number(p->getAgeDays());
        QString water   = QString::number(p->getMoisture());
        QString insect  = QString::number(p->getInsecticide());
        QString health  = QString::number(p->getHealth());

        QList<QStandardItem*> row;
        row << new QStandardItem(id)
            << new QStandardItem(species)
            << new QStandardItem(colour)
            << new QStandardItem(state)
            << new QStandardItem(biome)
            << new QStandardItem(age)
            << new QStandardItem(water)
            << new QStandardItem(insect)
            << new QStandardItem(health);
        plantModel->appendRow(row);
    }
    
    if (!selectedIds.isEmpty() && plantTable->selectionModel()) 
    {
        QItemSelection selection;
        for (int row = 0; row < plantModel->rowCount(); ++row) 
        {
            QString id = plantModel->item(row, 0)->text();
            if (selectedIds.contains(id)) 
            {
                QModelIndex idx = plantModel->index(row, 0);
                selection.select(idx, plantModel->index(row, plantModel->columnCount() - 1));
            }
        }
        plantTable->selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    }
    
    if (plantTable->verticalScrollBar()) 
    {
        plantTable->verticalScrollBar()->setValue(scrollPos);
    }
}

void SimpleStaffWindow::refreshStock()
{
    if (!facade) return;
    stockModel->removeRows(0, stockModel->rowCount());
    
    auto speciesList = facade->listAllSpecies();
    for (const auto& fw : speciesList) 
    {
        QString sku = QString::fromStdString(fw->getSku());
        int qty = facade->getSpeciesQuantity(fw->getSku());
        
        QList<QStandardItem*> row;
        row << new QStandardItem(sku)
            << new QStandardItem(QString::fromStdString(fw->getName()))
            << new QStandardItem(QString::fromStdString(fw->getBiome()))
            << new QStandardItem(QString::number(fw->getCost(), 'f', 2))
            << new QStandardItem(QString::number(qty));
        stockModel->appendRow(row);
    }
}

void SimpleStaffWindow::refreshStaff()
{
    if (!facade) return;
    staffModel->removeRows(0, staffModel->rowCount());
    
    auto staffList = facade->listAllStaff();
    for (const auto& s : staffList) 
    {
        QString id = QString::fromStdString(s.getId());
        QString name = QString::fromStdString(s.name);
        
        QStringList ordersList;
        for (const auto& order : s.assignedOrders)
            ordersList << QString::fromStdString(order);
        QString orders = ordersList.join(", ");
        
        QString available = s.available ? "Yes" : "No";
        
        QList<QStandardItem*> row;
        row << new QStandardItem(id)
            << new QStandardItem(name)
            << new QStandardItem(orders.trimmed())
            << new QStandardItem(available);
        staffModel->appendRow(row);
    }
}

void SimpleStaffWindow::refreshMyOrders()
{
    if (!facade || !ordersModel) return;
    ordersModel->removeRows(0, ordersModel->rowCount());
    
    auto orders = facade->getStaffOrders(userId.toStdString());
    for (const auto& o : orders) 
    {
        QString statusStr;
        switch (o.status) 
        {
            case events::OrderStatus::New:         statusStr = "New"; break;
            case events::OrderStatus::Assigned:    statusStr = "Assigned"; break;
            case events::OrderStatus::InProgress:  statusStr = "In Progress"; break;
            case events::OrderStatus::Completed:   statusStr = "Completed"; break;
            case events::OrderStatus::Cancelled:   statusStr = "Cancelled"; break;
        }
        
        double total = 0;
        for (const auto& l : o.lines) total += l.finalCost;
        
        QList<QStandardItem*> orderRow;
        orderRow << new QStandardItem(QString::fromStdString(o.orderId))
                 << new QStandardItem(statusStr)
                 << new QStandardItem(QString::number(total, 'f', 2));
        
        auto* parentItem = orderRow[0];
        ordersModel->appendRow(orderRow);
        
        for (const auto& l : o.lines)
        {
            QString desc = QString::fromStdString(l.description);
            QString cost = QString("R%1").arg(l.finalCost, 0, 'f', 2);
            QString plantId = QString::fromStdString(l.plantId);
            
            QList<QStandardItem*> subRow;
            subRow << new QStandardItem(" • " + plantId + " — " + desc)
                   << new QStandardItem("")
                   << new QStandardItem(cost);
            
            parentItem->appendRow(subRow);
        }
    }
    if (ordersTree) ordersTree->expandAll();
}

void SimpleStaffWindow::onMorningRoutine()
{
    QModelIndexList sel = plantTable->selectionModel()->selectedRows();
    if (sel.isEmpty())
    {
        QMessageBox::information(this, "No Selection", "Please select plants for the morning routine.");
        return;
    }

    std::vector<Plant*> plants;
    for (const auto& idx : sel)
    {
        QString id = plantModel->item(idx.row(), 0)->text();
        Plant* p = facade->getPlant(id.toStdString());
        if (p) plants.push_back(p);
    }

    facade->runMorningRoutine(plants);
    refreshGreenhouse();
    QMessageBox::information(this, "Morning Routine", QString("Applied morning routine to %1 plant(s).").arg(plants.size()));
}

void SimpleStaffWindow::onNightRoutine()
{
    QModelIndexList sel = plantTable->selectionModel()->selectedRows();
    if (sel.isEmpty())
    {
        QMessageBox::information(this, "No Selection", "Please select plants for the night routine.");
        return;
    }

    std::vector<Plant*> plants;
    for (const auto& idx : sel)
    {
        QString id = plantModel->item(idx.row(), 0)->text();
        Plant* p = facade->getPlant(id.toStdString());
        if (p) plants.push_back(p);
    }

    facade->runNightRoutine(plants);
    refreshGreenhouse();
    QMessageBox::information(this, "Night Routine", QString("Applied night routine to %1 plant(s).").arg(plants.size()));
}

void SimpleStaffWindow::onQueueWater()
{
    QModelIndexList sel = plantTable->selectionModel()->selectedRows();
    if (sel.isEmpty()) 
    {
        QMessageBox::information(this, "No Selection", "Please select plants to water.");
        return;
    }

    std::vector<Plant*> plants;
    for (const auto& idx : sel) 
    {
        QString id = plantModel->item(idx.row(), 0)->text();
        Plant* p = facade->getPlant(id.toStdString());
        if (p) plants.push_back(p);
    }

    facade->enqueueWater(plants, userId.toStdString());

    refreshCommandLog();
    QMessageBox::information(this, "Queued", QString("Queued water for %1 plant(s). Queue size: %2").arg(plants.size()).arg(facade->getQueueSize()));
}

void SimpleStaffWindow::onUrgentCare()
{
    if (!facade) return;
    
    facade->runUrgentCare();
    
    refreshGreenhouse();
    refreshCommandLog();
    QMessageBox::information(this, "Urgent Care", "Urgent care routine applied to wilting plants.");
}

void SimpleStaffWindow::onQueueFertilize()
{
    QModelIndexList sel = plantTable->selectionModel()->selectedRows();
    if (sel.isEmpty()) 
    {
        QMessageBox::information(this, "No Selection", "Please select plants to fertilize.");
        return;
    }

    std::vector<Plant*> plants;
    for (const auto& idx : sel) 
    {
        QString id = plantModel->item(idx.row(), 0)->text();
        Plant* p = facade->getPlant(id.toStdString());
        if (p) plants.push_back(p);
    }

    facade->enqueueFertilize(plants, userId.toStdString());

    refreshCommandLog();
    QMessageBox::information(this, "Queued", QString("Queued fertilize for %1 plant(s). Queue size: %2").arg(plants.size()).arg(facade->getQueueSize()));
}

void SimpleStaffWindow::onQueueSpray()
{
    QModelIndexList sel = plantTable->selectionModel()->selectedRows();
    if (sel.isEmpty()) 
    {
        QMessageBox::information(this, "No Selection", "Please select plants to apply insecticide.");
        return;
    }

    std::vector<Plant*> plants;
    for (const auto& idx : sel) 
    {
        QString id = plantModel->item(idx.row(), 0)->text();
        Plant* p = facade->getPlant(id.toStdString());
        if (p) plants.push_back(p);
    }

    facade->enqueueSpray(plants, userId.toStdString());

    refreshCommandLog();
    QMessageBox::information(this, "Queued", QString("Queued insecticide for %1 plant(s). Queue size: %2").arg(plants.size()).arg(facade->getQueueSize()));
}

void SimpleStaffWindow::onRunNextGreenhouse()
{
    if (facade->getQueueSize() == 0) 
    {
        QMessageBox::information(this, "Queue Empty", "No commands in queue to process.");
        return;
    }

    bool ok = facade->processNextCommand();
    refreshGreenhouse();
    refreshCommandLog();
    if (!ok) 
    {
        QMessageBox::warning(this, "Execution Failed", "The next command failed to execute.");
    }
}

void SimpleStaffWindow::onRestock()
{
    QModelIndexList sel = stockTable->selectionModel()->selectedRows();
    if (sel.isEmpty()) 
    {
        QMessageBox::information(this, "No Selection", "Please select a species to restock.");
        return;
    }
    
    QString sku = stockModel->item(sel.first().row(), 0)->text();
    bool ok = false;
    int qty = txtQty->text().toInt(&ok);
    if (!ok || qty <= 0 || qty >= 50) 
    {
        QMessageBox::warning(this, "Invalid Quantity", "Please enter a quantity between 1 and 49.");
        return;
    }
    
    facade->enqueueRestock(sku.toStdString(), qty, userId.toStdString());
    
    if (facade->processNextCommand()) 
    {
        refreshGreenhouse();
        refreshStock();
        QMessageBox::information(this, "Success", 
            QString("Restocked %1 units of %2.\nQueue size: %3 | Undo history: %4")
            .arg(qty).arg(sku)
            .arg(facade->getQueueSize())
            .arg(facade->getRestockHistorySize()));
    } 
    else 
    {
        QMessageBox::warning(this, "Error", "Failed to execute restock command.");
    }
    
    txtQty->clear();
    refreshCommandLog();
}

void SimpleStaffWindow::onUndoLastRestock()
{
    if (facade->getRestockHistorySize() == 0) 
    {
        QMessageBox::information(this, "Nothing to Undo", "No restock operations to undo.");
        return;
    }
    
    auto reply = QMessageBox::question(this, "Undo Restock", "Are you sure you want to undo the last restock operation?",
    QMessageBox::Yes | QMessageBox::No);
    
    if (reply != QMessageBox::Yes) return;
    
    if (facade->undoLastRestock()) 
    {
        refreshGreenhouse();
        refreshStock();
        refreshCommandLog();
        QMessageBox::information(this, "Success", "Last restock operation has been undone.");
    } 
    else 
    {
        QMessageBox::warning(this, "Error", "Failed to undo restock operation.");
    }
}

void SimpleStaffWindow::onCompleteOrder()
{
    if (!ordersTree->selectionModel() || ordersTree->selectionModel()->selectedRows().isEmpty()) 
    {
        QMessageBox::information(this, "No Selection", "Please select an order to complete.");
        return;
    }
    
    QModelIndex selectedIdx = ordersTree->selectionModel()->selectedRows().first();
    
    if (selectedIdx.parent().isValid()) 
    {
        selectedIdx = selectedIdx.parent();
    }
    
    QString orderId = ordersModel->item(selectedIdx.row(), 0)->text();
    QString status = ordersModel->item(selectedIdx.row(), 1)->text();
    
    if (status == "Completed") 
    {
        QMessageBox::information(this, "Already Completed", "This order is already marked as completed.");
        return;
    }
    
    auto reply = QMessageBox::question(this, "Complete Order", 
        QString("Are you sure you want to mark order %1 as completed?").arg(orderId),
        QMessageBox::Yes | QMessageBox::No);
    
    if (reply != QMessageBox::Yes) 
    {
        return;
    }
    
    bool success = facade->completeOrder(orderId.toStdString());
    
    if (success) 
    {
        QMessageBox::information(this, "Success", QString("Order %1 has been completed!").arg(orderId));
        refreshMyOrders();
        refreshStaff();
    } 
    else
    {
        QMessageBox::warning(this, "Error", "Failed to complete the order. Please try again.");
    }
}

void SimpleStaffWindow::refreshCommandLog()
{
    if (!txtCommandLog) return;
    
    QFile logFile("../../src/commands.log");
    if (!logFile.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        txtCommandLog->setText("Command log file not found or cannot be opened.");
        return;
    }
    
    QTextStream in(&logFile);
    QString logContent = in.readAll();
    logFile.close();
    
    QStringList lines = logContent.split('\n', Qt::SkipEmptyParts);
    std::reverse(lines.begin(), lines.end());
    
    txtCommandLog->setText(lines.join('\n'));

    txtCommandLog->moveCursor(QTextCursor::Start);
}

