#include "glscene.h"

glScene::glScene(QWidget* parent)
    : QOpenGLWidget(parent){
    this->height = 860;
    this->width = 900;
    this->level = 0;
    firstStart = false;
}

void glScene::initializeGL(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width, 0, this->height, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void glScene::resizeGL(int _x, int _y){
    glViewport(0, 0, _x, _y);
    this->width = _x;
    this->height = _y;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, (float)_x, 0, (float)_y, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void glScene::paintGL(){
    glClearColor(1, 1, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw inner triangle
    int centerX = this->width/2;
    int centerY = this->height/2;

    std::pair<double,double> dot1 = std::make_pair(centerX*2/3, centerY);
    std::pair<double,double> dot2 = std::make_pair(centerX*4/3, centerY);
    triangle triag(dot1, dot2);

    double side = (dot2.first - dot1.first)/2;
    double radius = side/cos(30 * M_PI/180);
    std::vector<std::pair<double, double>> hexagon = getHexagonCoords(triag.dots[0], triag.dots[1], triag.dots[2], radius);

    int times = 30;
    float size = 0.9;
    float rotation = -M_PI / 52;
    if(level > 0){
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
    else
        return;

    if(level > 1){
    for(int i = 0; i < 5; i++){
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(hexagon[i].first, hexagon[i].second);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(hexagon[i+1].first, hexagon[i+1].second);
        glEnd();
    }
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(hexagon[5].first, hexagon[5].second);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(hexagon[0].first, hexagon[0].second);
    glEnd();
    }
    else return;

    if(level > 2){
    drawFractal(hexagon[4], radius, 0, 30);
    drawFractal(hexagon[5], radius, 0, 90);
    drawFractal(hexagon[0], radius, 0, 150);
    drawFractal(hexagon[1], radius, 0, 210);
    drawFractal(hexagon[2], radius, 0, 270);
    drawFractal(hexagon[3], radius, 0, 330);
    }
    else return;
}

std::vector<std::pair<double, double>> glScene::getHexagonCoords(std::pair<double, double> dot1, std::pair<double, double> dot3, std::pair<double, double> dot5, double radius){
    std::vector<std::pair<double, double>> returnVector;
    std::pair<double, double> tempDot;

    returnVector.push_back(dot1);

    tempDot.first = dot1.first + (dot3.first - dot1.first)/2;
    tempDot.second = dot1.second - sin(30 * M_PI/180) * radius;
    returnVector.push_back(tempDot);

    returnVector.push_back(dot3);

    tempDot.first = dot3.first;
    tempDot.second = dot3.second + radius;
    returnVector.push_back(tempDot);

    returnVector.push_back(dot5);

    tempDot.first = dot1.first;
    tempDot.second = dot1.second + radius;
    returnVector.push_back(tempDot);

    return returnVector;
}

std::vector<std::pair<double, double>> glScene::getRotateMatrix(int angle){
    std::vector<std::pair<double, double>> returnMatrix;
    std::pair<double, double> tempLine;

    tempLine.first = cos(angle * M_PI/180);
    tempLine.second = -sin(angle * M_PI/180);
    returnMatrix.push_back(tempLine);

    tempLine.first = sin(angle * M_PI/180);
    tempLine.second = cos(angle * M_PI/180);
    returnMatrix.push_back(tempLine);

    return returnMatrix;
}

std::pair<double, double> glScene::getNewCoords(std::vector<std::pair<double, double>> rotateMatrix, std::pair<double, double> oldCoords, std::pair<double, double> point){
    std::pair<double, double> returnCoords;

    returnCoords.first = rotateMatrix[0].first * (oldCoords.first - point.first) + rotateMatrix[0].second * (oldCoords.second - point.second);
    returnCoords.second = rotateMatrix[1].first * (oldCoords.first - point.first) + rotateMatrix[1].second * (oldCoords.second - point.second);

    returnCoords.first += point.first;
    returnCoords.second += point.second;

    return returnCoords;
}

void glScene::drawFractal(std::pair<double, double> point2, double radius, int level, double angle){
    if(level == 3)
        return;
    triangle triag(std::make_pair(point2.first-radius, point2.second), point2);

    double side = radius/2;
    double hexagonRadius = side/cos(30 * M_PI/180);
    std::vector<std::pair<double, double>> hexagon = getHexagonCoords(triag.dots[0], triag.dots[1], triag.dots[2], hexagonRadius);

    int times = 30;
    float size = 0.9;
    float rotation = -M_PI / 52;

    glPointSize(10.0f);
    triangle rotateTriangle;
    std::vector<std::pair<double, double>> rotateMatrix = getRotateMatrix(angle);

    for(int i = 0; i < times; i++) {
        rotateTriangle.dots[0] = getNewCoords(rotateMatrix, triag.dots[0], point2);
        rotateTriangle.dots[1] = getNewCoords(rotateMatrix, triag.dots[1], point2);
        rotateTriangle.dots[2] = getNewCoords(rotateMatrix, triag.dots[2], point2);
        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);        glVertex2f(rotateTriangle.dots[0].first, rotateTriangle.dots[0].second);
        glColor3f(0.0f, 0.0f, 0.0f);        glVertex2f(rotateTriangle.dots[1].first, rotateTriangle.dots[1].second);
        glColor3f(0.0f, 0.0f, 0.0f);        glVertex2f(rotateTriangle.dots[2].first, rotateTriangle.dots[2].second);
        glEnd();

        triag.rotate(rotation);
        triag.resize(size);
    }

    for(int i = 0; i < 6; i++){
        hexagon[i] = getNewCoords(rotateMatrix, hexagon[i], point2);
    }

    if((this->level > 3 && level == 0) || (this->level != 5 && level == 1)){
    for(int i = 2; i < 5; i++){
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(hexagon[i].first, hexagon[i].second);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(hexagon[i+1].first, hexagon[i+1].second);
        glEnd();
    }
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(hexagon[5].first, hexagon[5].second);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(hexagon[0].first, hexagon[0].second);
    glEnd();
    }
    else return;

    if(this->level > 4 && level == 0){
        drawTriangle(hexagon[2], hexagonRadius, angle-90);
        drawFractal(hexagon[4], hexagonRadius, level+1, angle+30);
        drawFractal(hexagon[3], hexagonRadius, level+1, angle-30);
    }
    if(this->level > 6 && level == 1){
        drawTriangle(hexagon[2], hexagonRadius, angle-90);
        drawTriangle(hexagon[3], hexagonRadius, angle-30);
        drawTriangle(hexagon[4], hexagonRadius, angle+30);
        drawTriangle(hexagon[5], hexagonRadius, angle+90);
    }
}

void glScene::drawTriangle(std::pair<double, double> point2, double radius, double angle){
    triangle triag(std::make_pair(point2.first-radius, point2.second), point2);
    int times = 30;
    float size = 0.9;
    float rotation = -M_PI / 52;


    glPointSize(10.0f);
    triangle rotateTriangle;
    std::vector<std::pair<double, double>> rotateMatrix = getRotateMatrix(angle);
    for(int i = 0; i < times; i++) {
        rotateTriangle.dots[0] = getNewCoords(rotateMatrix, triag.dots[0], point2);
        rotateTriangle.dots[1] = getNewCoords(rotateMatrix, triag.dots[1], point2);
        rotateTriangle.dots[2] = getNewCoords(rotateMatrix, triag.dots[2], point2);
        glBegin(GL_LINE_LOOP);
        glColor3f(0.0f, 0.0f, 0.0f);        glVertex2f(rotateTriangle.dots[0].first, rotateTriangle.dots[0].second);
        glColor3f(0.0f, 0.0f, 0.0f);        glVertex2f(rotateTriangle.dots[1].first, rotateTriangle.dots[1].second);
        glColor3f(0.0f, 0.0f, 0.0f);        glVertex2f(rotateTriangle.dots[2].first, rotateTriangle.dots[2].second);
        glEnd();

        triag.rotate(rotation);
        triag.resize(size);
    }
}

void glScene::levelUp(){
    if(level == 7)
        return;
    level++;
    this->update();
}

void glScene::levelDown(){
    if(level == 0)
        return;
    level--;
    this->update();
}
