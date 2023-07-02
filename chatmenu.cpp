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
#include <QStandardPaths>
#include <QTcpSocket>
#include <QMetaType>
#include <QAbstractSocket>
#include <QHostAddress>

 QString ID;
 QString contactID[100];
 int CC;

chatMenu::chatMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chatMenu)
{

    ui->setupUi(this);

    socket = new QTcpSocket(this);

    connect(this, &chatMenu::newMessage, this, &chatMenu::displayMessage);
    connect(socket, &QTcpSocket::readyRead, this, &chatMenu::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &chatMenu::discardSocket);
    //connect(socket, &QAbstractSocket::errorOccurred, this, &MainWindow::displayError);

    socket->connectToHost(QHostAddress::LocalHost,8080);

    if(socket->waitForConnected())
       ui->statusbar->showMessage("Connected to Server");
    else{
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }
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
   // ui->menuchat->setGeometry(10,10,100,500);
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
CC= currentRow;
}

void chatMenu::readSocket()
{
    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_0);

    socketStream.startTransaction();
    socketStream >> buffer;

    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        emit newMessage(message);
        return;
    }

    QString header = buffer.mid(0,128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128);

    if(fileType=="attachment"){
        QString fileName = header.split(",")[1].split(":")[1];
        QString ext = fileName.split(".")[1];
        QString size = header.split(",")[2].split(":")[1].split(";")[0];

        if (QMessageBox::Yes == QMessageBox::question(this, "QTCPServer", QString("You are receiving an attachment from sd:%1 of size: %2 bytes, called %3. Do you want to accept it?").arg(socket->socketDescriptor()).arg(size).arg(fileName)))
        {
            QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+fileName, QString("File (*.%1)").arg(ext));

            QFile file(filePath);
            if(file.open(QIODevice::WriteOnly)){
                file.write(buffer);
                QString message = QString("INFO :: Attachment from sd:%1 successfully stored on disk under the path %2").arg(socket->socketDescriptor()).arg(QString(filePath));
                emit newMessage(message);
            }else
                QMessageBox::critical(this,"QTCPServer", "An error occurred while trying to write the attachment.");
        }else{
            QString message = QString("INFO :: Attachment from sd:%1 discarded").arg(socket->socketDescriptor());
            emit newMessage(message);
        }
    }else if(fileType=="message"){
        QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
        emit newMessage(message);
    }
}

void chatMenu::discardSocket()
{
//    socket->deleteLater();
//    socket=nullptr;

    //QMessageBox:: information(this, "Disconnected!","DC");
    socket->connectToHost(QHostAddress::LocalHost,8080);

    if(socket->waitForConnected())
       ui->statusbar->showMessage("Connected to Server");
    else{
        QMessageBox::critical(this,"QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        exit(EXIT_FAILURE);
    }
}

void chatMenu::displayError(QAbstractSocket::SocketError socketError)
{

    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "QTCPClient", "The host was not found. Please check the host name and port settings.");
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "QTCPClient", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
        default:
            QMessageBox::information(this, "QTCPClient", QString("The following error occurred: %1.").arg(socket->errorString()));
        break;
    }
}


void chatMenu::displayMessage(const QString& str)
{
    QListWidgetItem *newItem = new QListWidgetItem(str);
    newItem->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled);
    ui->massageMenu->addItem(newItem);
}



void chatMenu::on_sendButton_clicked()
{

    if(socket)
    {
        if(socket->isOpen())
        {
            QString str = "INSERT INTO PV (transfer,message,reciver,view) VALUES('"+ID+"','"+ui->messageText->text()+"','"+contactID[CC]+"',0)";
            QListWidgetItem *newItem = new QListWidgetItem(str);
            newItem->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsDragEnabled);
            ui->massageMenu->addItem(newItem);
            QDataStream socketStream(socket);
            socketStream.setVersion(QDataStream::Qt_5_0);

            QByteArray header;
            header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(str.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = str.toUtf8();
            byteArray.prepend(header);

            socketStream << byteArray;

            ui->messageText->clear();
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}

void chatMenu::on_attachmentButten_clicked()
{

    if(socket)
    {
        if(socket->isOpen())
        {
            QString filePath = QFileDialog::getOpenFileName(this, ("Select an attachment"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("File (*.json *.txt *.png *.jpg *.jpeg)"));

            if(filePath.isEmpty()){
                QMessageBox::critical(this,"QTCPClient","You haven't selected any attachment!");
                return;
            }

            QFile m_file(filePath);
            if(m_file.open(QIODevice::ReadOnly)){

                QFileInfo fileInfo(m_file.fileName());
                QString fileName(fileInfo.fileName());

                QDataStream socketStream(socket);
                socketStream.setVersion(QDataStream::Qt_5_0);

                QByteArray header;
                header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(m_file.size()).toUtf8());
                header.resize(128);

                QByteArray byteArray = m_file.readAll();
                byteArray.prepend(header);

                socketStream.setVersion(QDataStream::Qt_5_0);
                socketStream << byteArray;
            }else
                QMessageBox::critical(this,"QTCPClient","Attachment is not readable!");
        }
        else
            QMessageBox::critical(this,"QTCPClient","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPClient","Not connected");
}


