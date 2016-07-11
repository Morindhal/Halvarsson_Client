#ifndef TABLE_H
#define TABLE_H

#include <QDialog>

class Vector;
class Order;
class Halvarsson_client;
class QTabWidget;

namespace Ui {
class Table;
}

class Table : public QDialog
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = 0, int tTableNmbr = 0, double tTab = 0);
    int mTableNmbr;
    ~Table();
    std::vector<QJsonObject> toJSON();
    void addMenu(QTabWidget *tContainer);
    void displayOrders();
    void updateTimer();


public slots:
    void closeOrder(int tOrderID);
    void addOrder(const QString &tPic, const QString &tName, const QString &tTime);
    void newOrderEvent(const QString &tPic, const QString &tName, bool tKillTab = true);


    private slots:
    void on_pushButton_clicked();

    private:
    Ui::Table *ui;
    std::vector<Order*> mOrders;
    double mTab;
    Halvarsson_client *mParentServerApp;
    int mtemp;
};

#endif // TABLE_H
