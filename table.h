#ifndef TABLE_H
#define TABLE_H

#include <QDialog>

class Vector;
class Order;
class Halvarsson_client;
class QWidget;

namespace Ui {
class Table;
}

class Table : public QDialog
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = 0, int tTableNmbr = 0, double tTab = 0);
    int mTableNmbr;
    ~Table();
    QString toJSON();
    void addMenu(QWidget *tContainer);

public slots:
    void closeOrder(int tOrderID);


    private slots:
    void on_pushButton_clicked();

    private:
    Ui::Table *ui;
    std::vector<Order*> mOrders;
    double mTab;
    Halvarsson_client *mParentServerApp;
};

#endif // TABLE_H
