#include "mainwindow.h"
#include <QFile>
#include <QApplication>
#include <QDebug>
#include "chatmenu.h"
#include "main.h"
extern QString ID;
int main(int argc, char *argv[])
{

    QFile userfile("D:/Uinversity/chatbot2/finalProject/QUser.txt");
   if (!userfile.open(QIODevice::ReadOnly | QIODevice::Text))
   {
       qDebug()<< "cannot open the file";
   }
   else
   {
   }
    QApplication a(argc, argv);
    if (userfile.size() == 0 )
    {
        MainWindow *w = new MainWindow;
        w->showMinimized();

    }

    else
    {


        chatMenu *W = new chatMenu;
        W->showMinimized();
        }

    return a.exec();
}
