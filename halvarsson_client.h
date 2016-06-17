#ifndef HALVARSSON_CLIENT_H
#define HALVARSSON_CLIENT_H

#include <QMainWindow>

class Table;
class QVBoxLayout;

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
    Table *arr[50];
    QVBoxLayout *tVBox;
};

#endif // HALVARSSON_CLIENT_H
