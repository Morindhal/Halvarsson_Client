#include "order.h"
#include "ui_order.h"
#include "clickablelabel.h"
#include <vector>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include "attribute.h"
#include "table.h"

Order::Order(QWidget *parent, QString tOrderName, double tPrice, unsigned int tOrderID) :
    QWidget(parent),
    ui(new Ui::Order),
    mOrderName(tOrderName),
    mPrice(tPrice),
    pOrderID(tOrderID)
{
    ui->setupUi(this);

    ClickableLabel* tLabel = new ClickableLabel("", this);
    QPixmap tPix(":icons/Salmon_Halvarsson.png");
    tLabel->setPixmap(tPix.scaled(20, 20));
    tLabel->setFixedWidth(20);
    tLabel->setFixedHeight(20);
    ui->Order_Layout->addWidget(tLabel );
    mParentTable = (Table*)this->parent();
    connect(tLabel,SIGNAL(clicked()),this,SLOT(closeMe()));
    for(int i = 0 ; i<10 ; i++)
    {
        mAttribute.push_back(new Attribute(0, "Drinks"));
    }
}

Order::~Order()
{
    delete ui;
}

QString Order::toJSON()
{
    QJsonArray tAttributePackaging;
    for(int i = 0 ; i<mAttribute.size() ; i++)
        tAttributePackaging.prepend(mAttribute.at(i)->toJSON());
    /*Package:
            "table":X,
            "OrderID":Y,
            "Attribute":
     * mParentTable->mTableNmbr;
     * pOrderID;
     * tAttributePackaging;
     * into a JSon*/
    QJsonObject tJsonObject;
    tJsonObject.insert("table", mParentTable->mTableNmbr+1);
    tJsonObject.insert("orderID", QString::number(pOrderID));
    tJsonObject.insert("attribute", tAttributePackaging);

    return QJsonDocument(tJsonObject).toJson();
}

void Order::closeMe()
{
    //qDebug() << "Here I am!  : " << mAttribute.at(1)->mAttributeName;
    qDebug() << toJSON();
    for(Attribute* Attributes : mAttribute)
        delete Attributes;
    mParentTable->closeOrder(pOrderID);
}
