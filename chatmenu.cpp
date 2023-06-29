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
 QString contactID[100];


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

     q.exec("SELECT DISTINCT username,reciver  FROM PV JOIN user ON user.ID = PV.reciver WHERE transfer = '"+ID+"' ORDER BY sendingTime DESC");
    q.first();
    int Ccontact = 0;
    do{

        QString name , message;

    //  menuchat->selectionMode(QAbstractItemView::SingleSelection);

      //  if (q.first())
    //    {
           name = q.value(0).toString();
          // message =  q.value(1).toString();
          // time = q.value(2).toInt();
           contactID[Ccontact] = q.value(1).toString();

           QString itemText = name;
           inWidgetList.append(itemText);
           qDebug()<< itemText;
        Ccontact ++;
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
    ui->massageMenu->clear();
qDebug()<<currentRow<<contactID[currentRow];
QSqlQuery q;
QStringList inWidget ;
q.exec("SELECT message,sendingTime FROM PV WHERE transfer  = '"+ID+"' and reciver = '"+contactID[currentRow]+"' UNION SELECT message,sendingTime FROM PV WHERE transfer  = '"+ID+"' and reciver = '"+contactID[currentRow]+"' ORDER by sendingTime");
if (!q.first())
{
    qDebug ()<< "data base not working ";
}
do
{

    QString message = q.value(0).toString();
    int time = q.value(1).toInt();

     QString itemText = message +"        "+ QString::number(time);
      inWidget.append(itemText);




} while (q.next());
for (int i = 0 ; i < inWidget.size() ;i ++ ) {

    QString itemText = inWidget.at(i);
    QListWidgetItem *newItem = new QListWidgetItem(itemText);
    newItem->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled);
    ui->massageMenu->addItem(newItem);
    qDebug()<<inWidget.at(i)<<i<<inWidget.size();

}

}

