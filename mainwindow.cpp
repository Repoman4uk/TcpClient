#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->radioUTF->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Тест гита
void MainWindow::on_pushButton_clicked()
{
    client=new QTcpSocket(this);
    client->connectToHost(ui->lineIP->text(),ui->linePort->text().toInt());
    connect(client,SIGNAL(connected()),SLOT(slotConnected()));
    connect(client,SIGNAL(error(QAbstractSocket::SocketError)),SLOT(slotError(QAbstractSocket::SocketError)));

    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    if (ui->radioUTF->isChecked())
    {
        out<<ui->lineNumber->text().toUtf8();
        //client->write(data);
        //data.clear();
        out<<ui->linecontrol->text().toUtf8();

    }
    if (ui->radioInt->isChecked())
    {
        out<<ui->lineNumber->text().toInt();
        client->write(data);
        data.clear();
        out<<ui->linecontrol->text().toInt();
    }
    if (ui->radioUni->isChecked())
    {
        out<<ui->lineNumber->text();
        client->write(data);
        data.clear();
        out<<ui->linecontrol->text();
    }
    client->write(data);
    //client->flush();
    client->disconnectFromHost();
}
void MainWindow::slotConnected()
{
    ui->textBrowser->append("Коннект есть");

}
void MainWindow::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "Сервер не найден" :
                         err == QAbstractSocket::RemoteHostClosedError ?
                         "Удаленный хост закрыт" :
                         err == QAbstractSocket::ConnectionRefusedError ?
                         "Отказано в соединении" :
                         QString(client->errorString())
                        );
    ui->textBrowser->append(strError);
}
