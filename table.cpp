#include "table.h"
#include "ui_table.h"
#include "clickablelabel.h"
#include "order.h"
#include <vector>
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
        mOrders.push_back(new Order(this,"Ragu",20));
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
}

Table::~Table()
{
    delete ui;
}
