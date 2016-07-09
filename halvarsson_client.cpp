#include "halvarsson_client.h"
#include "ui_halvarsson_client.h"
#include "table.h"
#include <QtCore/QDebug>

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
}

Halvarsson_client::~Halvarsson_client()
{
    delete ui;
}

void Halvarsson_client::on_count_clicked()
{
    connect(&m_webSocket, &QWebSocket::connected, this, &Halvarsson_client::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Halvarsson_client::closed);
    m_webSocket.open(QUrl("ws://localhost:1234"));
}

void Halvarsson_client::onConnected()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &Halvarsson_client::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("update"));
}

void Halvarsson_client::onTextMessageReceived(QString message)
{
    qDebug() << "There be fire!";
    ui->label->setText(message);
}

void Halvarsson_client::closed()
{
    qDebug() << "There be ice!";
    ui->label->setText("Argh, server be closed!");
}
