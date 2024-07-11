#include "window.h"

#include <QMoveEvent>
#include <QWidget>

void Window::moveEvent(QMoveEvent *event) {

    QWidget::moveEvent(event);
    emit positionChanged(event->pos());
}
