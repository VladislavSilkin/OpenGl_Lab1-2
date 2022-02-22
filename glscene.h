#ifndef GLSCENE_H
#define GLSCENE_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class glScene : public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT

public:
    glScene(QWidget *parent = nullptr);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void paintGL(QString &arg1);
};

#endif // GLSCENE_H
