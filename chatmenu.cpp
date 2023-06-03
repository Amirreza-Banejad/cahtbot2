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
#include <qgroupbox.h>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>


 QString ID;
//class GContact: public QWidgetListItem
//{
//private:
//    QString n, id;
//public:
//    QGroupBox *contactName  = new QGroupBox ;

//    QGroupBox* setGroupBox(QString message, int time,QString name)
//    {
//        contactName->setTitle(name);
//         contactName->setGeometry(0,0,10,5);
//        QLabel *Name = new QLabel(message);
//        QString ti = QString :: number(time);
//        QLabel *Time= new QLabel (ti);
//         QHBoxLayout *layout = new QHBoxLayout(contactName);
//          layout->addWidget(Name);
//          layout->addWidget(Time);


//            n = name ;
//    return contactName;


//    }

chatMenu::chatMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatMenu)
{

     QFile userfile("D:/Uinversity/chatbot2/finalProject/QUser.txt");
     userfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray line;
    while (!userfile.atEnd()) {
            line = userfile.readLine();

        }
    qDebug()<< line;


    QListWidget *menuchat = new QListWidget(this);
      menuchat->setGeometry(10,10,100,500);

     QSqlDatabase db;
    db=QSqlDatabase ::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Uinversity\\Trem 2\\Advanced Programming\\finalProject\\maindatabase.db");
    db.open();
    QSqlQuery q;


     q.exec("SELECT DISTINCT reciver,message,sendingTime  FROM PV WHERE transfer = '"+ID+"' ORDER BY sendingTime DESC");
     q.first();
    while(q.next())
    {

        QString name , message;
        int time;
      //  if (q.first())
    //    {
           name = q.value(0).toString();
           message =  q.value(1).toString();
           time = q.value(2).toInt();

            QListWidgetItem *item = new QListWidgetItem;

           // Create a QGroupBox object
           QGroupBox* groupBox = new QGroupBox(name);
           QVBoxLayout *layout= new QVBoxLayout;
           // Add widgets to the QGroupBox
           QLabel *Message  = new QLabel (message);
           Message->setGeometry(5,5,15,5);
           layout->addWidget(Message);

           layout->addWidget(new QLabel(QString::number(time)));
           groupBox->setLayout(layout);

           item->setSizeHint(groupBox->sizeHint());
           menuchat->addItem(item);
          menuchat->setItemWidget(item, groupBox);
            menuchat->show();
            qDebug() << name << message;

                   // Add the QGroupBox to the QWidgetList






    }
    db.close();


    ui->setupUi(this);
}

chatMenu::~chatMenu()
{
    delete ui;
}



