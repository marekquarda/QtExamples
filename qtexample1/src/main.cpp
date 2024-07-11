#include "mainwindow.h"

#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    auto window = new QWidget();
    window->setAttribute(Qt::WA_DeleteOnClose);
    auto topLayout = new QVBoxLayout(window);

    // Set up of GUI
    auto slider = new QSlider(Qt::Horizontal);
    slider->setRange(0,100);

    auto spin = new QSpinBox;
    spin->setReadOnly(true);

    auto horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(slider);
    horizontalLayout->addWidget(spin);

    QObject::connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
    slider->setValue(49);

    window->show();
    app.exec();

    return 0;
}
