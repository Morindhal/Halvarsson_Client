#include "table.h"
#include "ui_table.h"
#include "clickablelabel.h"
#include "order.h"

#include <vector>

#include <QJsonObject>
#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>
#include <QTabWidget>
#include <QTextStream>
#include <QFile>
#include <QResource>
#include <QIODevice>
#include <QTabWidget>
#include <QDateTime>

#include "halvarsson_client.h"
//#include "QtAwesome/QtAwesome.h"

Table::Table(QWidget *parent, int tTableNmbr, double tTab) :
    QDialog(parent),
    ui(new Ui::Table),
    mTableNmbr(tTableNmbr),
    mTab(tTab),
    mtemp(0)
{
    ui->setupUi(this);
    //QtAwesome* awesome = new QtAwesome( qApp );
    //awesome->initFontAwesome();
    QLabel* tLabel2 = new QLabel("", this);
    tLabel2->setText(QString(std::to_string(mTableNmbr+1).c_str()) );
    tLabel2->setFont(QFont( "Arial", 30, QFont::Bold));
    ui->Table_Nmbr->addWidget(tLabel2);

    mParentServerApp = (Halvarsson_client*)parent;

    tLabel2->setStyleSheet("QLabel { color : black; }");
    ui->tabletime->setStyleSheet("QLabel { color : black; }");
}

Table::~Table()
{
    delete ui;
}

std::vector<QJsonObject>  Table::toJSON()
{
    std::vector<QJsonObject> tOrders;
    for(Order *order : mOrders)
        tOrders.push_back( order->toJSON());
    return tOrders;
}

void Table::closeOrder(int tOrderID)
{
    for(int i = 0 ; i<mOrders.size() ; i++)
        if(((Order*)mOrders.at(i))->pOrderID == tOrderID)
        {
            delete mOrders.at(i);
            mOrders.erase(mOrders.begin()+i);
        }
    displayOrders();
}

void Table::on_pushButton_clicked()
{
    if(mParentServerApp->m_webSocket.isValid())
        addMenu(mParentServerApp->centralWidget()->findChild<QTabWidget*>("tabWidget"));
    else
        mParentServerApp->centralWidget()->findChild<QLabel*>("label")->setText("You must connect first!!");
}

/*Add the menu to this container*/
void Table::addMenu(QTabWidget *tContainer)
{

    QFile mFile(":/Halvarsson JSON menu");

    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "could not open file for read";
        return;
    }

        QTextStream in(&mFile);
        QString mText = in.readAll();

    QJsonDocument tJsonDocument = QJsonDocument::fromJson(mText.toUtf8());
    QVariantMap result = tJsonDocument.toVariant().toMap();

    QVariantMap Order = result["order"].toMap();

    {
        /*
         * TODO:
         * implement more of the menu
        */
        int tColumnCount = 1, tRowCount = 0;
        QGridLayout *tLayoutFIXME = new QGridLayout;
        QWidget *tMenuWidgetFIXME = new QWidget;
        tMenuWidgetFIXME->setLayout(tLayoutFIXME);
        tContainer->addTab(tMenuWidgetFIXME,QString(("Table : "+std::to_string(mTableNmbr+1)).c_str()));
        tMenuWidgetFIXME->setObjectName(std::to_string(mTableNmbr+1).c_str());

        QList<QString> currentOrder = Order.keys();
        for(int i = 0; i<currentOrder.size() ; i++)
        {
            QVariantMap tOrderDetail = Order[currentOrder.at(i)].toMap();
            ClickableLabel * tClickLabel = new ClickableLabel("",tContainer, tOrderDetail["Picture"].toString(),currentOrder.at(i));

            QPixmap tPix(":icons/"+tOrderDetail["Picture"].toString());
            tClickLabel->setPixmap(tPix.scaled(30, 30));
            tClickLabel->setFixedWidth(30);
            tClickLabel->setFixedHeight(30);
            if(tColumnCount%4 == 0)
            {
                tColumnCount=1;
                ++tRowCount;
            }
            else
                ++tColumnCount;
            tLayoutFIXME->addWidget(tClickLabel,tRowCount,tColumnCount);
            connect(tClickLabel,SIGNAL(clicked(QString,QString)),this,SLOT(newOrderEvent(QString,QString)));
        }
    }


    //QVariantMap result3 = result2["Drinks"].toMap();

        mFile.close();
}

void Table::newOrderEvent(const QString &tPic, const QString &tName, bool tKillTab)
{
    QJsonDocument tDoc(Order(this,tPic,tName,20,mParentServerApp->pCurrentHighestOrderID++).toJSON());
    mParentServerApp->sendToServer("orderevent"+tDoc.toJson());
    QTabWidget *tTab = mParentServerApp->findChild<QTabWidget*>("tabWidget");
    if(tKillTab)
        tTab->removeTab(tTab->currentIndex());
    qDebug() << tDoc.toJson();
}

void Table::addOrder(const QString &tPic, const QString &tName, const QString &tTime)
{
    mOrders.push_back(new Order(this,tPic,tName,20,mParentServerApp->pCurrentHighestOrderID++, tTime));
    displayOrders();
}

void Table::displayOrders()
{
    int i = 0, n = 0;
    foreach (Order* order, mOrders)
            ui->Table_Layout->removeWidget(order);
    foreach (Order* order, mOrders)
    {
        ui->Table_Layout->addWidget(order, n%2, i);
        ++n;
        if(n%2== 0)
            ++i;
    }
}

void Table::updateTimer()
{
    QString color("QLabel{background-color:white;}");
    qint64 tMaxOrderTime = 0;
    qint64 tNewOrderTime = 0;
    for(Order* orders : mOrders)
    {
        tNewOrderTime = orders->mCreatedTime.msecsTo(QDateTime::currentDateTime());
        if(tNewOrderTime>300000)
            color = "background-color:red;";
        else if(tNewOrderTime>20000 && tMaxOrderTime<20000)
            color = "background-color:yellow;";

        if(tNewOrderTime>tMaxOrderTime)
            tMaxOrderTime = tNewOrderTime;
    }
    //this->setStyleSheet(color);
    //((tMaxOrderTime)/1000)%60)+":"+QString::number((tMaxOrderTime/1000-((tMaxOrderTime)/1000)%60)*60
    ui->tabletime->setText(QString::number(tMaxOrderTime/1000));
}
