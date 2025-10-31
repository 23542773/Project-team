#pragma once
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTabWidget>
#include "../NurseryFacade.h"
#include <memory>

class SimpleStaffWindow : public QMainWindow 
{
    Q_OBJECT
public:
    explicit SimpleStaffWindow(NurseryFacade* facade, QString userId, QWidget* parent = nullptr);
    void refreshGreenhouse();
    void refreshStock();
    void refreshStaff();
    void refreshMyOrders();
    void refreshCommandLog();

signals:
    void logoutRequested();

private slots:
    void onMorningRoutine();
    void onNightRoutine();
    void onQueueWater();
    void onUrgentCare();
    void onQueueFertilize();
    void onQueueSpray();
    void onRunNextGreenhouse();
    void onRestock();
    void onCompleteOrder();
    void onUndoLastRestock();

private:
    NurseryFacade* facade;
    QString userId;
    
    QTabWidget* tabs = nullptr;
    QWidget* tabGreenhouse = nullptr;
    QWidget* tabStock = nullptr;
    QWidget* tabStaff = nullptr;
    QWidget* tabOrders = nullptr;
    QWidget* tabMessages = nullptr;
    QWidget* tabCommandLog = nullptr;

    QTableView* plantTable;
    QStandardItemModel* plantModel;
    QPushButton* btnMorningRoutine;
    QPushButton* btnNightRoutine;
    QPushButton* btnQueueWater = nullptr;
    QPushButton* btnUrgentCare = nullptr;
    QPushButton* btnQueueFertilize = nullptr;
    QPushButton* btnQueueSpray = nullptr;
    QPushButton* btnRunNextCare = nullptr;
    QPushButton* btnLogout;
    
    QTableView* stockTable = nullptr;
    QStandardItemModel* stockModel = nullptr;
    class QLineEdit* txtQty = nullptr;
    QPushButton* btnRestock = nullptr;
    QPushButton* btnUndoRestock = nullptr;
    QPushButton* btnRunQueue = nullptr;
    
    QTableView* staffTable = nullptr;
    QStandardItemModel* staffModel = nullptr;
    QPushButton* btnRefreshStaff = nullptr;
    
    class QTreeView* ordersTree = nullptr;
    QStandardItemModel* ordersModel = nullptr;
    QPushButton* btnCompleteOrder = nullptr;
    
    class QListWidget* messagesList = nullptr;
    class QLineEdit* messageInput = nullptr;
    QPushButton* btnSendMessage = nullptr;
    class QComboBox* cmbRecipient = nullptr;
    void refreshRecipients();
    void loadConversation(const QString& peerId);
    
    class QTextEdit* txtCommandLog = nullptr;
    QPushButton* btnRefreshLog = nullptr;
};
