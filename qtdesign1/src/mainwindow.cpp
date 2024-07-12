#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include "pokus.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Pokus pokus;
    ui->setupUi(this);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    //connect(ui->actionSave, &QAction::triggered, saved);
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