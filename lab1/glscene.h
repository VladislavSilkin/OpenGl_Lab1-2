#ifndef GLSCENE_H
#define GLSCENE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <iostream>

class glScene : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
    int GLType;
public:
    glScene(QWidget *parent = nullptr);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

public slots:
    void slot(int);
};

#endif // GLSCENE_H
