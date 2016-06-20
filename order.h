#ifndef ORDER_H
#define ORDER_H

#include <QWidget>

class vector;
class Attribute;

namespace Ui {
class Order;
}

class Order : public QWidget
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = 0, QString tOrderName = "Extra", double tPrice = 0);
    ~Order();

private:
    Ui::Order *ui;
    QString mOrderName;
    std::vector<Attribute> mAttribute;
    double mPrice;
};

#endif // ORDER_H
