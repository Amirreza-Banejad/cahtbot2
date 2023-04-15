#include "confirm.h"
#include "ui_confirm.h"
#include <QMessageBox>
int r;
confirm::confirm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::confirm)
{

    ui->setupUi(this);

}

confirm::~confirm()
{
    delete ui;
}



void confirm::on_loadCode_clicked()
{
     r = rand()%10000+1;
    QString rand= QString ::number (r);
   QMessageBox::warning(this ,"confirm code ", "code : "+rand+"");
}


void confirm::on_GO_clicked()
{

    int rand = ui->lineEdit->text().toInt();
    if (r == rand )
    {
        QMessageBox ::information (this," Welcome!","hello !");

    }
    else
    {
        QMessageBox ::information (this,"wrong","try again!");
    }
}

