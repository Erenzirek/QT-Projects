#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TCP_Server = new QTcpServer();
    if (TCP_Server->listen(QHostAddress::Any, 8080))
    {
        connect(TCP_Server, SIGNAL(newConnection()), this, SLOT(newConnection()));
        /*
         * Signals and slots allow communication by establishing connections between objects derived from QObject.
         * A signal is emitted when an event occurs, triggering connected slots to be invoked automatically.
         */
        QMessageBox::information(this, "Qt With Eren", "Server started");
    }
    else
    {
        QMessageBox::information(this, "Qt With Eren", "Server start Failed");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// This function is check is any client are coming or not and store in list
void MainWindow::newConnection()
{
    while (TCP_Server->hasPendingConnections())
    {
        /*
         * TCP_Server->hasPendingConnections()
         * The QTcpServer class is a class that accepts and manages TCP-based network connections. The hasPendingConnections() function,
         * when called on this object, checks whether there are any pending (unaccepted) connection requests on the server.
         * If there are pending connection requests, this function returns true; otherwise, it returns false.
         *
        */
        Add_New_Client_Connection(TCP_Server->nextPendingConnection());
    }
}

// Read Data From Client
void MainWindow::Read_Data_From_Socket()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender()); // Cast using qobject_cast
    QByteArray Message_From_Server = socket->readAll();
    QString Message = "Client : " + QString::number(socket->socketDescriptor()) + "::" + QString::fromUtf8(Message_From_Server); // Use fromUtf8
    ui->textEdit_Client_Messages->append(Message);
}

// This Function is Use for store all new clients connection and assingn it's signal and slot
void MainWindow::Add_New_Client_Connection(QTcpSocket *socket)
{
    Client_Connection_List.append(socket);
    connect(socket, SIGNAL(readyRead()), this, SLOT(Read_Data_From_Socket()));
    ui->comboBox_Client_List->addItem(QString::number(socket->socketDescriptor()));
    QString Client = "Client : " + QString::number(socket->socketDescriptor()) + " Connected With The Server"; // Added space
    ui->textEdit_Client_Messages->append(Client);
}

// When push button is clicked Send message
void MainWindow::on_pushButton_Send_clicked()
{
    QString Message_For_Client = ui->lineEdit_Message_For_Client->text();
    QString Receiver = ui->comboBox_Client_List->currentText();
    if (ui->comboBox_Send_Message_Type->currentText() == "All") // Send Message To All Connected Clients
    {
        foreach (QTcpSocket *socket, Client_Connection_List)
        {
            socket->write(Message_For_Client.toUtf8()); // Use toUtf8
        }
    }
    else // Send Message To Only Selected Connected Client
    {
        foreach (QTcpSocket *socket, Client_Connection_List)
        {
            if (socket->socketDescriptor() == Receiver.toLongLong())
            {
                socket->write(Message_For_Client.toUtf8()); // Use toUtf8
            }
        }
    }
}
