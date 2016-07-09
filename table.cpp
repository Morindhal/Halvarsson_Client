#include "table.h"
#include "ui_table.h"
#include "clickablelabel.h"
#include "order.h"

#include <vector>

#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QTabWidget>
#include <QTextStream>
#include <QFile>
#include <QResource>
#include <QIODevice>
#include <QVariantMap>

#include "halvarsson_client.h"
//#include "QtAwesome/QtAwesome.h"

Table::Table(QWidget *parent, int tTableNmbr, double tTab) :
    QDialog(parent),
    ui(new Ui::Table),
    mTableNmbr(tTableNmbr),
    mTab(tTab)
{
    ui->setupUi(this);
    //QtAwesome* awesome = new QtAwesome( qApp );
    //awesome->initFontAwesome();
    QLabel* tLabel2 = new QLabel("", this);
    tLabel2->setText(QString(std::to_string(mTableNmbr+1).c_str()) );
    tLabel2->setFont(QFont( "Arial", 30, QFont::Bold));
    ui->Table_Nmbr->addWidget(tLabel2);
    for(int i = 0 ; i<10 ; i++)
        mOrders.push_back(new Order(this,"Ragu",20,i));
    {
        int i = 0, n = 0;
        foreach (Order* var, mOrders)
        {
            ui->Table_Layout->addWidget(var, n%2, i);
            ++n;
            if(n%2== 0)
                ++i;
        }
    }
    mParentServerApp = (Halvarsson_client*)parent;
}

Table::~Table()
{
    delete ui;
}

QString Table::toJSON()
{
    QString tReturnString = "";
    for(Order *order : mOrders)
        tReturnString += order->toJSON();
    return tReturnString;
}

void Table::closeOrder(int tOrderID)
{
    for(int i = 0 ; i<mOrders.size() ; i++)
        if(((Order*)mOrders.at(i))->pOrderID == tOrderID)
        {
            delete mOrders.at(i);
            mOrders.erase(mOrders.begin()+i);
        }
}

void Table::on_pushButton_clicked()
{
    addMenu(mParentServerApp->centralWidget()->findChild<QTabWidget*>("tabWidget"));
}

/*Add the menu to this container*/
void Table::addMenu(QWidget *tContainer)
{

    QFile mFile(":/Halvarsson JSON menu");

    if(!mFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "could not open file for read";
        return;
    }

        QTextStream in(&mFile);
        QString mText = in.readAll();

       // qDebug() << mText;

        QJsonDocument tJsonDocument = QJsonDocument::fromJson(mText.toUtf8());
        qDebug() << tJsonDocument.toJson();
QVariantMap result = tJsonDocument.toVariant().toMap();

        qDebug() << "Extra  : " << result["Extra"].toMap()["Picture"].toString();
        mFile.close();
}
