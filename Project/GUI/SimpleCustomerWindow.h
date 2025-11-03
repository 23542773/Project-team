#pragma once
#include <QMainWindow>
#include <QTableView>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QLabel>
#include <set>
#include "../CustomerDash.h"
#include "../NurseryFacade.h"

class SimpleCustomerWindow : public QMainWindow 
{
    Q_OBJECT

public:
    explicit SimpleCustomerWindow(NurseryFacade* facade, QString userId, QWidget* parent = nullptr, CustomerDash* dashObserver = nullptr);
    void populateCatalog();
    int findCartRow(const QString& plantId) const;
    void recalcTotal();
    void refreshMyOrders();
    void filterCatalog(const QString& term);

signals:
    void logoutRequested();

private:
    NurseryFacade* facade;
    QString userId;
    class QTabWidget* tabs = nullptr;
    QWidget* tabCatalog = nullptr;
    QWidget* tabRecommendations = nullptr;
    QWidget* tabEncyclopedia = nullptr; 
    QWidget* tabOrders = nullptr;
    QWidget* tabMessages = nullptr;
    QWidget* tabAlerts = nullptr;
    
    QLineEdit* searchBox;
    QTableView* tblCatalog;
    QStandardItemModel* mCatalog;
    
    QTableView* tblCart;
    QStandardItemModel* mCart;
    QLabel* lblOrderId;
    QLabel* lblTotals;

    QPushButton* btnStartOrder;
    QPushButton* btnAddToCart;
    QPushButton* btnCustomize;
    QPushButton* btnRemoveFromCart;
    QPushButton* btnLogout;

    class QTreeView* ordersTree = nullptr;
    QStandardItemModel* ordersModel = nullptr;

    QTableView* tblRecommendations = nullptr;
    QStandardItemModel* mRecommendations = nullptr;
    void showPersonalizedRecommendations();
    
    QTableView* tblEncyclopedia = nullptr;
    QStandardItemModel* mEncyclopedia = nullptr;
    void populateEncyclopedia();
    
    class QListWidget* messagesList = nullptr;
    class QLineEdit* messageInput = nullptr;
    QPushButton* btnSendMessage = nullptr;
    class QComboBox* cmbRecipient = nullptr;
    void refreshRecipients();
    void loadConversation(const QString& peerId);

    CustomerDash* customerDash = nullptr;
    class QListWidget* alertsList = nullptr;
    void refreshAlerts();
};
