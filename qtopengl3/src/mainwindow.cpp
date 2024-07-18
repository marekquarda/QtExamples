#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtOpenGLWidgets/QtOpenGLWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Qt Morning Adventure");

    // Create OpenGL Widget
    QOpenGLWidget *openGLWidget = new QOpenGLWidget(this);

    ui->verticalLayout->addWidget(openGLWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}
