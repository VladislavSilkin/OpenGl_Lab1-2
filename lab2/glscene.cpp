#include "glscene.h"

glScene::glScene(QWidget *parent)
    : QOpenGLWidget (parent)
{
    GLType = GL_TRIANGLES;
    alphaFunction = GL_ALWAYS;
    alphaRefValue = 0;
    xLb = 0;
    yLb = 0;
    widthLb = 0;
    heightLb = 0;
    sfactor = GL_ZERO;
    dfactor = GL_ZERO;
}

void glScene::initializeGL()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//------------------------------------------------------------------------------
void glScene::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -1.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//------------------------------------------------------------------------------
void glScene::paintGL()
{  
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glEnable(GL_ALPHA_TEST);
    glEnable(GL_SCISSOR_TEST);
    glEnable(GL_BLEND);

    glAlphaFunc(alphaFunction, alphaRefValue);
    glBlendFunc(sfactor, dfactor);
    glScissor(xLb, yLb, widthLb, heightLb);

    glBegin(GLType);
    glColor4f(1.0f, 0.0f, 0.0f, 0.25f);         glVertex2f(25.0f, 50.0f);
    glColor4f(0.0f, 1.0f, 0.0f, 0.5f);         glVertex2f(75.0f, 50.0f);
    glColor4f(0.0f, 0.0f, 1.0f, 0.75f);         glVertex2f(50.0f, 75.0f);
    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);         glVertex2f(50.0f, 25.0f);
    glEnd();


    glDisable(GL_ALPHA_TEST);
    glDisable(GL_SCISSOR_TEST);
    glDisable(GL_BLEND);
}

void glScene::slot(int id)
{
    if(id == 0)
        GLType = GL_TRIANGLES;
    if(id == 1)
        GLType = GL_LINES;
    if(id == 2)
        GLType = GL_LINE_STRIP;
    if(id == 3)
        GLType = GL_TRIANGLE_STRIP;
    this->update();
}

void glScene::alphaChooseSlot(int id){
    if(id == 0)
        this->alphaFunction = GL_ALWAYS;
    if(id == 1)
        this->alphaFunction = GL_LESS;
    if(id == 2)
        this->alphaFunction = GL_EQUAL;
    if(id == 3)
        this->alphaFunction = GL_LEQUAL;
    if(id == 4)
        this->alphaFunction = GL_GREATER;
    if(id == 5)
        this->alphaFunction = GL_NOTEQUAL;
    if(id == 6)
        this->alphaFunction = GL_GEQUAL;
    if(id == 7)
        this->alphaFunction = GL_NEVER;
    this->update();
}

void glScene::alphaRefSlot(int id){
    this->alphaRefValue = id/50.0f;
    if(this->alphaRefValue > 1)
        this->alphaRefValue = 1.0f;
    this->update();
}

void glScene::sfactorSlot(int id){
    if(id == 0)
        sfactor = GL_ZERO;
    if(id == 1)
        sfactor = GL_ONE;
    if(id == 2)
        sfactor = GL_DST_COLOR;
    if(id == 3)
        sfactor = GL_ONE_MINUS_DST_COLOR;
    if(id == 4)
        sfactor = GL_SRC_ALPHA;
    if(id == 5)
        sfactor = GL_ONE_MINUS_SRC_ALPHA;
    if(id == 6)
        sfactor = GL_DST_ALPHA;
    if(id == 7)
        sfactor = GL_ONE_MINUS_DST_ALPHA;
    if(id == 8)
        sfactor = GL_SRC_ALPHA_SATURATE;
    this->update();
}

void glScene::dfactorSlot(int id){
    if(id == 0)
        dfactor = GL_ZERO;
    if(id == 1)
        dfactor = GL_ONE;
    if(id == 2)
        dfactor = GL_SRC_COLOR;
    if(id == 3)
        dfactor = GL_ONE_MINUS_SRC_COLOR;
    if(id == 4)
        dfactor = GL_SRC_ALPHA;
    if(id == 5)
        dfactor = GL_ONE_MINUS_SRC_ALPHA;
    if(id == 6)
        dfactor = GL_DST_ALPHA;
    if(id == 7)
        dfactor = GL_ONE_MINUS_DST_ALPHA;
    this->update();
}

void glScene::xSlot(int _x){
    this->xLb = _x;
    this->update();
}

void glScene::ySlot(int _y){
    this->yLb = _y;
    this->update();
}

void glScene::heightSlot(int _h){
    this->heightLb = _h;
    this->update();
}

void glScene::widthSlot(int _w){
    this->widthLb = _w;
    this->update();
}
