#include "addaccountdial.h"
#include "ui_addaccountdial.h"
#include <sqlite_modern_cpp.h>
#include "../passman.hpp"

addAccountDial::addAccountDial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addAccountDial)
{
    ui->setupUi(this);
    account =  new Passman::Account();
}

addAccountDial::~addAccountDial()
{
    delete ui;
}



void addAccountDial::on_saveButton_clicked()
{
    account -> setService(ui->serviceLineEdit->text().toStdString());
    account -> setEmail(ui->emailLineEdit->text().toStdString());
    account -> setUsername(ui->usernameLineEdit->text().toStdString());
    account -> setPassword(ui->passwordLineEdit->text().toStdString());

    account -> saveToDatabase();
    close();
}

void addAccountDial::on_checkBox_toggled(bool checked)
{
    ui->passwordLineEdit->setReadOnly(checked);

    if(checked)
    {
        account -> generatePassword();
        ui -> passwordLineEdit->setText(QString::fromStdString(account -> getPassword()));
    }

    else
        ui -> passwordLineEdit -> clear();
}
