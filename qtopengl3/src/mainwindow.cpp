#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include "triangleglwidget.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Qt Morning Adventure");

    // Create OpenGL Widget
    TriangleGLWidget *triangleglwidget = new TriangleGLWidget(this);

    ui->verticalLayout->addWidget(triangleglwidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}
