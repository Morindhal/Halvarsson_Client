#include "order.h"
#include "ui_order.h"
#include "clickablelabel.h"
#include <vector>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDateTime>
#include "attribute.h"
#include "table.h"

Order::Order(QWidget *parent, QString tPic, QString tOrderName, double tPrice, unsigned int tOrderID, const QString &tTime) :
    QWidget(parent),
    ui(new Ui::Order),
    mOrderName(tOrderName),
    mPic(tPic),
    mPrice(tPrice),
    pOrderID(tOrderID)
{
    mCreatedTime = QDateTime::fromString(tTime, Qt::ISODate);
    ui->setupUi(this);

    mLabel = new ClickableLabel("", this);
    QPixmap tPix(":icons/"+tPic);
    mLabel->setPixmap(tPix.scaled(20, 20));
    mLabel->setFixedWidth(20);
    mLabel->setFixedHeight(20);
    ui->Order_Layout->addWidget(mLabel );
    mParentTable = (Table*)this->parent();
    connect(mLabel,SIGNAL(clicked()),this,SLOT(closeMe()));
}

Order::~Order()
{
    delete ui;
}

QJsonObject Order::toJSON()
{
    QJsonArray tAttributePackaging;
    for(int i = 0 ; i<mAttribute.size() ; i++)
        tAttributePackaging.prepend(mAttribute.at(i)->toJSON());
    QJsonObject tJsonObject;
    tJsonObject.insert("table", mParentTable->mTableNmbr);
    tJsonObject.insert("orderID", (int)pOrderID);
    tJsonObject.insert("attribute", tAttributePackaging);
    tJsonObject.insert("picture", mPic);
    tJsonObject.insert("name", mOrderName);

    return tJsonObject;
}

void Order::closeMe()
{
    for(Attribute* Attributes : mAttribute)
        delete Attributes;
    mParentTable->closeOrder(pOrderID);
}
