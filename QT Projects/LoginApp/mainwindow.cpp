#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/image/login_icon.png");  // give location of image
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
    ui->statusbar->addPermanentWidget(ui->label_3,1);
    ui->statusbar->addPermanentWidget(ui->progressBar,3);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if(username == "test" && password == "test"){
        /*
        QMessageBox::information(this, "Login", "Username and password is correct");
        hide();
        secDialog = new SecDialog(this);
        secDialog->show();
        */
        ui->statusbar->showMessage("Username and password is correct",5000); // 5s göster sonra kapat
        ui->label_3->setText("Username and password is correct"); // 5s göster sonra kapat
        ui(new Ui::SecDialog());

    }
    else{
      //  QMessageBox::information(this, "Login", "Username and password is not correct");
        ui->statusbar->showMessage("Username and password is not correct",5000); // 5s göster sonra kapat
        ui->label_3->setText("Username and password is not correct"); // 5s göster sonra kapat

    }
}

