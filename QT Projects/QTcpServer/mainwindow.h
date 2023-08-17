#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QList>
#include <QByteArray>
#include <QString>
#include <QMessageBox>
#include <QComboBox>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void newConnection();               // creating new connection function
    void Read_Data_From_Socket();       // reading read data from Socket
    void on_pushButton_Send_clicked();  // To send data from push button

private:
    void Add_New_Client_Connection(QTcpSocket *socket);
private:
    Ui::MainWindow *ui;
    QTcpServer *TCP_Server; // TCP Server created
    QList<QTcpSocket*> Client_Connection_List; // List of client connection
};
#endif // MAINWINDOW_H
