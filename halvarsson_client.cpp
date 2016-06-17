#include "halvarsson_client.h"
#include "ui_halvarsson_client.h"
#include "table.h"

Halvarsson_client::Halvarsson_client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Halvarsson_client)
{
    ui->setupUi(this);
    t = new Table(this);
    //ui->Tables->addWidget(t);
    tVBox = new QVBoxLayout(ui->area);
    //tVBox->setSizeConstraint(QLayout :: SetMinAndMaxSize);

    for(int n = 0 ; n<10 ; n++)
    {
        arr[n] = new Table(this, n);
        ui->tVBox->addWidget(arr[n]);
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
    //ui->label->setText(QString::fromUtf8(std::to_string(arr[49]->mInt+1).c_str()));
}
