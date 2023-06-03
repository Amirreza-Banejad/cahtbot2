#include "chatmenu.h"
#include "ui_chatmenu.h"
#include <qfile.h>
#include <QScrollArea>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QGroupBox>
#include <QGridLayout>
#include <QTextLine>
#include <QLabel>
#include <QDebug>
#include "main.h"
#include <QFile>

 QString ID;
class GContact: public QWidget
{
private:
    QString n, id;
public:
    QGroupBox *contactName  = new QGroupBox ;

    QGroupBox* setGroupBox(QString message, int time,QString name)
    {
        contactName->setTitle(name);
         contactName->setGeometry(0,0,10,5);
        QLabel *Name = new QLabel(message);
        QString ti = QString :: number(time);
        QLabel *Time= new QLabel (ti);
         QHBoxLayout *layout = new QHBoxLayout(contactName);
          layout->addWidget(Name);
          layout->addWidget(Time);


            n = name ;
    return contactName;


    }


};
chatMenu::chatMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatMenu)
{
     QFile userfile("D:/Uinversity/chatbot2/finalProject/QUser.txt");
    QByteArray line;
    while (!userfile.atEnd()) {
            line = userfile.readLine();

        }
    qDebug()<< line;
    ID = "4876";

    QListWidget *menuchat = new QListWidget;

     QSqlDatabase db;
    db=QSqlDatabase ::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Uinversity\\Trem 2\\Advanced Programming\\finalProject\\maindatabase.db");
    db.open();
    QSqlQuery q;



    for (int i = 0 ; q.next()  ; i++ )
    {
        q.exec("SELECT DISTINCT reciver,message,sendingTime  FROM PV WHERE transfer = '"+ID+"' ORDER BY sendingTime DESC");
        QString name, message;
        int time;
        if (q.first())
        {
           name = q.value(0).toString();
           message =  q.value(1).toString();
           time = q.value(2).toInt();
           GContact *contact = new GContact;
           contact->setGroupBox(message, time, name);
           QListWidgetItem *item = new QListWidgetItem;
           item->setSizeHint(contact->contactName->sizeHint());
           menuchat->addItem(item);

        }
        else
        {
            qDebug()<<"connat execute the sqlite query for finding the PVs";
        }

    }









    db.close();


    ui->setupUi(this);
}

chatMenu::~chatMenu()
{
    delete ui;
}



