/**
 * @file SimpleStaffWindow.h
 * @brief Staff interface window for nursery management operations
 * @date 2025-11-03
 */

#pragma once
#include <QMainWindow>
#include <QTableView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTabWidget>
#include "../NurseryFacade.h"
#include "../StaffDash.h"
#include <memory>

/**
 * @class SimpleStaffWindow
 * @brief Main window interface for staff members
 * 
 * Provides tabbed interface for staff to manage plants, inventory, orders,
 * messages, and view command logs and alerts. Features include plant care
 * operations, restocking, order fulfillment, and command queue management.
 */
class SimpleStaffWindow : public QMainWindow 
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new staff window
     * @param facade Pointer to the NurseryFacade for operations
     * @param userId The staff member's user ID
     * @param parent Parent widget (optional)
     * @param dashObserver Observer for dashboard updates (optional)
     */
    explicit SimpleStaffWindow(NurseryFacade* facade, QString userId, QWidget* parent = nullptr, StaffDash* dashObserver = nullptr);
    
    /**
     * @brief Refresh the greenhouse plant table
     */
    void refreshGreenhouse();
    
    /**
     * @brief Refresh the stock/inventory table
     */
    void refreshStock();
    
    /**
     * @brief Refresh the staff member list
     */
    void refreshStaff();
    
    /**
     * @brief Refresh assigned orders for this staff member
     */
    void refreshMyOrders();
    
    /**
     * @brief Refresh the command log display
     */
    void refreshCommandLog();

signals:
    /**
     * @brief Signal emitted when user requests logout
     */
    void logoutRequested();

private slots:
    /**
     * @brief Queue water commands for all plants (morning routine)
     */
    void onMorningRoutine();
    
    /**
     * @brief Queue insecticide commands for all plants (night routine)
     */
    void onNightRoutine();
    
    /**
     * @brief Queue water commands for selected plants
     */
    void onQueueWater();
    
    /**
     * @brief Queue fertilize commands for wilting plants
     */
    void onUrgentCare();
    
    /**
     * @brief Queue fertilize commands for selected plants
     */
    void onQueueFertilize();
    
    /**
     * @brief Queue spray insecticide commands for selected plants
     */
    void onQueueSpray();
    
    /**
     * @brief Process the next command in the queue
     */
    void onRunNextGreenhouse();
    
    /**
     * @brief Restock selected species with specified quantity
     */
    void onRestock();
    
    /**
     * @brief Mark selected order as completed
     */
    void onCompleteOrder();
    
    /**
     * @brief Undo the most recent restock operation
     */
    void onUndoLastRestock();

private:
    NurseryFacade* facade;  ///< Facade for nursery operations
    QString userId;         ///< Current staff member's ID
    
    QTabWidget* tabs = nullptr;             ///< Main tab widget
    QWidget* tabGreenhouse = nullptr;       ///< Greenhouse/plant care tab
    QWidget* tabStock = nullptr;            ///< Inventory management tab
    QWidget* tabStaff = nullptr;            ///< Staff roster tab
    QWidget* tabOrders = nullptr;           ///< Order management tab
    QWidget* tabMessages = nullptr;         ///< Messaging tab
    QWidget* tabCommandLog = nullptr;       ///< Command history tab
    QWidget* tabAlerts = nullptr;           ///< Alert notifications tab

    QTableView* plantTable;                 ///< Table displaying plants
    QStandardItemModel* plantModel;         ///< Model for plant table
    QPushButton* btnMorningRoutine;         ///< Button for morning watering routine
    QPushButton* btnNightRoutine;           ///< Button for night insecticide routine
    QPushButton* btnQueueWater = nullptr;   ///< Button to queue water commands
    QPushButton* btnUrgentCare = nullptr;   ///< Button to fertilize wilting plants
    QPushButton* btnQueueFertilize = nullptr; ///< Button to queue fertilize commands
    QPushButton* btnQueueSpray = nullptr;   ///< Button to queue insecticide commands
    QPushButton* btnRunNextCare = nullptr;  ///< Button to process next command
    QPushButton* btnLogout;                 ///< Logout button
    
    QTableView* stockTable = nullptr;       ///< Table displaying inventory
    QStandardItemModel* stockModel = nullptr; ///< Model for stock table
    class QLineEdit* txtQty = nullptr;      ///< Input for restock quantity
    QPushButton* btnRestock = nullptr;      ///< Button to execute restock
    QPushButton* btnUndoRestock = nullptr;  ///< Button to undo last restock
    QPushButton* btnRunQueue = nullptr;     ///< Button to process command queue
    
    QTableView* staffTable = nullptr;       ///< Table displaying staff members
    QStandardItemModel* staffModel = nullptr; ///< Model for staff table
    QPushButton* btnRefreshStaff = nullptr; ///< Button to refresh staff list
    
    class QTreeView* ordersTree = nullptr;  ///< Tree view for orders
    QStandardItemModel* ordersModel = nullptr; ///< Model for orders tree
    QPushButton* btnCompleteOrder = nullptr; ///< Button to complete selected order
    
    class QListWidget* messagesList = nullptr; ///< List widget for messages
    class QLineEdit* messageInput = nullptr;   ///< Input field for new message
    QPushButton* btnSendMessage = nullptr;     ///< Button to send message
    class QComboBox* cmbRecipient = nullptr;   ///< Dropdown to select message recipient
    
    /**
     * @brief Refresh the recipient dropdown list
     */
    void refreshRecipients();
    
    /**
     * @brief Load conversation history with a specific peer
     * @param peerId The ID of the peer (customer or staff)
     */
    void loadConversation(const QString& peerId);
    
    class QTextEdit* txtCommandLog = nullptr; ///< Text display for command log
    QPushButton* btnRefreshLog = nullptr;     ///< Button to refresh command log

    StaffDash* staffDash = nullptr;           ///< Dashboard observer
    class QListWidget* alertsList = nullptr;  ///< List widget for alerts
    
    /**
     * @brief Refresh the alerts list
     */
    void refreshAlerts();
};

