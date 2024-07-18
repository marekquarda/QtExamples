#include "triangleglwidget.h"

TriangleGLWidget::TriangleGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

TriangleGLWidget::~TriangleGLWidget()
{
}

void TriangleGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // Clear to cyan
    glClearColor(0,0,0,0);
}

void TriangleGLWidget::paintGL()
{
    /// Set every pixel in the frame buffer to the current clear color
    glClear(GL_COLOR_BUFFER_BIT);

    qDebug("Repainting opengl");

    // Draw triangles
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f,0.0f,0.0f);  // red
        glVertex3f(0.0f,0.707f,0.0f);

        glColor3f(0.0f,1.0f,0.0f);  // green
        glVertex3f(-0.5f,-0.5f,0.0f);

        glColor3f(0.0f,0.0f,1.0f);  // blue
        glVertex3f(0.5f,-0.5f,0.0f);
    glEnd();
}
