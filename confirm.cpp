#include "confirm.h"
#include "ui_confirm.h"
#include <QMessageBox>
#include <QFile>
#include <QDebug>
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

        QFile *userFile = new QFile("D:/Uinversity/chatbot2/finalProject/user.txt");



        if(!userFile->open(QFile::WriteOnly |
                                 QFile::Text))
        {
            qDebug()<<"not succes";
        }
        else {

        }
        userFile->close();

    }
    else
    {
        QMessageBox ::information (this,"wrong","try again!");
    }

}

