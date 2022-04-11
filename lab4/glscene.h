#ifndef GLSCENE_H
#define GLSCENE_H

#include <QOpenGLWidget>
#include <iostream>

#include "triangle.h"
class glScene : public QOpenGLWidget
{
    Q_OBJECT
public:
    glScene(QWidget* parent = nullptr);
    std::vector<std::pair<double, double>> getHexagonCoords(std::pair<double, double> dot1, std::pair<double, double> dot3, std::pair<double, double> dot5, double radius);
    std::vector<std::pair<double, double>> getRotateMatrix(int angle);
    std::pair<double, double> getNewCoords(std::vector<std::pair<double, double>> rotateMatrix, std::pair<double, double> oldCoords, std::pair<double, double> point);
    void drawFractal(std::pair<double, double> point2, double radius, int level, double angle);
    void drawTriangle(std::pair<double, double> point2, double radius, double angle);
protected:
    void initializeGL() override;
    void resizeGL(int _x, int _y) override;
    void paintGL() override;
public slots:
    void levelUp();
    void levelDown();
private:
    int height, width;
    int level;
    bool firstStart;
};

#endif // GLSCENE_H
