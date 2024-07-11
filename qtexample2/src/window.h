#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QMoveEvent>
#include <QPoint>

class Window : public QWidget
{
    Q_OBJECT

public:
    //Window(QWidget *parent = nullptr);

protected:
    void moveEvent(QMoveEvent *event) override;

signals:
    void positionChanged(const QPoint &point);

};

#endif // WINDOW_H
