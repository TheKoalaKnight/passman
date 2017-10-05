#ifndef VIEWACCOUNT_H
#define VIEWACCOUNT_H


#include <QDialog>
#include "../passman.hpp"

namespace Ui {
class viewAccount;
}

class viewAccount : public QDialog
{
    Q_OBJECT

public:
    explicit viewAccount(QWidget *parent = 0);
    ~viewAccount();
    void selectAccount(Passman::Account);

private slots:
    void on_saveButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::viewAccount *ui;
    Passman::Account *account;
};

#endif // VIEWACCOUNT_H
