#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMoveEvent>
#include <QPoint>

class Window : public QWidget {
    Q_OBJECT

public:

protected:
    void moveEvent(QMoveEvent *event) override;

signals:
    void positionChanged(const QPoint &point);

};

#endif
