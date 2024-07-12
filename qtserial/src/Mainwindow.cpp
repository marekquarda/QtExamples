#include "Mainwindow.h"
#include "./ui_Mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);

     ComPort = new QSerialPort();
     ComPort->setPortName("COM3");
     ComPort->setBaudRate(QSerialPort::BaudRate::Baud115200);
     ComPort->setParity(QSerialPort::Parity::NoParity);
     ComPort->setDataBits(QSerialPort::DataBits::Data8);
     ComPort->setStopBits(QSerialPort::StopBits::OneStop);
     ComPort->setFlowControl(QSerialPort::FlowControl::NoFlowControl);
     ComPort->open(QIODevice::ReadWrite);

     if (ComPort->isOpen()) {
         qDebug() << "Serial Port Is Connected.";
         qDebug() << ComPort->error();
     } else {
         qDebug() << "Serial Port Is Not Connected.";
         qDebug() << ComPort->error();
     }
     connect(ComPort, &QSerialPort::readyRead, this, &MainWindow::Read_Data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Send_clicked() {
    qDebug() << "Push button send clicked ...";
    if (ComPort->isOpen()) {
        // Char(10) = \n;
        // Char(13) = \r;
        ComPort->write(ui->lineEdit_Serial_Data->text().toLatin1() +  char(10));
        ComPort->flush();
    }
}

void MainWindow::Read_Data() {
    if (ComPort->isOpen()) {
        while (ComPort->bytesAvailable()) {
            Data_From_SerialPort += ComPort->readAll();
            if (Data_From_SerialPort.at(Data_From_SerialPort.length() - 1) == char(10)) {
                IS_Data_Received = true;
            }
        }
        if (IS_Data_Received == true) {
            qDebug() << "Data From Serial Port : " << Data_From_SerialPort;
            ui->textEdit->append(Data_From_SerialPort);
            Data_From_SerialPort = "";
            IS_Data_Received = false;
        }
    }
}

