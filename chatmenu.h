#ifndef CHATMENU_H
#define CHATMENU_H

#include<QListWidgetItem>
#include <QMainWindow>
#include <QAbstractSocket>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QHostAddress>
#include <QMessageBox>
#include <QMetaType>
#include <QString>
#include <QStandardPaths>
#include <QTcpSocket>

extern QString ID;
namespace Ui {
class chatMenu;
}

class chatMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit chatMenu(QWidget *parent = nullptr);
    ~chatMenu();
signals:
    void newMessage(QString);

private slots:




    void on_menuchat_currentRowChanged(int currentRow);

    void on_sendButton_clicked();

    void on_attachmentButten_clicked();

private:
    Ui::chatMenu *ui;
    void readSocket();
    void discardSocket();
    void displayError(QAbstractSocket::SocketError socketError);

    void displayMessage(const QString& str);
   // void on_pushButton_sendMessage_clicked();
    void on_pushButton_sendAttachment_clicked();


    QTcpSocket* socket;
};





#endif // CHATMENU_H
