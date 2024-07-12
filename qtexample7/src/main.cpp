#include <QApplication>
#include "scribbleArea.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ScribbleArea scribbleArea;
    scribbleArea.resize(400,400);
    scribbleArea.show();

    return app.exec();
}
