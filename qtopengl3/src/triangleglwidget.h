#ifndef TRIANGLEGLWIDGET_H
#define TRIANGLEGLWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class TriangleGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    TriangleGLWidget(QWidget *parent = nullptr);
    ~TriangleGLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;

};

#endif // TRIANGLEGLWIDGET_H
