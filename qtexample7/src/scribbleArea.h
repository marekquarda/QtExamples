#ifndef SCRIBLEAREA_H
#define SCRIBLEAREA_H

#include <QWidget>
#include <QPainterPath>

class QResizeEvent;
class QPaintEvent;
class QMouseEvent;

/**
 * A class that lets the user draw scribbles with the mouse. The
 * Window  know how to redraw itself.s
 */
class ScribbleArea : public QWidget {
    Q_OBJECT

public:
    explicit ScribbleArea(QWidget *parent = nullptr);
    ~ScribbleArea() override;

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;

private:
    QPainterPath m_drawing;
};

#endif
