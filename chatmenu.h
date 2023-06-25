#ifndef CHATMENU_H
#define CHATMENU_H

#include<QListWidgetItem>
#include <QMainWindow>
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

private slots:




    void on_menuchat_currentRowChanged(int currentRow);

private:
    Ui::chatMenu *ui;
};

#endif // CHATMENU_H
