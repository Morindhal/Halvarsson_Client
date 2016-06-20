#include "halvarsson_client.h"
#include "ui_halvarsson_client.h"
#include "table.h"

Halvarsson_client::Halvarsson_client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Halvarsson_client)
{
    ui->setupUi(this);
    t = new Table(this);
    tVBox = new QVBoxLayout(ui->area);

    for(int n = 0 ; n<10 ; n++)
    {
        mTable.push_back(new Table(this, n));
        ui->tVBox->addWidget(mTable.at(n));
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
