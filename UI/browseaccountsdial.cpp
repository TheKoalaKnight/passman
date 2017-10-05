#include "browseaccountsdial.h"
#include "ui_browseaccountsdial.h"
#include <vector>
#include "../passman.hpp"
#include "viewaccount.h"

BrowseAccountsDial::BrowseAccountsDial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrowseAccountsDial)
{
    ui->setupUi(this);
}

BrowseAccountsDial::~BrowseAccountsDial()
{
    delete ui;
}

void BrowseAccountsDial::on_searchButton_clicked()
{
    ui->listWidget->clear();
    std::vector <Passman::Account> result;
    result = Passman::Account::searchDatabase(ui->searchTermLineEdit->text().toStdString());
    for (Passman::Account a : result)
        ui->listWidget->addItem(QString::fromStdString(a.getService()));
}

void BrowseAccountsDial::on_listWidget_clicked(const QModelIndex &index)
{
    std::vector <Passman::Account> result;
    result = Passman::Account::searchDatabase(ui->searchTermLineEdit->text().toStdString());
    viewAccount dial;
    dial.setModal(true);
    dial.selectAccount(result[index.row()]);
    dial.setWindowTitle(QString::fromStdString(result[index.row()].getService()));
    dial.exec();
}
