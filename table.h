#ifndef TABLE_H
#define TABLE_H

#include <QDialog>

namespace Ui {
class Table;
}

class Table : public QDialog
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = 0, int tInt = 0);
    int mInt;
    ~Table();

private slots:

private:
    Ui::Table *ui;
};

#endif // TABLE_H
