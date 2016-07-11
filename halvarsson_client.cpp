#include "halvarsson_client.h"
#include "ui_halvarsson_client.h"
#include "table.h"
#include <QtCore/QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariantMap>
#include <chrono>
#include <thread>

QT_USE_NAMESPACE

Halvarsson_client::Halvarsson_client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Halvarsson_client)
{
    ui->setupUi(this);
    tVBox = new QVBoxLayout(ui->area);

    for(int n = 0 ; n<10 ; n++)
    {
        mTable.push_back(new Table(this, n));
        ui->tVBox->addWidget(mTable.at(n));
    }
    ui->Tables->setWidget(ui->tVBox->widget());
    ui->area->setBackgroundRole(QPalette::Dark);

    Timers = new std::thread(IterateThroughTableTimers, &mTable);
}

Halvarsson_client::~Halvarsson_client()
{
    delete ui;
}

void Halvarsson_client::on_count_clicked()
{
    connect(&m_webSocket, &QWebSocket::connected, this, &Halvarsson_client::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Halvarsson_client::closed);
    m_webSocket.open(QUrl("ws://"+ui->adress->text()+":1234"));
}

void Halvarsson_client::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &Halvarsson_client::onTextMessageReceived);
    ui->count->setEnabled(false);
    m_webSocket.sendTextMessage(QStringLiteral("update"));
}

void Halvarsson_client::onTextMessageReceived(QString message)
{
    qDebug() << message;
    if(message.contains("update"))
    {
        BuildUI(message.replace("update",""));
    }
    else if(message.contains("orderevent"))
    {
        QString tstring = message.replace("orderevent","");
        QJsonDocument tEvent = QJsonDocument::fromJson(tstring.toUtf8());
        BuildTable(tEvent.object());
    }
    else
        qDebug() << "Error, unknown message recieved.";
}

void Halvarsson_client::sendToServer(QString message)
{
    m_webSocket.sendTextMessage(message);
}

void Halvarsson_client::closed()
{
    ui->label->setText("Argh, server be closed!");
}

void Halvarsson_client::on_tabWidget_tabCloseRequested(int index)
{
    if(ui->tabWidget->widget(index)->objectName()!=QString("tab"))
    {
        ui->tabWidget->widget(index)->deleteLater();
        ui->tabWidget->removeTab(index);
    }
}

void Halvarsson_client::BuildUI(QString &JsonMessage)
{
    QJsonDocument tJsonDocument = QJsonDocument::fromJson(JsonMessage.toUtf8());
    QVariantMap tResult = tJsonDocument.toVariant().toMap();
    auto tVector = QJsonDocument::fromVariant(tResult["vector"]).array();
    for(int i = 0; i<tVector.size() ; i++)
    {
        BuildTable(tVector.at(i).toObject());
    }
}

void Halvarsson_client::BuildTable(QJsonObject tObject)
{
    QVariantMap tOrderMap = tObject.toVariantMap();
    mTable.at(tOrderMap["table"].toInt())->addOrder(tOrderMap["picture"].toString(), tOrderMap["name"].toString(), tOrderMap["time"].toString());
    pCurrentHighestOrderID = tOrderMap["orderID"].toInt()-1;
}

void Halvarsson_client::IterateThroughTableTimers(std::vector<Table *> *tTable)
{
    /*Eterna-loop the thread that updates the timers.*/
    while(true)
    {
        for(Table* tables : *tTable)
            tables->updateTimer();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
