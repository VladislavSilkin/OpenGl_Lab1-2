#include "figure.h"

Figure::Figure()
{
    shaderProgram = new QOpenGLShaderProgram();
    z = 1.8;
    r = 0.4;
    R = 0.4;
    frequency = 4;
    x0 = 1.6;
    y0 = 1.6;
    camX = 3.5;
    camY = 3.5;
    camZ = 3.5;
    moveX = 0.0;
    moveY = 0.0;
    moveZ = 0.0;
    xAlpha = 0.0f;
    yAlpha = 0.0f;
    zAlpha = 0.0f;
    xScale = 1.0f;
    yScale = 1.0f;
    zScale = 1.0f;
    depth = false;
    hasAxis = true;
    isOrtho = true;
}

void Figure::initializeGL(){
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(255.0f, 255.0f, 255.0f, 1.0f);
    init();
}

void Figure::resizeGL(int width, int height){
    glViewport(0, 0, (GLint)width, (GLint)height);
}

void Figure::paintGL(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 mProjectionMatrix;
    if(isOrtho){
        mProjectionMatrix.ortho(5, -5, -5, 5, -5, 14);
    }else{
        mProjectionMatrix.frustum(-2, 2, -3, 3, 1.5, 14);
    }

    QMatrix4x4 mViewMatrix;
    mViewMatrix.lookAt({camX, camY, camZ}, {0, 0, 0}, {0, 1, 0});

    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(xAlpha, 1.0f, 0.0f, 0.0f);
    rotationMatrix.rotate(yAlpha, 0.0f, 1.0f, 0.0f);
    rotationMatrix.rotate(zAlpha, 0.0f, 0.0f, 1.0f);

    scaleMatrix.setToIdentity();
    scaleMatrix.scale(xScale, yScale, zScale);

    shaderProgram->setUniformValue("projection", mProjectionMatrix);
    shaderProgram->setUniformValue("view", mViewMatrix);

    QVector<GLfloat> coordsArraySmallCircle(720*3);
    QVector<GLfloat> coordsArrayBigCircle(720*3);
    QVector<GLfloat> blueColors(720*3);
    QVector<QVector<GLfloat>> horRects(100);
    QVector<QVector<GLfloat>> verZRects(100);
    QVector<QVector<GLfloat>> verXRects(100);
    int j = 0;
    for(int alpha = 0; alpha < 720; alpha++){
        blueColors[j] = 1.0;
        blueColors[j+1] = 0.0;
        blueColors[j+2] = 1.0;
        j+=3;
    }
    if(depth){
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    //drawConeCircle(r, z, coordsArraySmallCircle, blueColors);//draw small circle
    //drawConeCircle(R, z - 1, coordsArrayBigCircle, blueColors);//draw big circle
    //drawConeLines();
    int rectYIterator = 0;
    int rectZIterator = 0;
    int rectXIterator = 0;
    if(frequency > 14) {
    drawHorizontalRect(0.2, 0.2, 0, 0, 0, horRects, blueColors, rectYIterator);
    drawHorizontalRect(2, 0.2, 1.8, 0, 0, horRects, blueColors, rectYIterator);
    drawHorizontalRect(0.2, 2, 0, 1.8, 0, horRects, blueColors, rectYIterator);
    drawHorizontalRect(2, 2, 1.8, 1.8, 0, horRects, blueColors, rectYIterator);
    // Нижняя часть ножек стула

    drawVerticalZRect(0.2, 0, 0, 1.5, 0, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 0, 1.8, 1.5, 0, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(0.2, 0, 0, 1.5, 0.2, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 0, 1.8, 1.5, 0.2, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(0.2, 0, 0, 1.5, 1.8, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 0, 1.8, 1.5, 1.8, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(0.2, 0, 0, 1.5, 2, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 0, 1.8, 1.5, 2, verZRects, blueColors, rectZIterator);

    drawVerticalXRect(0, 0, 1.5, 0.2, 0, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(0, 1.8, 1.5, 2, 0, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(0, 0, 1.5, 0.2, 0.2, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(0, 1.8, 1.5, 2, 0.2, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(0, 0, 1.5, 0.2, 1.8, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(0, 1.8, 1.5, 2, 1.8, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(0, 0, 1.5, 0.2, 2, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(0, 1.8, 1.5, 2, 2, verXRects, blueColors, rectXIterator);
    // Ножки стула

    drawHorizontalRect(2, 2, 0, 0, 1.5, horRects, blueColors, rectYIterator);
    drawHorizontalRect(2, 2, 0, 0, 1.6, horRects, blueColors, rectYIterator);

    drawVerticalZRect(2, 1.5, 0, 1.6, 0, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 1.5, 0, 1.6, 2, verZRects, blueColors, rectZIterator);

    drawVerticalXRect(1.5, 0, 1.6, 2, 0, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(1.5, 0, 1.6, 2, 2, verXRects, blueColors, rectXIterator);
    // Седушка стула

    drawVerticalZRect(0.2, 1.6, 0, 2.6, 0, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 1.6, 1.8, 2.6, 0, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(0.2, 1.6, 0, 2.6, 0.2, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 1.6, 1.8, 2.6, 0.2, verZRects, blueColors, rectZIterator);

    drawVerticalXRect(1.6, 0, 2.6, 0.2, 0, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(1.6, 0, 2.6, 0.2, 0.2, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(1.6, 0, 2.6, 0.2, 1.8, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(1.6, 0, 2.6, 0.2, 2, verXRects, blueColors, rectXIterator);
    // Опоры спинки

    drawHorizontalRect(2, 0.2, 0, 0, 2.6, horRects, blueColors, rectYIterator);
    drawHorizontalRect(2, 0.2, 0, 0, 3, horRects, blueColors, rectYIterator);

    drawVerticalZRect(2, 2.6, 0, 3, 0, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 2.6, 0, 3, 0.2, verZRects, blueColors, rectZIterator);

    drawVerticalXRect(2.6, 0, 3, 0.2, 0, verXRects, blueColors, rectXIterator);
    drawVerticalXRect(2.6, 0, 3, 0.2, 2, verXRects, blueColors, rectXIterator);
    // Спинка стула
    } else {
    drawVerticalZRect(0.2, 0, 0, 1.5, 0, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 0, 1.8, 1.5, 0, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(0.2, 0, 0, 1.5, 2, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 0, 1.8, 1.5, 2, verZRects, blueColors, rectZIterator);

    drawHorizontalRect(2, 2, 0, 0, 1.5, horRects, blueColors, rectYIterator);

    drawVerticalZRect(0.2, 1.5, 0, 2.6, 0, verZRects, blueColors, rectZIterator);
    drawVerticalZRect(2, 1.5, 1.8, 2.6, 0, verZRects, blueColors, rectZIterator);

    drawVerticalZRect(2, 2.6, 0, 3, 0, verZRects, blueColors, rectZIterator);
    }
    if(hasAxis){
        drawAxis();//draw axis
    }

    if(depth){
        glDisable(GL_DEPTH_TEST);
    }
}

void Figure::setPoint(float x, float y, float z, QVector<GLfloat>& array, int& iterator){
    QVector4D curCoordinate;
    curCoordinate.setX(x);
    curCoordinate.setY(y);
    curCoordinate.setZ(z);
    curCoordinate.setW(0.0f);
    curCoordinate = rotationMatrix * curCoordinate;
    curCoordinate = scaleMatrix * curCoordinate;
    array[iterator] = curCoordinate.x();
    array[iterator+1] = curCoordinate.y();
    array[iterator+2] = curCoordinate.z();
    iterator += 3;
}

void Figure::drawHorizontalRect(float x1, float z1, float x2, float z2, float y, QVector<QVector<GLfloat>>& arrays, QVector<GLfloat>& colorArray, int& rectIterator){
    QVector<GLfloat> array = arrays[rectIterator];
    array.resize(4*3);
    int iterator = 0;
    setPoint(x1, y, z1, array, iterator);
    setPoint(x1, y, z2, array, iterator);
    setPoint(x2, y, z1, array, iterator);
    setPoint(x2, y, z2, array, iterator);
    glPointSize(2.0f);
    shaderProgram->setAttributeArray("position", array.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorArray.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_LINE_STRIP, 0, 4);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
    arrays[rectIterator] = array;
    rectIterator++;
}

void Figure::drawVerticalZRect(float x1, float y1, float x2, float y2, float z, QVector<QVector<GLfloat>>& arrays, QVector<GLfloat>& colorArray, int& rectIterator){
    QVector<GLfloat> array = arrays[rectIterator];
    array.resize(4*3);
    int iterator = 0;
    setPoint(x1, y1, z, array, iterator);
    setPoint(x2, y1, z, array, iterator);
    setPoint(x1, y2, z, array, iterator);
    setPoint(x2, y2, z, array, iterator);
    glPointSize(2.0f);
    shaderProgram->setAttributeArray("position", array.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorArray.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_LINE_STRIP, 0, 4);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
    arrays[rectIterator] = array;
    rectIterator++;
}

void Figure::drawVerticalXRect(float y1, float z1, float y2, float z2, float x, QVector<QVector<GLfloat>>& arrays, QVector<GLfloat>& colorArray, int& rectIterator){
    QVector<GLfloat> array = arrays[rectIterator];
    array.resize(4*3);
    int iterator = 0;
    setPoint(x, y1, z1, array, iterator);
    setPoint(x, y1, z2, array, iterator);
    setPoint(x, y2, z1, array, iterator);
    setPoint(x, y2, z2, array, iterator);
    glPointSize(2.0f);
    shaderProgram->setAttributeArray("position", array.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorArray.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_LINE_STRIP, 0, 4);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
    arrays[rectIterator] = array;
    rectIterator++;
}

void Figure::drawCircle(float x0, float y0, float r, float z, QVector<GLfloat>& array){
    int i = 0;
    QVector4D curCoordinate;
    for(float alpha = 0; alpha < 360; alpha+=0.5){

        curCoordinate.setX(x0 + r*cos(alpha) + moveX);
        curCoordinate.setY(y0 + r*sin(alpha) + moveY);
        curCoordinate.setZ(z + moveZ);
        curCoordinate.setW(0.0f);
        curCoordinate = rotationMatrix * curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;

        array[i] = curCoordinate.x();
        array[i+1] = curCoordinate.y();
        array[i+2] = curCoordinate.z();
        i+=3;
    }
}

void Figure::drawConeCircle(float radius, float tmpZ, QVector<GLfloat>& array, QVector<GLfloat>& colorArray){
    drawCircle(x0, y0, radius, tmpZ, array);
    glPointSize(2.0f);
    shaderProgram->setAttributeArray("position", array.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorArray.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_POINTS, 0, 720);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
}

void Figure::drawAxis()
{
    GLfloat axes[] = {
        -4, 0, 0,   4, 0, 0,
        0, -4, 0,   0, 4, 0,
        0, 0, -4,   0, 0, 4
    };
    GLfloat colors[] = {
        1, 0, 0,   1, 0, 0,
        0, 1, 0,   0, 1, 0,
        0, 0, 1,   0, 0, 1
    };

    shaderProgram->setAttributeArray("position", axes, 3, 0);
    shaderProgram->setAttributeArray("colors", colors, 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_LINES, 0, 6);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
}

void Figure::drawConeLines()
{
    float step = (360.0/(frequency))*M_PI/180;
    float radius = r;
    float tmpZ = z;
    QVector<GLfloat> coordsConeLines(frequency*6);
    QVector<GLfloat> colorsConeLines(frequency*6);
    QVector4D curCoordinate;
    int j = 0;
    for(int i = 0; i < frequency; i++){
        if(i%2 == 0){
            radius = r;
        }else{
            radius = R;
        }

        curCoordinate.setX(x0+radius*cos(i*step)); //x0+radius*cos(i*step) + moveX
        curCoordinate.setY(y0+radius*sin(i*step)); //y0+radius*sin(i*step) + moveY
        curCoordinate.setZ(tmpZ + moveZ);
        curCoordinate.setW(0.0f);
        curCoordinate = rotationMatrix * curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;

        coordsConeLines[j] = curCoordinate.x();
        coordsConeLines[j+1] = curCoordinate.y();
        coordsConeLines[j+2] = curCoordinate.z();

        if(i%2 == 0){
            radius = R;
            tmpZ = z - 1;
        }else{
            radius = r;
            tmpZ = z;
        }

        curCoordinate.setX(x0+radius*cos((i+1)*step) + moveX);
        curCoordinate.setY(y0+radius*sin((i+1)*step) + moveY);
        curCoordinate.setZ(tmpZ + moveZ);
        curCoordinate.setW(0.0f);
        curCoordinate = rotationMatrix*curCoordinate;
        curCoordinate = scaleMatrix * curCoordinate;

        coordsConeLines[j+3] = curCoordinate.x();
        coordsConeLines[j+4] = curCoordinate.y();
        coordsConeLines[j+5] = curCoordinate.z();

        colorsConeLines[j] = 1.0;
        colorsConeLines[j+1] = 0.0;
        colorsConeLines[j+2] = 1.0;

        colorsConeLines[j+3] = 1.0;
        colorsConeLines[j+4] = 0.0;
        colorsConeLines[j+5] = 1.0;
        j += 6;
    }
    glLineWidth(2.0);
    shaderProgram->setAttributeArray("position", coordsConeLines.cbegin(), 3, 0);
    shaderProgram->setAttributeArray("colors", colorsConeLines.cbegin(), 3, 0);
    shaderProgram->enableAttributeArray("position");
    shaderProgram->enableAttributeArray("colors");
    glDrawArrays(GL_LINES, 0, frequency*2);
    shaderProgram->disableAttributeArray("position");
    shaderProgram->disableAttributeArray("colors");
}

void Figure::init(){
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Vertex, "D:\\Desktop\\lab6\\lab6\\figureShadVert.vert");
    shaderProgram->addShaderFromSourceFile(QOpenGLShader::Fragment, "D:\\Desktop\\lab6\\lab6\\figureShadFrag.frag");
    shaderProgram->link();
    shaderProgram->bind();
}

void Figure::setEnableAxis(bool checkbox){
    hasAxis = checkbox;
    update();
}

void Figure::setDivision(int tmpDivision){
    frequency = tmpDivision;
    update();
}

//void Figure::setSmallRadius(float tmpr){
//    r = tmpr;
//    update();
//}

//void Figure::setBigRadius(double tmpR){
//    R = tmpR;
//    update();
//}

void Figure::setEnableDepth(bool depthCheck)
{
    depth = depthCheck;
    update();
}

void Figure::camXChanged(float camXtmp)
{
    camX = (float)camXtmp;
    update();
}

void Figure::camYChanged(float camYtmp)
{
    camY = (float)camYtmp;
    update();
}

void Figure::camZChanged(float camZtmp)
{
    camZ = camZtmp;
    update();
}

void Figure::setOrthoFrustum(bool tmpOrtho)
{
    isOrtho = tmpOrtho;
    update();
}

void Figure::setXMove(float tmpX){
    moveX = tmpX;
    update();
}

void Figure::setYMove(float tmpY){
    moveY = tmpY;
    update();
}

void Figure::setZMove(float tmpZ){
    moveZ = tmpZ;
    update();
}

void Figure::setXRot(float xalphatmp){
    xAlpha = xalphatmp;
    update();
}

void Figure::setYRot(float yalphatmp){
    yAlpha = yalphatmp;
    update();
}

void Figure::setZRot(float zalphatmp){
    zAlpha = zalphatmp;
    update();
}

void Figure::setXScal(float xScalTmp)
{
    xScale = xScalTmp;
    update();
}

void Figure::setYScal(float yScalTmp)
{
    yScale = yScalTmp;
    update();
}

void Figure::setZScal(float zScalTmp)
{
    zScale = zScalTmp;
    update();
}
