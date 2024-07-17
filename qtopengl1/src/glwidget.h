#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGlWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QObject *parent = 0);


};

#endif // GLWIDGET_H
