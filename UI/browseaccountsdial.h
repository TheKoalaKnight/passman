#ifndef BROWSEACCOUNTSDIAL_H
#define BROWSEACCOUNTSDIAL_H

#include <QDialog>

namespace Ui {
class BrowseAccountsDial;
}

class BrowseAccountsDial : public QDialog
{
    Q_OBJECT

public:
    explicit BrowseAccountsDial(QWidget *parent = 0);
    ~BrowseAccountsDial();

private slots:
    void on_searchButton_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

private:
    Ui::BrowseAccountsDial *ui;

};

#endif // BROWSEACCOUNTSDIAL_H
