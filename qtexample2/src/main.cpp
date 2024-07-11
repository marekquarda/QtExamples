#include <QtWidgets>
#include "stopwatch.h"
//#include <QGuiApplication>
#include "window.h"

// global variable
int value = 0;

// this is a fuctor {Lambda code}
struct LogString {
    explicit LogString(const QString & prefix) : m_prefix(prefix) {}

void operator() (const QString &string) {
    qDebug() << m_prefix + string;
}
private:
    QString m_prefix;
};

void closeWindowFuction() {
    QApplication::quit();
}

static void printWindowPosition(const QPoint &point) {
    qDebug() << "new window postion is " << point;
}

int main(int argc, char *argv[])
{   
    QApplication app(argc, argv);
    StopWatch start;

    auto window = new Window;
    window->setAttribute(Qt::WA_DeleteOnClose);
    auto topLayout = new QVBoxLayout(window);

    // Set up of GUI
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(0,100);

    auto spin = new QSpinBox;
    //spin->setReadOnly(true);

    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(slider);
    horizontalLayout->addWidget(spin);
    topLayout->addLayout(horizontalLayout);

    auto LineEdit = new QLineEdit;
    topLayout->addWidget(LineEdit);

    auto button = new QPushButton("Press Me");
    auto close = new QPushButton("Close App");
    topLayout->addWidget(button);
    topLayout->addWidget(close);

    // using pointer to member function
    QObject::connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
    QObject::connect(spin, &QSpinBox::valueChanged, slider, &QSlider::setValue);
    slider->setValue(49);

    // using functor
    QObject::connect(LineEdit, &QLineEdit::textChanged, LogString("Log: "));

    // using a lambda function
    QObject::connect(button, &QPushButton::pressed, [button] {button->setText("Release Me!");});
    QObject::connect(button, &QPushButton::released, [button] {button->setText("Press Me!");});

    QObject::connect(close, &QPushButton::pressed, closeWindowFuction);

    // Using a context object to break connection (when the context object is destroyed)
    auto selfDestroyingLabel = new QLabel("Click the button int the other window"
                                            "Then close this window and reclick the button.");
    selfDestroyingLabel->setWordWrap(true);
    selfDestroyingLabel->resize(400,200);
    // make the label delete itsef when it gets closed
    selfDestroyingLabel->setAttribute(Qt::WA_DeleteOnClose);

    QObject::connect(button, &QPushButton::clicked,selfDestroyingLabel, [selfDestroyingLabel] {
        selfDestroyingLabel->setText(selfDestroyingLabel->text() + " \nButton clicked!");
    });

    window->show();
    selfDestroyingLabel->show();

    window->raise();
    window->activateWindow();

    QObject::connect(window, &Window::positionChanged, printWindowPosition);

    return app.exec();
}
