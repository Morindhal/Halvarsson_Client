#ifndef HALVARSSON_CLIENT_H
#define HALVARSSON_CLIENT_H

#include <QMainWindow>
#include <QtWebSockets/QWebSocket>

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

private slots:

    void on_count_clicked();

private:
    Ui::Halvarsson_client *ui;
    Table *t;
    std::vector<Table*> mTable;
    QVBoxLayout *tVBox;
    QWebSocket m_webSocket;

    void onTextMessageReceived(QString message);
    void onConnected();
    void closed();
};

#endif // HALVARSSON_CLIENT_H
