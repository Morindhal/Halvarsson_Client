#include "table.h"
#include "ui_table.h"
#include "clickablelabel.h"

Table::Table(QWidget *parent, int tInt) :
    QDialog(parent),
    ui(new Ui::Table),
    mInt(tInt)
{
    ui->setupUi(this);
    ClickableLabel* tLabel = new ClickableLabel("", this);
    QLabel* tLabel2 = new QLabel(this);
    tLabel->setPixmap(QPixmap(":/icons/J:/android/Halvarsson icons/my-icons-collection/png/food-1.png"));
    tLabel2->setText(QString("Bord:  ")  + QString(std::to_string(mInt).c_str()) );
    ui->gridLayout->addWidget(tLabel );
    ui->gridLayout->addWidget(tLabel2);
    connect(tLabel,SIGNAL(clicked()),this,SLOT(close()));
}

Table::~Table()
{
    delete ui;
}
