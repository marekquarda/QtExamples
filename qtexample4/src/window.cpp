#include "window.h"

void Window::moveEvent(QMoveEvent *event) {
    QWidget::moveEvent(event);
    emit positionChanged(event->pos());
}
