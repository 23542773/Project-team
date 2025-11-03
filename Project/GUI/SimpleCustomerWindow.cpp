#include "SimpleCustomerWindow.h"
#include "../Plant.h"
#include "../PlantFlyweight.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QHeaderView>
#include <QDateTime>
#include <QMessageBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QTabWidget>
#include <QTreeView>
#include <QStringList>
#include <QTimer>
#include <QScrollBar>
#include <QSet>
#include <QListWidget>
#include <QComboBox>
#include <random>
#include <algorithm>

#include "../Events.h"
#include "../CustomerService.h"
#include "../StaffService.h"
#include "../Message.h"
#include "../Customer.h"
#include "../Staff.h"

#include "../SaleItem.h"
#include "../PlantItem.h"
#include "../ReinforcedPot.h"
#include "../GiftWrap.h"
#include "../MessageCard.h"

SimpleCustomerWindow::SimpleCustomerWindow(NurseryFacade* f, QString uid, QWidget* parent, CustomerDash* dash)  : QMainWindow(parent), facade(f), userId(uid), customerDash(dash)
{
    setWindowTitle(QString("Customer View - %1").arg(userId));
    
    tabs = new QTabWidget(this);

    tabCatalog = new QWidget(this);
    auto* root = new QVBoxLayout(tabCatalog);
    
    auto* top = new QHBoxLayout();
    searchBox = new QLineEdit(this);
    searchBox->setPlaceholderText("Search plants...");
    searchBox->setClearButtonEnabled(true);
    connect(searchBox, &QLineEdit::textChanged, this, [this](const QString& text){
        this->filterCatalog(text);
    });
    
    btnStartOrder = new QPushButton("Checkout", this);
    btnAddToCart = new QPushButton("Add To Cart", this);
    btnCustomize = new QPushButton("Customize", this);
    btnRemoveFromCart = new QPushButton("Remove Selected", this);
    btnLogout = new QPushButton("Logout", this);
    
    top->addWidget(searchBox, 1);
    top->addStretch();
    top->addWidget(btnStartOrder);
    top->addWidget(btnAddToCart);
    top->addWidget(btnCustomize);
    top->addWidget(btnRemoveFromCart);
    top->addWidget(btnLogout);
    
    connect(btnLogout, &QPushButton::clicked, this, [this]() 
    {
        emit logoutRequested();
        this->close();
    });
    
    auto* split = new QSplitter(Qt::Horizontal, this);
    
    auto* left = new QWidget(this);
    auto* leftL = new QVBoxLayout(left);
    tblCatalog = new QTableView(this);
    mCatalog = new QStandardItemModel(0, 6, this);
    mCatalog->setHorizontalHeaderLabels({"Plant ID", "Species SKU", "Colour", "Name", "Biome", "Price"});
    tblCatalog->setModel(mCatalog);
    tblCatalog->horizontalHeader()->setStretchLastSection(true);
    tblCatalog->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblCatalog->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tblCatalog->setEditTriggers(QAbstractItemView::NoEditTriggers);
    leftL->addWidget(new QLabel("Catalogue (Available Plants)", this));
    leftL->addWidget(tblCatalog);
    
    auto* right = new QWidget(this);
    auto* rightL = new QVBoxLayout(right);
    lblOrderId = new QLabel("Cart", this);
    tblCart = new QTableView(this);
    mCart = new QStandardItemModel(0, 3, this);
    mCart->setHorizontalHeaderLabels({"Item", "Biome", "Price"});
    tblCart->setModel(mCart);
    tblCart->horizontalHeader()->setStretchLastSection(true);
    tblCart->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblCart->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tblCart->setEditTriggers(QAbstractItemView::NoEditTriggers);
    lblTotals = new QLabel("Subtotal: R0.00", this);
    rightL->addWidget(lblOrderId);
    rightL->addWidget(tblCart);
    rightL->addWidget(lblTotals);
    
    split->addWidget(left);
    split->addWidget(right);
    split->setStretchFactor(0, 3);
    split->setStretchFactor(1, 2);
    
    root->addLayout(top);
    root->addWidget(split);
    
    tabOrders = new QWidget(this);
    auto* ordersLayout = new QVBoxLayout(tabOrders);
    
    QPushButton* btnViewReceipts = new QPushButton("View My Receipts", this);
    ordersLayout->addWidget(btnViewReceipts);
    
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
    
    connect(btnViewReceipts, &QPushButton::clicked, this, [this]() 
    {
        if (!facade) return;
        
        auto receipts = facade->getCustomerReceipts(userId.toStdString());
        
        if (receipts.empty()) 
        {
            QMessageBox::information(this, "No Receipts", "You have no receipts yet. Place an order to get started!");
            return;
        }
        
        QDialog receiptsDialog(this);
        receiptsDialog.setWindowTitle("My Receipts");
        receiptsDialog.resize(500, 400);
        QVBoxLayout* layout = new QVBoxLayout(&receiptsDialog);
        
        QListWidget* receiptsList = new QListWidget(&receiptsDialog);
        receiptsList->setAlternatingRowColors(true);
        
        for (const auto& receipt : receipts) 
        {
            QString receiptText = QString("Order: %1 | Total: R%2 | Paid: R%3 | Change: R%4")
            .arg(QString::fromStdString(receipt.orderId))
            .arg(receipt.totalCost, 0, 'f', 2)
            .arg(receipt.amountPaid, 0, 'f', 2)
            .arg(receipt.change, 0, 'f', 2);
            
            receiptsList->addItem(receiptText);
        }
        
        layout->addWidget(new QLabel("Your Payment Receipts:", &receiptsDialog));
        layout->addWidget(receiptsList);
        
        QPushButton* closeBtn = new QPushButton("Close", &receiptsDialog);
        connect(closeBtn, &QPushButton::clicked, &receiptsDialog, &QDialog::accept);
        layout->addWidget(closeBtn);
        
        receiptsDialog.exec();
    });

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
            
            Customer* customer = facade->getCustomer(userId.toStdString());
            if (customer) 
            {
                customer->sendMessage(peerId.toStdString(), text.toStdString());
            }
            
            messageInput->clear();
            loadConversation(peerId);
        });
    }
    
    {
        tabRecommendations = new QWidget(this);
        auto* layout = new QVBoxLayout(tabRecommendations);
        
        auto* buttonRow = new QHBoxLayout();
        
        QPushButton* btnForYou = new QPushButton("For You", this);
        btnForYou->setToolTip("Get personalized recommendations based on your purchase history");
        connect(btnForYou, &QPushButton::clicked, this, &SimpleCustomerWindow::showPersonalizedRecommendations);
        buttonRow->addWidget(btnForYou);
        
        buttonRow->addStretch();
        layout->addLayout(buttonRow);
        
        tblRecommendations = new QTableView(this);
        mRecommendations = new QStandardItemModel(0, 7, this);
        mRecommendations->setHorizontalHeaderLabels({"Plant ID", "Species SKU", "Colour", "Name", "Biome", "Season", "Price"});
        tblRecommendations->setModel(mRecommendations);
        tblRecommendations->horizontalHeader()->setStretchLastSection(true);
        tblRecommendations->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblRecommendations->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tblRecommendations->setEditTriggers(QAbstractItemView::NoEditTriggers);
        layout->addWidget(tblRecommendations);
    }

    {
        tabEncyclopedia = new QWidget(this);
        auto* layout = new QVBoxLayout(tabEncyclopedia);
        layout->addWidget(new QLabel("Plant Encyclopedia (Species Info)", this));

        tblEncyclopedia = new QTableView(this);
        mEncyclopedia = new QStandardItemModel(0, 7, this);
        mEncyclopedia->setHorizontalHeaderLabels({
            "Species Name", "Biome", "Season", "Water Sensitivity",
            "Insecticide Tolerance", "Growth Rate", "Price"
        });
        tblEncyclopedia->setModel(mEncyclopedia);
        tblEncyclopedia->horizontalHeader()->setStretchLastSection(true);
        tblEncyclopedia->setSelectionBehavior(QAbstractItemView::SelectRows);
        tblEncyclopedia->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tblEncyclopedia->setEditTriggers(QAbstractItemView::NoEditTriggers);
        layout->addWidget(tblEncyclopedia);
    }
    
    tabs->addTab(tabCatalog, tr("Catalog"));
    tabs->addTab(tabRecommendations, tr("Recommendations"));
    tabs->addTab(tabEncyclopedia, tr("Encyclopedia"));
    tabs->addTab(tabOrders, tr("My Orders"));
    tabs->addTab(tabMessages, tr("Messages"));

    tabAlerts = new QWidget(this);
    {
        auto* alertsLayout = new QVBoxLayout(tabAlerts);
        alertsList = new QListWidget(this);
        alertsList->setAlternatingRowColors(true);
        alertsLayout->addWidget(new QLabel("Newly Matured Plants", this));
        alertsLayout->addWidget(alertsList, 1);
    }
    tabs->addTab(tabAlerts, tr("Alerts"));
    setCentralWidget(tabs);

    auto* catalogRefreshTimer = new QTimer(this);
    catalogRefreshTimer->setInterval(3000);
    connect(catalogRefreshTimer, &QTimer::timeout, this, &SimpleCustomerWindow::populateCatalog);
    catalogRefreshTimer->start();
    
    populateCatalog();
    filterCatalog(searchBox->text());
    
    auto* alertsTimer = new QTimer(this);
    alertsTimer->setInterval(3000);
    connect(alertsTimer, &QTimer::timeout, this, &SimpleCustomerWindow::refreshAlerts);
    alertsTimer->start();
    
    showPersonalizedRecommendations();

    populateEncyclopedia();
    
    refreshMyOrders();
    
    
    if (cmbRecipient && cmbRecipient->count() > 0) 
    {
        QString peerId = cmbRecipient->currentData().toString();
        if (!peerId.isEmpty()) loadConversation(peerId);
    }

    connect(btnAddToCart, &QPushButton::clicked, this, [this]() 
    {
        if (!tblCatalog->selectionModel() || tblCatalog->selectionModel()->selectedRows().isEmpty()) 
        {
            QMessageBox::information(this, "No Selection", "Please select plant(s) from the catalog first.");
            return;
        }
        
        QModelIndexList selectedRows = tblCatalog->selectionModel()->selectedRows();
        int added = 0;
        int skipped = 0;
        
        for (const auto& index : selectedRows) 
        {
            const int row = index.row();
            QString plantId = mCatalog->item(row, 0)->text();
            QString sku     = mCatalog->item(row, 1)->text();
            QString species = mCatalog->item(row, 3)->text();
            QString biome   = mCatalog->item(row, 4)->text();
            double price = mCatalog->item(row, 5)->data(Qt::UserRole + 1).toDouble();

            if (findCartRow(plantId) >= 0) 
            {
                skipped++;
                continue;
            }

            QList<QStandardItem*> rowItems;
            auto itemSpecies = new QStandardItem(species);
            itemSpecies->setData(plantId, Qt::UserRole);
            itemSpecies->setData(sku, Qt::UserRole + 2);

            auto itemPrice = new QStandardItem(QString::number(price, 'f', 2));
            itemPrice->setData(price, Qt::UserRole + 1);

            rowItems << itemSpecies
                     << new QStandardItem(biome)
                     << itemPrice;

            mCart->appendRow(rowItems);
            added++;
        }
        
        recalcTotal();
        
        if (added > 0 && skipped > 0) 
        {
            QMessageBox::information(this, "Items Added", 
            QString("Added %1 item(s) to cart. %2 item(s) already in cart were skipped.").arg(added).arg(skipped));
        } 

        else if (added > 0) 
        {
            QMessageBox::information(this, "Items Added", QString("Added %1 item(s) to cart.").arg(added));
        } 

        else if (skipped > 0) 
        {
            QMessageBox::information(this, "Duplicate", "All selected items are already in your cart.");
        }
    });

    connect(btnRemoveFromCart, &QPushButton::clicked, this, [this]()
    {
        if (!tblCart->selectionModel()) return;
        auto sel = tblCart->selectionModel()->selectedRows();

        if (sel.isEmpty()) 
        {
            QMessageBox::information(this, "No Selection", "Select an item in the cart to remove.");
            return;
        }

        std::sort(sel.begin(), sel.end(), [](auto a, auto b){ return a.row() > b.row(); });
        for (const auto& idx : sel)
            mCart->removeRow(idx.row());
        recalcTotal();
    });

    connect(btnStartOrder, &QPushButton::clicked, this, [this]() 
    {
        if (!facade) 
        {
            QMessageBox::warning(this, "Error", "No facade connected.");
            return;
        }

        if (mCart->rowCount() == 0) 
        {
            QMessageBox::warning(this, "Empty Cart", "Please add some plants to your cart before checkout.");
            return;
        }

        double total = 0.0;
        for (int r = 0; r < mCart->rowCount(); ++r) 
        {
            total += mCart->item(r, 2)->data(Qt::UserRole + 1).toDouble();
        }

        QDialog paymentDialog(this);
        paymentDialog.setWindowTitle("Payment");
        QVBoxLayout* layout = new QVBoxLayout(&paymentDialog);
        
        QLabel* lblTotal = new QLabel(QString("Total Amount: R%1").arg(total, 0, 'f', 2), &paymentDialog);
        QFont boldFont = lblTotal->font();
        boldFont.setBold(true);
        boldFont.setPointSize(boldFont.pointSize() + 2);
        lblTotal->setFont(boldFont);
        layout->addWidget(lblTotal);
        
        layout->addWidget(new QLabel("Enter payment amount:", &paymentDialog));
        QLineEdit* paymentInput = new QLineEdit(&paymentDialog);
        paymentInput->setPlaceholderText("0.00");
        layout->addWidget(paymentInput);
        
        QDialogButtonBox* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &paymentDialog);
        layout->addWidget(buttons);
        
        connect(buttons, &QDialogButtonBox::accepted, &paymentDialog, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, &paymentDialog, &QDialog::reject);
        
        if (paymentDialog.exec() != QDialog::Accepted) return;
        
        bool ok;
        double payment = paymentInput->text().toDouble(&ok);
        if (!ok || payment < 0) 
        {
            QMessageBox::warning(this, "Invalid Amount", "Please enter a valid payment amount.");
            return;
        }
        
        std::vector<events::OrderLine> lines;
        lines.reserve(mCart->rowCount());
        for (int r = 0; r < mCart->rowCount(); ++r) 
        {
            events::OrderLine line;
            line.plantId     = mCart->item(r, 0)->data(Qt::UserRole).toString().toStdString();
            line.speciesSku  = mCart->item(r, 0)->data(Qt::UserRole + 2).toString().toStdString();
            line.description = mCart->item(r, 0)->text().toStdString();
            line.finalCost   = mCart->item(r, 2)->data(Qt::UserRole + 1).toDouble();
            lines.push_back(std::move(line));
        }
        
        auto receipt = facade->checkout(userId.toStdString(), lines, payment);
        
        if (receipt.success) 
        {
            QString receiptText = QString(
                "✓ Payment Successful!\n\n"
                "Order ID: %1\n"
                "Total: R%2\n"
                "Paid: R%3\n"
                "Change: R%4\n\n"
                "%5"
            ).arg(QString::fromStdString(receipt.orderId))
             .arg(receipt.totalCost, 0, 'f', 2)
             .arg(receipt.amountPaid, 0, 'f', 2)
             .arg(receipt.change, 0, 'f', 2)
             .arg(QString::fromStdString(receipt.message));
            
            QMessageBox::information(this, "Receipt", receiptText);
            
            mCart->removeRows(0, mCart->rowCount());
            recalcTotal();
            
            populateCatalog();
            refreshMyOrders();
        } 
        else 
        {
            QMessageBox::critical(this, "Payment Failed", QString::fromStdString(receipt.message));
        }
    });

    connect(btnCustomize, &QPushButton::clicked, this, [this]() 
    {
        if (!facade) 
        {
            QMessageBox::warning(this, "Error", "No facade connected.");
            return;
        }

        if (!tblCart->selectionModel() || tblCart->selectionModel()->selectedRows().isEmpty()) 
        {
            QMessageBox::information(this, "No Selection", "Please select an item in your cart to customize.");
            return;
        }

        const int row = tblCart->selectionModel()->selectedRows().first().row();
        QString plantId = mCart->item(row, 0)->data(Qt::UserRole).toString();
        if (plantId.isEmpty()) 
        {
            QMessageBox::warning(this, "Invalid Selection", "Cannot customize this item.");
            return;
        }

        Plant* plant = facade->getPlant(plantId.toStdString());
        if (!plant) 
        {
            QMessageBox::warning(this, "Error", "Plant not found in greenhouse.");
            return;
        }

        std::unique_ptr<SaleItem> item = std::make_unique<PlantItem>(plant);

        QDialog dialog(this);
        dialog.setWindowTitle("Customize Your Plant");
        QVBoxLayout layout(&dialog);
        QLabel label("Select customizations:");
        layout.addWidget(&label);
        QCheckBox cbPot("Reinforced Pot (+80)");
        QCheckBox cbCard("Message Card (+15)");
        QCheckBox cbWrap("Gift Wrap (+25)");
        layout.addWidget(&cbPot);
        layout.addWidget(&cbCard);
        layout.addWidget(&cbWrap);
        QLineEdit messageEdit;
        messageEdit.setPlaceholderText("Enter card message...");
        layout.addWidget(&messageEdit);
        QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout.addWidget(&buttons);
        QObject::connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        QObject::connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        if (dialog.exec() != QDialog::Accepted)
            return;

        if (cbPot.isChecked())
            item = std::make_unique<ReinforcedPot>(std::move(item));

        if (cbCard.isChecked()) 
        {
            std::string msg = messageEdit.text().toStdString();
            if (msg.empty()) msg = "Best Wishes!";
            item = std::make_unique<MessageCard>(std::move(item), msg);
        }

        if (cbWrap.isChecked())
            item = std::make_unique<GiftWrap>(std::move(item));

        QString desc = QString::fromStdString(item->description());
        double cost = item->cost();
        QString tooltip = QString("Customizations: %1\nTotal Cost: R%2").arg(desc).arg(cost, 0, 'f', 2);
        mCart->item(row, 0)->setText(desc);
        mCart->item(row, 0)->setToolTip(tooltip);
        mCart->item(row, 2)->setText(QString::number(cost, 'f', 2));
        mCart->item(row, 2)->setData(cost, Qt::UserRole + 1);
        recalcTotal();
        QMessageBox::information(this, "Customized", "Your plant has been customized!");
    });
}

void SimpleCustomerWindow::refreshAlerts()
{
    if (!alertsList) return;
    alertsList->clear();
    if (!customerDash) return;
    for (const auto& id : customerDash->getMatured()) {
        alertsList->addItem(QString::fromStdString(id));
    }
}

void SimpleCustomerWindow::populateCatalog()
{
    if (!facade) return;
    
    QSet<QString> selectedIds;
    if (tblCatalog->selectionModel()) 
    {
        QModelIndexList sel = tblCatalog->selectionModel()->selectedRows();
        for (const auto& idx : sel) 
        {
            QString id = mCatalog->item(idx.row(), 0)->text();
            selectedIds.insert(id);
        }
    }
    int scrollPos = tblCatalog->verticalScrollBar() ? tblCatalog->verticalScrollBar()->value() : 0;
    
    mCatalog->removeRows(0, mCatalog->rowCount());
    
    auto plants = facade->browseAvailable();
    QSet<QString> availablePlantIds; 
    
    for (Plant* p : plants) 
    {
        if (!p) continue;
        
        QString plantId = QString::fromStdString(p->id());
        availablePlantIds.insert(plantId);
        
        QList<QStandardItem*> row;
        row << new QStandardItem(plantId)
            << new QStandardItem(QString::fromStdString(p->sku()))
            << new QStandardItem(QString::fromStdString(p->getColour()))
            << new QStandardItem(QString::fromStdString(p->getSpeciesFly()->getName()))
            << new QStandardItem(QString::fromStdString(p->getSpeciesFly()->getBiome()));
        
        auto priceItem = new QStandardItem(QString("R%1").arg(QString::number(p->cost(), 'f', 2)));
        priceItem->setData(p->cost(), Qt::UserRole + 1);
        row << priceItem;
        
        mCatalog->appendRow(row);
    }
    
    for (int r = mCart->rowCount() - 1; r >= 0; --r) 
    {
        QString cartPlantId = mCart->item(r, 0)->data(Qt::UserRole).toString();
        if (!availablePlantIds.contains(cartPlantId)) 
        {
            mCart->removeRow(r);
        }
    }
    recalcTotal();
    
    if (!selectedIds.isEmpty() && tblCatalog->selectionModel()) 
    {
        QItemSelection selection;
        for (int row = 0; row < mCatalog->rowCount(); ++row) 
        {
            QString id = mCatalog->item(row, 0)->text();

            if (selectedIds.contains(id)) 
            {
                QModelIndex idx = mCatalog->index(row, 0);
                selection.select(idx, mCatalog->index(row, mCatalog->columnCount() - 1));
            }
        }
        tblCatalog->selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
    }
    
    if (tblCatalog->verticalScrollBar()) 
    {
        tblCatalog->verticalScrollBar()->setValue(scrollPos);
    }
    
    tblCatalog->resizeColumnsToContents();
    tblCatalog->horizontalHeader()->setStretchLastSection(true);
}

int SimpleCustomerWindow::findCartRow(const QString& plantId) const
{
    for (int r = 0; r < mCart->rowCount(); ++r) 
    {
        auto item = mCart->item(r, 0);
        if (item && item->data(Qt::UserRole).toString() == plantId) return r;
    }
    return -1;
}

void SimpleCustomerWindow::filterCatalog(const QString& term)
{
    const QString t = term.trimmed();
    const bool hasTerm = !t.isEmpty();
    const int nameCol = 3;
    for (int r = 0; r < mCatalog->rowCount(); ++r)
    {
        bool show = true;
        if (hasTerm)
        {
            const QString name = mCatalog->item(r, nameCol)->text();
            show = name.contains(t, Qt::CaseInsensitive);
        }
        tblCatalog->setRowHidden(r, !show);
    }
}

void SimpleCustomerWindow::recalcTotal()
{
    double subtotal = 0.0;
    for (int r = 0; r < mCart->rowCount(); ++r) 
    {
        subtotal += mCart->item(r, 2)->data(Qt::UserRole + 1).toDouble();
    }
    if (lblTotals) lblTotals->setText(QString("Subtotal: R%1").arg(subtotal, 0, 'f', 2));
}

void SimpleCustomerWindow::refreshMyOrders()
{
    if (!facade || !ordersModel) return;
    ordersModel->removeRows(0, ordersModel->rowCount());

    auto orders = facade->getCustomerOrders(userId.toStdString());
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

void SimpleCustomerWindow::refreshRecipients()
{
    if (!facade) return;
    if (!cmbRecipient) return;
    cmbRecipient->clear();
    auto staff = facade->listAllStaff();

    for (const auto& s : staff) 
    {
        Staff* staffObj = facade->getStaff(s.getId());
        if (staffObj && staffObj->getRole() == StaffRole::Sales) 
        {
            QString display = QString::fromStdString(s.getId() + " - " + s.getName());
            cmbRecipient->addItem(display, QString::fromStdString(s.getId()));
        }
    }
}

void SimpleCustomerWindow::loadConversation(const QString& peerId)
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

void SimpleCustomerWindow::showPersonalizedRecommendations()
{
    if (!facade || !mRecommendations) return;
    
    mRecommendations->removeRows(0, mRecommendations->rowCount());
    
    auto plants = facade->getPersonalizedRecommendations(userId.toStdString());
    
    if (plants.empty()) 
    {
        return;
    }
    
    for (Plant* p : plants) 
    {
        if (!p) continue;
        
        QString plantId = QString::fromStdString(p->id());
        QString sku = QString::fromStdString(p->sku());
        QString colour = QString::fromStdString(p->getColour());
        QString name = QString::fromStdString(p->getSpeciesFly()->getName());
        QString biome = QString::fromStdString(p->getSpeciesFly()->getBiome());
        
        QString season;
        Season s = p->getSpeciesFly()->getThrivingSeason();
        switch(s) 
        {
            case Season::Spring: season = "Spring"; break;
            case Season::Summer: season = "Summer"; break;
            case Season::Autumn: season = "Autumn"; break;
            case Season::Winter: season = "Winter"; break;
        }
        
        double cost = p->cost();
        
        QList<QStandardItem*> row;
        row << new QStandardItem(plantId)
            << new QStandardItem(sku)
            << new QStandardItem(colour)
            << new QStandardItem(name)
            << new QStandardItem(biome)
            << new QStandardItem(season);
        
        auto priceItem = new QStandardItem(QString("R%1").arg(QString::number(cost, 'f', 2)));
        priceItem->setData(cost, Qt::UserRole + 1);
        row << priceItem;
        
        mRecommendations->appendRow(row);
    }
    
    tblRecommendations->resizeColumnsToContents();
    tblRecommendations->horizontalHeader()->setStretchLastSection(true);
}


void SimpleCustomerWindow::populateEncyclopedia()
{
    if (!facade || !mEncyclopedia) return;

    mEncyclopedia->removeRows(0, mEncyclopedia->rowCount());

    auto species = facade->listAllSpecies();
    if (species.empty()) return;

    auto toBand = [](double v) -> QString 
    {
        if (v < 0.9) return "LOW";
        if (v <= 1.1) return "MEDIUM";
        return "HIGH";
    };

    auto seasonToString = [](Season s) -> QString 
    {
        switch (s) {
            case Season::Spring: return "Spring";
            case Season::Summer: return "Summer";
            case Season::Autumn: return "Autumn";
            case Season::Winter: return "Winter";
        }
        return "";
    };

    for (const auto& fw : species) 
    {
        if (!fw) continue;

        const QString name = QString::fromStdString(fw->getName());
        const QString biome = QString::fromStdString(fw->getBiome());
        const QString season = seasonToString(fw->getThrivingSeason());
        const QString water = toBand(fw->getWaterSensitivity());
        const QString insect = toBand(fw->getInsecticideTolerance());
        const QString growth = toBand(fw->getGrowthRate());
        const double price = static_cast<double>(fw->getCost());

        QList<QStandardItem*> row;
        row << new QStandardItem(name)
            << new QStandardItem(biome)
            << new QStandardItem(season)
            << new QStandardItem(water)
            << new QStandardItem(insect)
            << new QStandardItem(growth);

        auto priceItem = new QStandardItem(QString("R%1").arg(QString::number(price, 'f', 2)));
        priceItem->setData(price, Qt::UserRole + 1);
        row << priceItem;

        mEncyclopedia->appendRow(row);
    }

    if (tblEncyclopedia) 
    {
        tblEncyclopedia->resizeColumnsToContents();
        tblEncyclopedia->horizontalHeader()->setStretchLastSection(true);
    }
}

