/**
 * @file SimpleCustomerWindow.h
 * @brief Customer interface window for browsing and purchasing plants
 * @date 2025-11-03
 */

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

/**
 * @class SimpleCustomerWindow
 * @brief Main window interface for customers
 * 
 * Provides a tabbed interface for customers to browse plants, manage shopping cart,
 * view recommendations, access plant encyclopedia, track orders, and send messages to staff.
 */
class SimpleCustomerWindow : public QMainWindow 
{
    Q_OBJECT

public:
    /**
     * @brief Construct a new customer window
     * @param facade Pointer to the NurseryFacade for operations
     * @param userId The customer's user ID
     * @param parent Parent widget (optional)
     * @param dashObserver Observer for dashboard updates (optional)
     */
    explicit SimpleCustomerWindow(NurseryFacade* facade, QString userId, QWidget* parent = nullptr, CustomerDash* dashObserver = nullptr);
    
    /**
     * @brief Populate the catalog table with available plants
     */
    void populateCatalog();
    
    /**
     * @brief Find a cart row by plant ID
     * @param plantId The plant ID to search for
     * @return int Row index if found, -1 otherwise
     */
    int findCartRow(const QString& plantId) const;
    
    /**
     * @brief Recalculate and update the order total
     */
    void recalcTotal();
    
    /**
     * @brief Refresh the customer's order history
     */
    void refreshMyOrders();
    
    /**
     * @brief Filter the catalog by search term
     * @param term The search term (matches species name or SKU)
     */
    void filterCatalog(const QString& term);

signals:
    /**
     * @brief Signal emitted when user requests logout
     */
    void logoutRequested();

private:
    NurseryFacade* facade;      ///< Facade for nursery operations
    QString userId;             ///< Current customer's ID
    class QTabWidget* tabs = nullptr;       ///< Main tab widget
    QWidget* tabCatalog = nullptr;          ///< Plant browsing/shopping tab
    QWidget* tabRecommendations = nullptr;  ///< Personalized recommendations tab
    QWidget* tabEncyclopedia = nullptr;     ///< Plant encyclopedia tab
    QWidget* tabOrders = nullptr;           ///< Order history tab
    QWidget* tabMessages = nullptr;         ///< Messaging tab
    QWidget* tabAlerts = nullptr;           ///< Alert notifications tab
    
    QLineEdit* searchBox;                   ///< Search input for filtering catalog
    QTableView* tblCatalog;                 ///< Table displaying available plants
    QStandardItemModel* mCatalog;           ///< Model for catalog table
    
    QTableView* tblCart;                    ///< Table displaying shopping cart
    QStandardItemModel* mCart;              ///< Model for cart table
    QLabel* lblOrderId;                     ///< Label showing current order ID
    QLabel* lblTotals;                      ///< Label showing order totals

    QPushButton* btnStartOrder;             ///< Button to start new order
    QPushButton* btnAddToCart;              ///< Button to add selected plant to cart
    QPushButton* btnCustomize;              ///< Button to customize cart items
    QPushButton* btnRemoveFromCart;         ///< Button to remove items from cart
    QPushButton* btnLogout;                 ///< Logout button

    class QTreeView* ordersTree = nullptr;  ///< Tree view for order history
    QStandardItemModel* ordersModel = nullptr; ///< Model for orders tree

    QTableView* tblRecommendations = nullptr;      ///< Table for personalized recommendations
    QStandardItemModel* mRecommendations = nullptr; ///< Model for recommendations table
    
    /**
     * @brief Display personalized plant recommendations based on purchase history
     */
    void showPersonalizedRecommendations();
    
    QTableView* tblEncyclopedia = nullptr;  ///< Table for plant encyclopedia
    QStandardItemModel* mEncyclopedia = nullptr; ///< Model for encyclopedia table
    
    /**
     * @brief Populate the encyclopedia with all species information
     */
    void populateEncyclopedia();
    
    class QListWidget* messagesList = nullptr;  ///< List widget for messages
    class QLineEdit* messageInput = nullptr;    ///< Input field for new message
    QPushButton* btnSendMessage = nullptr;      ///< Button to send message
    class QComboBox* cmbRecipient = nullptr;    ///< Dropdown to select message recipient
    
    /**
     * @brief Refresh the recipient dropdown list
     */
    void refreshRecipients();
    
    /**
     * @brief Load conversation history with a specific peer
     * @param peerId The ID of the peer (staff member)
     */
    void loadConversation(const QString& peerId);

    CustomerDash* customerDash = nullptr;       ///< Dashboard observer
    class QListWidget* alertsList = nullptr;    ///< List widget for alerts
    
    /**
     * @brief Refresh the alerts list
     */
    void refreshAlerts();
};

