#include "viewaccount.h"
#include "ui_viewaccount.h"
#include "../passman.hpp"
#include <QClipboard>

viewAccount::viewAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewAccount)
{
    ui->setupUi(this);
}

viewAccount::~viewAccount()
{
    delete ui;
}

void viewAccount::selectAccount(Passman::Account a)
{
    account = new Passman::Account(a.getService(), a.getEmail(), a.getUsername(), a.getPassword());
    ui->serviceEdit->setText(QString::fromStdString(account ->getService()));
    ui->emailEdit->setText(QString::fromStdString(account ->getEmail()));
    ui->usernameEdit->setText(QString::fromStdString(account ->getUsername()));
    ui->passwordEdit->setText(QString::fromStdString(account ->getPassword()));
}



void viewAccount::on_saveButton_clicked()
{
    account->setEmail(ui->emailEdit->text().toStdString());
    account->setUsername(ui->usernameEdit->text().toStdString());
    account->setPassword(ui->passwordEdit->text().toStdString());

    account->updateDatabase();
    close();
}

void viewAccount::on_pushButton_clicked()
{
    QClipboard *clip = QApplication::clipboard();
    clip -> setText(ui -> passwordEdit ->text());
}
