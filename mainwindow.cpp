#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCheckBox>
#include "login.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->nextBtn->setEnabled(false);
    ui->nextBtnEn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}







void MainWindow::on_changeLanguge_activated(int index )
{

    if (index == 0)
    {
            ui->nextBtn->show();
            ui->rolls->show();
            ui->rollsCheck->setText("من موافقم.");
            ui->Englishtext->hide();
            ui->nextBtnEn->hide();



    }
    if (index ==1)
    {

        ui->nextBtn->hide();
        ui->rolls->hide();
        ui->rollsCheck->setText("I accept that.");
        ui->Englishtext->show();
        ui->nextBtnEn->show();


    }
}






void MainWindow::on_rollsCheck_clicked(bool checked)
{
    if (checked)
    {
     ui->nextBtn->setEnabled(true);
     ui->nextBtnEn->setEnabled(true);


    }
    else
    {
        ui->nextBtn->setEnabled(false);
        ui->nextBtnEn->setEnabled(false);
    }

}








void MainWindow::on_nextBtn_clicked()
{
    login *loginPage = new login;

    loginPage->show();
    this->close();

}


void MainWindow::on_nextBtnEn_clicked()
{
    login *loginPage = new login;
    loginPage->show();
    this->close();
}

