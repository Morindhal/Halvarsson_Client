#include "order.h"
#include "ui_order.h"
#include "clickablelabel.h"
#include <vector>
#include "attribute.h"

Order::Order(QWidget *parent, QString tOrderName, double tPrice) :
    QWidget(parent),
    ui(new Ui::Order),
    mOrderName(tOrderName),
    mPrice(tPrice)
{
    ui->setupUi(this);

    ClickableLabel* tLabel = new ClickableLabel("", this);
    QPixmap tPix(":icons/Salmon_Halvarsson.png");
    tLabel->setPixmap(tPix.scaled(20, 20));
    tLabel->setFixedWidth(20);
    tLabel->setFixedHeight(20);
    ui->Order_Layout->addWidget(tLabel );
    connect(tLabel,SIGNAL(clicked()),this,SLOT(close()));
}

Order::~Order()
{
    delete ui;
}
