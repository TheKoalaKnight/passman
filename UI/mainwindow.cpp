#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addaccountdial.h"
#include "browseaccountsdial.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    addAccountDial dial;
    dial.setModal(true);
    dial.setWindowTitle("Add account");
    dial.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    BrowseAccountsDial dial;
    dial.setModal(true);
    dial.setWindowTitle("Search accounts");
    dial.exec();
}
