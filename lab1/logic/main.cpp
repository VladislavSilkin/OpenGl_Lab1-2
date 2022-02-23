#include <GL/gl.h>
#include <GL/glut.h>

#include <iostream>

int type = 0;
int Width = 800, Height = 800;
const int CubeSize = 200;

void Display(GLvoid){

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if(type == 0){
        int left, right, top, bottom;

        left = (Width - CubeSize)/2;
        right = left + CubeSize;
        bottom = (Height - CubeSize)/2;
        top = bottom + CubeSize;

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3ub(255, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(left, bottom);
        glVertex2f(left, top);
        glVertex2f(right, top);
        glVertex2f(right, bottom);
        glEnd();
    }

    if(type == 1){
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(10);
        glBegin(GL_POINTS);
        glColor3d(1, 0, 0);
        glVertex3d(100, 20, 0);
        glVertex3d(100,50,0);
        glVertex3d(200, 20, 0);
        glVertex3d(200, 50, 0);
        glEnd();
    }
    if(type == 2){
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_LINES);
        glColor3d(1, 0, 0);
        glVertex3d(100, 20, 0);
        glVertex3d(100,50,0);
        glVertex3d(200, 20, 0);
        glVertex3d(200, 50, 0);
        glEnd();
    }

    if(type == 3){
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_LINE_STRIP);
        glColor3d(1, 0, 0);
        glVertex3d(100, 20, 0);
        glVertex3d(100,50,0);
        glVertex3d(200, 20, 0);
        glVertex3d(200, 50, 0);
        glEnd();
    }

    glFinish();
}

void Reshape(GLint width, GLint height){
    Width = width;
    Height = height;

    glViewport(0, 0, Width, Height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Keyboard(unsigned char key, int w, int h){
#define ESC '\033'
    if(key == ESC)
        std::exit(0);
}

void specialKeyboard(int key, int x, int y){
    switch(key){
    case GLUT_KEY_F1:
        type = 1;
        break;
    case GLUT_KEY_F2:
        type = 2;
        break;
    case GLUT_KEY_F3:
        type = 3;
        break;
    case GLUT_KEY_F4:
        type = 3;
        break;
    }
    Display();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(Width, Height);
    glutCreateWindow("lab1");

    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(specialKeyboard);

    glutMainLoop();
}
