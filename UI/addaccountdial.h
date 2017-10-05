
#ifndef ADDACCOUNTDIAL_H
#define ADDACCOUNTDIAL_H

#include <QDialog>
#include "../passman.hpp"

namespace Ui {
class addAccountDial;
}

class addAccountDial : public QDialog
{
    Q_OBJECT

public:
    explicit addAccountDial(QWidget *parent = 0);
    ~addAccountDial();

private slots:


    void on_saveButton_clicked();

    void on_checkBox_toggled(bool checked);

private:
    Ui::addAccountDial *ui;
    Passman::Account *account;
};

#endif // ADDACCOUNTDIAL_H
