#include<GL/glut.h>
#include<cmath>
#include<iostream>
using namespace std;

int points[4][2];
int clicks=0;
bool curvedrawn=false;

void drawpoint(GLfloat x, GLfloat y)
{
  glColor3f(1.0,0.0,0.0);
  glPointSize(4.0);
  glBegin(GL_POINTS);
  glVertex2f(x,y);
  glEnd();
  glFlush();
}
void drawline(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2)
{  
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
  glFlush();
}

void midpointsubdivision(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfoat y4)
{
  GLfloat xAB = (x1+x2)/2;
  GLfloat yAB = (y1+y2)/2;
  GLfloat xBC = (x2+x3)/2;
  GLfloat yBC = (y2+y3)/2;
  GLfloat xCD = (x3+x4)/2;
  GLfloat yCD = (y3+y4)/2;
  
  GLfloat xABC = (xAB+xBC)/2;
  GLfloat yABC = (yAB+yBC)/2;
  GLfloat xBCD = (xBC+xCD)/2;
  GLfloat yBCD = (yBC+yCD)/2;
  
  GLfloat xABCD = (xABC+xBCD)/2;
  GLfloat yABCD = (yABC+yBCD)/2;
  
  if(((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))>4||((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2))>4| | ((x4-x3)*(x4-x3)+(y4-y3)*(y4-y3))>4)
  {
    midpointsubdivision(x1, y1, xAB,  yAB, xABC, yABC, xABCD, yABCD);
    midpointsubdivision(xABCD, yABCD, xBCD, yBCD, xCD, yCD, x4, y4);
  }
  else
  {
    drawline(x1, y1, x4, y4);
  }
}


void Init()
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,600,0,600);
}

void display()
{  
  glClear(GL_COLOR_BUFFER_BIT);
  if(curvedrawn)
  {
    for(int i=0; i<4; i++)
    {  drawpoint(points[i][0], points[i][1]);
    }
  }
  glFlush();
}
void mouse(int btn, int state, int x, int y)
{
    if (state == GLUT_DOWN && btn == GLUT_LEFT_BUTTON && clicks < 4)
    {
        points[clicks][0] = x;
        points[clicks][1] = 600 - y;
        drawpoint(x, 600 - y);
        clicks++;

        if (clicks == 4)
        {
            curvedrawn = true;
            for (int i = 0; i < 3; i++)
                drawLine(points[i][0], points[i][1], points[i + 1][0], points[i + 1][1]);

            midpointsubdivision(points[0][0], points[0][1],
                                points[1][0], points[1][1],
                                points[2][0], points[2][1],
                                points[3][0], points[3][1]);
        }
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bezier Curve - Midpoint Subdivision");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}  
  

