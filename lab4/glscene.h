#ifndef GLSCENE_H
#define GLSCENE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "triangle.h"
#include <utility>
#include <cmath>

class glscene : public QOpenGLWidget
{
    Q_OBJECT
public:
    glscene(QWidget *parent = nullptr);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // GLSCENE_H
