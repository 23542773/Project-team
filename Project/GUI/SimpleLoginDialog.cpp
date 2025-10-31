#include "SimpleLoginDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

SimpleLoginDialog::SimpleLoginDialog(NurseryFacade* f, QWidget* parent) : QDialog(parent), facade(f)
{
    setWindowTitle("Login — Nursery System");
    setFixedSize(800, 350);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Enter User ID:"));
    userIdEdit = new QLineEdit(this);
    layout->addWidget(userIdEdit);

    layout->addWidget(new QLabel("Select Role:"));
    roleBox = new QComboBox(this);
    roleBox->addItem("Customer");
    roleBox->addItem("Staff");
    layout->addWidget(roleBox);

    loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &SimpleLoginDialog::tryLogin);
}

QString SimpleLoginDialog::getUserId() const
{
    return userIdEdit->text();
}

QString SimpleLoginDialog::getRole() const
{
    return roleBox->currentText();
}

void SimpleLoginDialog::tryLogin()
{
    if (userIdEdit->text().trimmed().isEmpty()) 
    {
        QMessageBox::warning(this, "Error", "Please enter a User ID.");
        return;
    }

    QString role = getRole();
    std::string id = userIdEdit->text().toStdString();
    bool valid = false;

    if (facade) 
    {
        if (role == "Customer") valid = facade->isValidCustomer(id);

        else valid = facade->isValidStaff(id);
    }

    if (!valid) 
    {
        QMessageBox::warning(this, "Error", "User ID not found for selected role.");
        return;
    }

    accept(); 
}
