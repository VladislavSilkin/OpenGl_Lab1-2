#include "glscene.h"

glscene::glscene(QWidget *parent) : QOpenGLWidget (parent)
{
}

void glscene::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void glscene::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void glscene::paintGL()
{
    glClearColor(1.f, 1.f, 1.f, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::pair<double,double> dot1 = std::make_pair(25.0f, 50.0f);
    std::pair<double,double> dot2 = std::make_pair(75.0f, 50.0f);
    triangle triag(dot1, dot2);
//    triag.rotate(-M_PI / 2);

    int times = 30;
    float size = 0.9;
    float rotation = -M_PI / 52;

    glPointSize(10.0f);
    for(int i = 0; i < times; i++) {

        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);        glVertex2f(triag.dots[0].first, triag.dots[0].second);
        glColor3f(0.0f, 0.0f, 0.0f);        glVertex2f(triag.dots[1].first, triag.dots[1].second);
        glColor3f(0.0f, 0.0f, 0.0f);        glVertex2f(triag.dots[2].first, triag.dots[2].second);
        glEnd();

        triag.rotate(rotation);
        triag.resize(size);
    }
}
