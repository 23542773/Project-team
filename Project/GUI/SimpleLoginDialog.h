/**
 * @file SimpleLoginDialog.h
 * @brief Login dialog for user authentication
 * @author Project Teams
 * @date 2025-11-03
 */

#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "../NurseryFacade.h"

/**
 * @class SimpleLoginDialog
 * @brief Dialog for user authentication and role selection
 * 
 * Provides a simple login interface where users enter their ID and select
 * their role (Customer or Staff). The dialog validates credentials through
 * the NurseryFacade before allowing access.
 */
class SimpleLoginDialog : public QDialog 
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new login dialog
     * @param facade Pointer to the NurseryFacade for authentication
     * @param parent Parent widget (optional)
     */
    explicit SimpleLoginDialog(NurseryFacade* facade, QWidget* parent = nullptr);
    
    /**
     * @brief Get the entered user ID
     * @return QString The user ID entered in the dialog
     */
    QString getUserId() const;
    
    /**
     * @brief Get the selected role
     * @return QString The role selected ("Customer" or "Staff")
     */
    QString getRole() const;

private slots:
    /**
     * @brief Handle login button click
     * 
     * Validates the user ID and role, then accepts the dialog if valid.
     */
    void tryLogin();

private:
    QLineEdit* userIdEdit;      ///< Input field for user ID
    QComboBox* roleBox;         ///< Dropdown for role selection
    QPushButton* loginButton;   ///< Button to submit login
    NurseryFacade* facade;      ///< Facade for authentication
};

