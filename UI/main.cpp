#include "../passman.hpp"
#include "mainwindow.h"
#include <QApplication>
#include <sqlite_modern_cpp.h>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);

    sqlite::database database("/usr/share/passman/accounts.db");
    Passman::Account::setDatabase(database);
    std::srand (time(NULL));

    MainWindow w;
    w.setWindowTitle("Jakob's Password manager");
    w.show();

    return a.exec();
}
