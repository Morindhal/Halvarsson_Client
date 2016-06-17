#ifndef ORDER_H
#define ORDER_H

#include <QWidget>

namespace Ui {
class Order;
}

class Order : public QWidget
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = 0);
    ~Order();

private:
    Ui::Order *ui;
};

#endif // ORDER_H
