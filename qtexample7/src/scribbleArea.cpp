#include "scribbleArea.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>

ScribbleArea::ScribbleArea(QWidget * parent) : QWidget(parent), m_drawing() {
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

ScribbleArea::~ScribbleArea() {}

/**
  * This vitual method gets called whenever the users pressed the
  * mouse over the window.
  **/
void ScribbleArea::mousePressEvent(QMouseEvent* event) {
    m_drawing.moveTo(event->pos());
}

/**
 * This virtual method gets called whenver the user moves the mouse
 * while the mouse button is pressed si pressed (this is also known as "dragging")
 * If we had called setMousetracking (true) before, this method would also be called
 * when the mouse was moved without any button pressed. We know that we haven't, and trus
 * don't have to chack whether any buttons are pressed
 */
void ScribbleArea::mouseMoveEvent(QMouseEvent* event) {
    // record a line from the last position to the currnet one
    m_drawing.lineTo(event->pos());
    // schedule a repaint
    update();
}

/**
 * Draw the path
 */
void ScribbleArea::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::black,3));
    painter.drawPath(m_drawing);
}





