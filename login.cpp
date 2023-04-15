#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include "signin.h"
#include "confirm.h"




login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{


    ui->setupUi(this);


}

login::~login()
{
    delete ui;
}

void login::on_loginBtn_clicked()
{
    QSqlDatabase db;
    QString s =ui->IDEdite->text();
    QString pass = ui->passwordEdit->text();
    db=QSqlDatabase ::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Uinversity\\Trem 2\\Advanced Programming\\finalProject\\maindatabase.db");
    db.open();
    QSqlQuery q;

    q.exec ("SELECT password FROM user WHERE username = '"+s+"' ");
    if (q.first()&&q.value(0).toString()== pass)
    {
        confirm *w3 = new confirm;
        this->hide();
        w3->show();


    }
    else
    {
        QMessageBox :: warning (this,"wrong!!!", "username or password is wrong");

    }


    db.close();
}


void login::on_signInBtn_clicked()
{
    signIn *w2 = new signIn;
    w2->show();
}

