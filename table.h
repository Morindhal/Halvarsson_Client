#ifndef TABLE_H
#define TABLE_H

#include <QDialog>

class Vector;
class Order;

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

private slots:

private:
    Ui::Table *ui;
    std::vector<Order*> mOrders;
    double mTab;
};

#endif // TABLE_H
