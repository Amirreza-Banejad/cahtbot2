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
#include <QVector>

 QString ID;
//class GContact: public QWidgetListItem
//{
//private:

//public:
//    QString name, id;
//};
//QVector<GContact> contact;
chatMenu::chatMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatMenu)
{

    ui->setupUi(this);
     QFile userfile("D:/Uinversity/chatbot2/finalProject/QUser.txt");
     userfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray line;
    while (!userfile.atEnd()) {
            line = userfile.readLine();

        }
    qDebug()<< line;
    ID = line;

  //  QListWidget *menuchat = new QListWidget (this);
  //  menuchat = ;
    ui->menuchat->setGeometry(10,10,100,500);
     // menuchat->setSelectionMode(QAbstractItemView::SingleSelection);
      //menuchat->setDragEnabled(true);
      //menuchat->viewport()->setAcceptDrops(true);

     // menuchat->editTriggers(QAbstractItemView::doubleClicked);
     ui->menuchat->setDropIndicatorShown(true);
      //! [0] //! [1]
      ui->menuchat->setDragDropMode(QAbstractItemView::InternalMove);
     // menuchat->QAbstractItemView::selectionMode(QAbstractItemView::SingleSelection);
     QSqlDatabase db;
    db=QSqlDatabase ::addDatabase("QSQLITE");
    db.setDatabaseName("D:\\Uinversity\\Trem 2\\Advanced Programming\\finalProject\\maindatabase.db");
    db.open();
    QSqlQuery q;

    //QListWidgetItem *item = new QListWidgetItem [2];
    QStringList inWidgetList ;

     q.exec("SELECT DISTINCT reciver,message,sendingTime,username  FROM PV JOIN user ON user.ID = PV.reciver WHERE transfer = '"+ID+"' ORDER BY sendingTime DESC");
    q.first();
    int i = 0 ;
    do{

        QString name , message;
        int time;
    //  menuchat->selectionMode(QAbstractItemView::SingleSelection);

      //  if (q.first())
    //    {
           name = q.value(3).toString();
           message =  q.value(1).toString();
           time = q.value(2).toInt();

           QString itemText = name +"   "+ QString::number(time);
           inWidgetList.append(itemText);
           qDebug()<< itemText;

    }while(q.next());
    //db.close();


    for (int i = 0; i < inWidgetList.size(); i++) {
        QString itemText = inWidgetList.at(i);
        QListWidgetItem *newItem = new QListWidgetItem(itemText);
        newItem->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled);
        ui->menuchat->addItem(newItem);

    }



}

chatMenu::~chatMenu()
{
    delete ui;
}






void chatMenu::on_menuchat_currentRowChanged(int currentRow)
{
qDebug()<<currentRow;
}

