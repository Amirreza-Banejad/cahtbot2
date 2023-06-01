#include "chatmenu.h"
#include "ui_chatmenu.h"
#include <qfile.h>
#include <QScrollArea>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>

chatMenu::chatMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatMenu)
{
     QSqlDatabase db;
    db=QSqlDatabase ::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Uinversity\\Trem 2\\Advanced Programming\\finalProject\\maindatabase.db");
    db.open();
    QSqlQuery q;

    //q.exec ("SELECT password FROM user WHERE username = );



    db.close();


    ui->setupUi(this);
}

chatMenu::~chatMenu()
{
    delete ui;
}



