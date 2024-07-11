#include "window.h"

#include <QtWidgets>
#include <QDebug>

static void printWindowPosition(const QPoint &point) {
    qDebug() << "new window position is : " << point;
}

void closeWindowFunction() {
    QApplication::quit();
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    auto window = new Window();
    window->setAttribute(Qt::WA_DeleteOnClose);
    auto toplayout = new QVBoxLayout(window);

    auto LineEdit = new QLineEdit;
    toplayout->addWidget(LineEdit);

    auto button = new QPushButton("Press Me");
    auto close = new QPushButton("Close App");
    toplayout->addWidget(button);
    toplayout->addWidget(close);

    // Using a lambda function
    QObject::connect(button, &QPushButton::pressed, [button] {button->setText("Release me!");});
    QObject::connect(button, &QPushButton::released, [button] {button->setText("Press Me!");});

    QObject::connect(close, &QPushButton::pressed, closeWindowFunction);

    QObject::connect(window, &Window::positionChanged, printWindowPosition);

    window->show();
    window->activateWindow();

    return app.exec();
}

