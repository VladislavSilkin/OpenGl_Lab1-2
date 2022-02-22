#include "glscene.h"

glScene::glScene(QWidget *parent)
    : QOpenGLWidget {parent}
{
}

void glScene::initializeGL()
{
  initializeOpenGLFunctions();

}
//------------------------------------------------------------------------------
void glScene::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}
//------------------------------------------------------------------------------
void glScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glBegin(GL_POINT);
      glVertex2i(200,200);
  glEnd();
}
//------------------------------------------------------------------------------
void glScene::paintGL(QString &arg1)
{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    if(arg1 == "GL_POINT") glBegin(GL_POINT);
//    else if(arg1 == "GL_LINES") glBegin(GL_LINES);
//    else if(arg1 == "GL_LINE_STRIP") glBegin(GL_LINE_STRIP);
//    else if(arg1 == "GL_LINE_LOOP") glBegin(GL_LINE_LOOP);

//        glVertex2i(200,200);
//    glEnd();
}
