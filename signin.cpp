#include "signin.h"
#include "ui_signin.h"
#include <iostream>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>



signIn::signIn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::signIn)
{
    ui->setupUi(this);
}

signIn::~signIn()
{
    delete ui;
}



void signIn::on_signInBtn_clicked()
{
    QString username,pass ,pass2, phone ;
    username = ui->usernameEdit->text();
    pass = ui->pass1->text();
    pass2 = ui-> pass2->text();
    phone = ui->phone->text();
    int r= rand()%10000;
    QString ID = QString::number(r);
    if (pass == pass2 )
    {
        QSqlDatabase db;

        db=QSqlDatabase ::addDatabase("QSQLITE");
        db.setDatabaseName("D:\\Uinversity\\Trem 2\\Advanced Programming\\finalProject\\maindatabase.db");
        db.open();
        QSqlQuery q;

            q.exec("INSERT INTO user  "
                          "VALUES ('"+username+"', '"+ID+"', ,'"+pass+"','"+phone+"',0)");

            db.close();


    }
    else
    {
        QMessageBox :: warning (this , "password","password not match");
    }
}

