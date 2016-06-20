#include "order.h"
#include "ui_order.h"
#include <vector>
#include "attribute.h"

Order::Order(QWidget *parent, QString tOrderName, double tPrice) :
    QWidget(parent),
    ui(new Ui::Order),
    mOrderName(tOrderName),
    mPrice(tPrice)
{
    ui->setupUi(this);
}

Order::~Order()
{
    delete ui;
}
