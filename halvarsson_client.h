#ifndef HALVARSSON_CLIENT_H
#define HALVARSSON_CLIENT_H

#include <QMainWindow>
#include <QtWebSockets/QWebSocket>
#include <thread>

class Table;
class QVBoxLayout;
class vector;

namespace Ui {
class Halvarsson_client;
}

class Halvarsson_client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Halvarsson_client(QWidget *parent = 0);
    ~Halvarsson_client();
    unsigned int pCurrentHighestOrderID = 0;
    void BuildUI(QString &JsonMessage);
    void BuildTable(QJsonObject tObject);
    void sendToServer(QString message);
    QWebSocket m_webSocket;

private slots:

    void on_count_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    private:
    Ui::Halvarsson_client *ui;
    Table *t;
    std::vector<Table*> mTable;
    QVBoxLayout *tVBox;
    std::thread *Timers;

    void onTextMessageReceived(QString message);
    void onConnected();
    void closed();
    static void IterateThroughTableTimers(std::vector<Table *> *tTable);
};

#endif // HALVARSSON_CLIENT_H
