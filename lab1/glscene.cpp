#include "glscene.h"

glScene::glScene(QWidget *parent)
    : QOpenGLWidget (parent)
{
    GLType = 0;
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
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (GLType == 0)
      glBegin(GL_TRIANGLES);
  else if (GLType == 1)
      glBegin(GL_LINES);
  else if (GLType == 2)
      glBegin(GL_LINE_STRIP);
  else if (GLType == 3)
      glBegin(GL_TRIANGLE_STRIP);
  else std::cout << "Error in GLType";

    glColor3d(1, 0, 0);         glVertex2d(-0.75, 0);
    glColor3d(0, 1, 0);         glVertex2d(0.75, 0);
    glColor3d(0, 0, 1);         glVertex2d(0, 0.75);
    glColor3d(0.5, 0.5, 0.5);   glVertex2d(0, -0.75);
    glEnd();
}

void glScene::slot(int id)
{
    this->GLType = id;
    this->update();
}

