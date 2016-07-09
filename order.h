#ifndef ORDER_H
#define ORDER_H

#include <QWidget>

class vector;
class Attribute;
class Table;

namespace Ui {
class Order;
}

class Order : public QWidget
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = 0, QString tOrderName = "Extra", double tPrice = 0, unsigned int tOrderID = 0);
    ~Order();
    unsigned int pOrderID;
    QString toJSON();

private slots:
    void closeMe();

private:
    Ui::Order *ui;
    QString mOrderName;
    std::vector<Attribute*> mAttribute;
    double mPrice;
    Table *mParentTable;
};

#endif // ORDER_H
