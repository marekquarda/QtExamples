#include "stopwatch.h"
#include <QCoreApplication>

int main(int argc,char *argv[]) {
    QCoreApplication app(argc, argv);
    StopWatch watch;

    return app.exec();
}
