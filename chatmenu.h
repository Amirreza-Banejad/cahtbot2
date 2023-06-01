#ifndef CHATMENU_H
#define CHATMENU_H

#include <QMainWindow>

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


private:
    Ui::chatMenu *ui;
};

#endif // CHATMENU_H
