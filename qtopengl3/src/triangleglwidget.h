#ifndef TRIANGLEGLWIDGET_H
#define TRIANGLEGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>

class TriangleGLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    TriangleGLWidget(QWidget *parent = nullptr);
    ~TriangleGLWidget();

protected:
    void initializeGL();
    void paintGL();

};

#endif // TRIANGLEGLWIDGET_H
