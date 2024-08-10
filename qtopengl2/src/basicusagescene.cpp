#include "basicusagescene.h"
#include "glassert.h"

#include <QObject>
#include <QOpenGLContext>

BasicUsageScene::BasicUsageScene() : mShaderProgram(),
    mVertexPositionBuffer(QOpenGLBuffer::VertexBuffer),
    mVertexColorBuffer(QOpenGLBuffer::VertexBuffer)
{
}

void BasicUsageScene::initialize() {
    prepareShaderProgram();
    prepareVertexBuffers();
}

void BasicUsageScene::update(float t)
{
    Q_UNUSED(t);
}

void BasicUsageScene::render()
{
   // glAssert(glClear(GL_COLOR_BUFFER_BIT));
    mShaderProgram.bind();
   mVAO.bind();
   // glAssert("afasdfas");
   // glAssert( glDrawArrays(GL_TRIANGLES, 0, 3) );

}

void BasicUsageScene::resize(int width, int height)
{
    glViewport(0,0,width,height);
}

void BasicUsageScene::prepareShaderProgram()
{

}

void BasicUsageScene::prepareVertexBuffers()
{

}






