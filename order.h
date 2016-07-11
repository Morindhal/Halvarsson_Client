#ifndef ORDER_H
#define ORDER_H

#include <QWidget>
#include <QDateTime>

class vector;
class Attribute;
class Table;
class QDateTime;
class ClickableLabel;

namespace Ui {
class Order;
}

class Order : public QWidget
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = 0, QString tPic = "", QString tOrderName = "", double tPrice = 0, unsigned int tOrderID = 0, const QString &tTime = "");
    ~Order();
    unsigned int pOrderID;
    QJsonObject toJSON();
    QString mOrderName;
    QDateTime mCreatedTime;

private slots:
    void closeMe();

private:
    Ui::Order *ui;
    QString mPic;
    std::vector<Attribute*> mAttribute;
    double mPrice;
    Table *mParentTable;
    ClickableLabel* mLabel;
};

#endif // ORDER_H
