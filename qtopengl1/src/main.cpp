#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setTitle("OpenGL Tutorial");
    w.resize(640,480);
    w.show();
    return a.exec();
}
