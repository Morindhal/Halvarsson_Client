#include "table.h"
#include "ui_table.h"
#include "clickablelabel.h"
#include "order.h"
#include <vector>
#include "QtAwesome/QtAwesome.h"

Table::Table(QWidget *parent, int tTableNmbr, double tTab) :
    QDialog(parent),
    ui(new Ui::Table),
    mTableNmbr(tTableNmbr),
    mTab(tTab)
{
    ui->setupUi(this);
    QtAwesome* awesome = new QtAwesome( qApp );
    awesome->initFontAwesome();
    ClickableLabel* tLabel = new ClickableLabel("", this);
    QLabel* tLabel2 = new QLabel("", this);
    QPixmap tPix(":icons/pizza.png");
    tLabel->setPixmap(tPix.scaled(30, 30));
    tLabel2->setText(QString("Bord:  ")  + QString(std::to_string(mTableNmbr).c_str()) );
    tLabel->setFixedWidth(65);
    ui->gridLayout->addWidget(tLabel );
    ui->gridLayout->addWidget(tLabel2);
    connect(tLabel,SIGNAL(clicked()),this,SLOT(close()));
}

Table::~Table()
{
    delete ui;
}
