#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QSerialPort>

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
    void on_pushButton_Send_clicked();
    void Read_Data();

private:
     Ui::MainWindow *ui;
     QSerialPort* ComPort;
     QString Data_From_SerialPort;
     bool IS_Data_Received = false;
};
#endif // MAINWINDOW_H
