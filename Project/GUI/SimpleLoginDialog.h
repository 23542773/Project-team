#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "../NurseryFacade.h"

class SimpleLoginDialog : public QDialog 
{
    Q_OBJECT
public:
    explicit SimpleLoginDialog(NurseryFacade* facade, QWidget* parent = nullptr);
    QString getUserId() const;
    QString getRole() const;

private slots:
    void tryLogin();

private:
    QLineEdit* userIdEdit;
    QComboBox* roleBox;
    QPushButton* loginButton;
    NurseryFacade* facade;
};
