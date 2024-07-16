#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
 //   Pokus pokus;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::close()
{
    qDebug() << "Close action was called";
}

void MainWindow::save()
{
    auto text = ui->plainTextEdit->toPlainText();
    qDebug() << "Save: " + text;
}



