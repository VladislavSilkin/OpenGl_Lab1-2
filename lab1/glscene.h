#ifndef GLSCENE_H
#define GLSCENE_H

#include <QOpenGLWidget>
#include <iostream>
#include <string>

class glScene : public QOpenGLWidget
{
    Q_OBJECT
    GLenum GLType;
    GLenum alphaFunction;
    float alphaRefValue;
    GLenum sfactor;
    GLenum dfactor;
    float xLb, yLb;
    float heightLb, widthLb;
    bool alphaFlag;
    bool scissorFlag;
    bool blendFlag;

public:
    glScene(QWidget *parent = nullptr);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void drawTriangles();
    void drawLines();
    void setVariable();

public slots:
    void slot(int);
    void alphaChooseSlot(int);
    void alphaRefSlot(int);
    void sfactorSlot(int);
    void dfactorSlot(int);
    void xSlot(int);
    void ySlot(int);
    void heightSlot(int);
    void widthSlot(int);
};

#endif // GLSCENE_H
