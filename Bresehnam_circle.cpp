#include<iostream>
#include<cmath>
#include<GL/glut.h>
using namespace std;

int choice =0;
void MyInit()
{
  glClearColor(1.0,1.0,1.0,1.0);
  glPointSize(5.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-640.0, 640.0, -480.0, 480.0);
}

void DrawAxes(){
    for(int i=-640;i<640;i++){
        glBegin(GL_POINTS);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2i(i,0);
        glEnd();
    }
    for(int i=-480;i<480;i++){
        glBegin(GL_POINTS);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2i(0,i);
        glEnd();
    }
    glFlush();
}


void BresenhamCircle(int rad, int h, int k)
{
  int x=0, y=rad;
  int d= 3-2*rad;
  glBegin(GL_POINTS);
  glVertex2i(x, y);
  glEnd();
  while(x<=y)
  {
    if(d<=0)
    {
      d=d+4*x+6;
    }
    else
    {
      d=d+4*(x-y)+10;
      y--;
    }
    x++;
    glBegin(GL_POINTS);
    glVertex2i(x+h, y+k);
    glVertex2i(-x+h, y+k);
    glVertex2i(x+h, -y+k);
    glVertex2i(-x+h, -y+k);
    glVertex2i(y+h, x+k);
    glVertex2i(-y+h, x+k);
    glVertex2i(y+h, -x+k);
    glVertex2i(-y+h, -x+k);
    glEnd();
  }
  glFlush();
}

void spiral(int maxrad, int h, int k, int noturns)
{
  float anglestep = 0.05f;
  float radiusstep = 0.1f;
  float theta = 0.0f;
  float r = 0.0f;
  
  glBegin(GL_LINE_STRIP);
  while(r<=maxrad)
  {
    int x = static_cast<int>(r*cos(theta))+h;
    int y = static_cast<int>(r*sin(theta))+k;
    
    glVertex2i(x, y);
    theta+=anglestep;
    r+=radiusstep;
  }
  glEnd();
  glFlush();
}
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  DrawAxes();
  switch(choice)
  {
    case 1:
    glColor3f(1.0,0.0,0.0);
    BresenhamCircle(100, -200, 200);
    break;
    case 2:
    glColor3f(1.0,0.0,0.0);
    BresenhamCircle(75, 550, 250);
    glColor3f(0.0,0.0,0.0);
    BresenhamCircle(75, 380, 250);
    glColor3f(0.0, 0.5, 1.0);
    BresenhamCircle(75, 210, 250);
    glColor3f(0.9, 0.72,0.0);
    BresenhamCircle(75, 295, 175);
    glColor3f(0.0,1.0,0.0);
    BresenhamCircle(75, 465, 175);
    break;
    case 3:
    BresenhamCircle(100, -200, -200);
    BresenhamCircle(80, -200, -200);
    BresenhamCircle(60, -200, -200);
    BresenhamCircle(40, -200, -200);
    break;
    case 4:
    glColor3f(0.0,0.0,1.0);
    spiral(150, 0,0, 5);
    break;
    case 5:
    glColor3f(0.0,0.0,0.0);
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2f(150, -258);
    glVertex2f(310, -258);
    glVertex2f(310, -258);
  
    glVertex2f(230, (int)(-1*sqrt(3)*(310-150)/2)+22);
    glVertex2f(230, (int)(-1*sqrt(3)*(310-150)/2)+22);
      glVertex2f(150, -258);
    glEnd();	
    BresenhamCircle(((int)((310-150)/sqrt(3))), 230,(int)((-1.5*sqrt(3)*(310-150)/2)));
    BresenhamCircle(((int)((310-150)/(2*sqrt(3)))), 230,(int)((-1.5*sqrt(3)*(310-150)/2)));
    break;
  }
}
         
void Menu(int option)
{
  switch(option)
  {
    case 1:
    choice=1;
    break;
    case 2:
    choice =2;
    break;
    case 3:
    choice =3;
    break;
    case 4:
    choice =4;
    break;
    case 5:
    choice =5;
    break;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("BRESENHAM CIRCLE");
  glutCreateMenu(Menu);
  glutAddMenuEntry("Bresenhamcircle",1);
  glutAddMenuEntry("olympic ring",2);
  glutAddMenuEntry("concentric circle",3);
  glutAddMenuEntry("spiral",4);
  glutAddMenuEntry("pattern", 5);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutDisplayFunc(display);
  MyInit();
  glutMainLoop();
  return 0;
}

    
    
      
      
  
  
