#ifndef SIGNIN_H
#define SIGNIN_H

#include <QMainWindow>

namespace Ui {
class signIn;
}

class signIn : public QMainWindow
{
    Q_OBJECT

public:
    explicit signIn(QWidget *parent = nullptr);
    ~signIn();

private slots:


    void on_signInBtn_clicked();

private:
    Ui::signIn *ui;
};

#endif // SIGNIN_H
