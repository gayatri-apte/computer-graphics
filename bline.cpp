#include<iostream>
#include<GL/glut.h>
#include<cmath>
using namespace std;

int choice =0;
void MyInit()
{
  glClearColor(1.0,1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-640.0, 640.0, -360.0, 360.0);
}

int sign(int x, int y)
{
  if(x-y<0)
  {
    return -1;
  }
  return 1;
}

void BresenhamLine(int x1, int y1, int x2, int y2)
{
  if(x1==x2 && y1==y2)
  {
    glColor3f(0.0,0.0,0.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
    cout<<"Error: Origin and Destination are the same.";
    return;
  }
  int x= x1, y= y1;
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int s1 = (x2>x1)?1:-1;
  int s2 = (y2>y1)?1:-1;
  int interchange =0;
  if(dy>dx)
  {
    int temp=dx;
    dx = dy; 
    dy = temp;
    interchange = 1;
  }
 int e = 2*dy - dx;
 glPointSize(2.0);
 for(int i=0; i<=dx; i++)
 {
   glBegin(GL_POINTS);
   glColor3f(0.0,0.0,0.0);
   glVertex2f(x, y);
   glEnd();
   
   while(e>=0)
   {
     if(interchange == 1)
     {
       x+=s1;
     }
     else
     {
      y+=s2;
    }
    e-=2*dx;
  }
  if(interchange == 1)
  {
    y+=s2;
  }else
  {
  x+=s1;
  }
  e+=2*dy;
}
glFlush();
}

void DottedLine(int x1, int y1, int x2, int y2)
{
  if(x1==x2 && y1==y2)
  {
    glColor3f(0.0,0.0,0.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
    cout<<"Error: Origin and Destination are the same.";
    return;
  }
  int x= x1, y= y1;
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int s1 = (x2>x1)?1:-1;
  int s2 = (y2>y1)?1:-1;
  int interchange =0;
  if(dy>dx)
  {
    int temp=dx;
    dx = dy; 
    dy = temp;
    interchange = 1;
  }
 int e = 2*dy - dx;
 glPointSize(2.0);
 for(int i=0; i<=dx; i++)
 {
   glBegin(GL_POINTS);
   if(i%2==0)
   {
     glColor3f(0.0,0.0,0.0);
   }
   else
   {
     glColor3f(1.0,1.0,1.0);
   }
   glVertex2i(x, y);
   glEnd();
   
   while(e>=0)
   {
     if(interchange == 1)
     {
       x+=s1;
     }
     else
     {
      y+=s2;
    }
    e-=2*dx;
  }
  if(interchange == 1)
  {
    y+=s2;
  }else
  {
  x+=s1;
  }
  e+=2*dy;
}
glFlush();
}

void DashedLine(int x1, int y1, int x2, int y2)
{
  if(x1==x2 && y1==y2)
  {
    glColor3f(0.0,0.0,0.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
    cout<<"Error: Origin and Destination are the same.";
    return;
  }
  int x= x1, y= y1;
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int s1 = (x2>x1)?1:-1;
  int s2 = (y2>y1)?1:-1;
  int interchange =0;
  if(dy>dx)
  {
    int temp=dx;
    dx = dy; 
    dy = temp;
    interchange = 1;
  }
 int e = 2*dy - dx;
 glPointSize(2.0);
 for(int i=0; i<=dx; i++)
 {
   glBegin(GL_POINTS);
   if(i%10<5)
   {
     glColor3f(0.0,0.0,0.0);
     glVertex2i(x, y);
   }
   else
   {
     glColor3f(1.0,1.0,1.0);
     glVertex2i(x, y);
   }
   glEnd();
   
   while(e>=0)
   {
     if(interchange == 1)
     {
       x+=s1;
     }
     else
     {
      y+=s2;
    }
    e-=2*dx;
  }
  if(interchange == 1)
  {
    y+=s2;
  }else
  {
  x+=s1;
  }
  e+=2*dy;
}
glFlush();
}


void CenterDottedLine(int x1, int y1, int x2, int y2)
{
  if(x1==x2 && y1==y2)
  {
    glColor3f(0.0,0.0,0.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
    cout<<"Error: Origin and Destination are the same.";
    return;
  }
  int x= x1, y= y1;
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int s1 = (x2>x1)?1:-1;
  int s2 = (y2>y1)?1:-1;
  int interchange =0;
  if(dy>dx)
  {
    int temp=dx;
    dx = dy; 
    dy = temp;
    interchange = 1;
  }
 int e = 2*dy - dx;
 glPointSize(2.0);
 for(int i=0; i<=dx; i++)
 {
   glBegin(GL_POINTS);
   if(i%10<5|| i%10 ==7)
   {
     glColor3f(0.0,0.0,0.0);
     glVertex2i(x, y);
   }
   else
   {
     glColor3f(1.0,1.0,1.0);
     glVertex2i(x, y);
   }
   glEnd();
   
   while(e>=0)
   {
     if(interchange == 1)
     {
       x+=s1;
     }
     else
     {
      y+=s2;
    }
    e-=2*dx;
  }
  if(interchange == 1)
  {
    y+=s2;
  }else
  {
  x+=s1;
  }
  e+=2*dy;
}
glFlush();
}


void SolidLine(int x1, int y1, int x2, int y2)
{
  if(x1==x2 && y1==y2)
  {
    glColor3f(0.0,0.0,0.0);
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glVertex2i(x1, y1);
    glEnd();
    glFlush();
    cout<<"Error: Origin and Destination are the same.";
    return;
  }
  int x= x1, y= y1;
  int dx = abs(x2 - x1);
  int dy = abs(y2 - y1);
  int s1 = (x2>x1)?1:-1;
  int s2 = (y2>y1)?1:-1;
  int interchange =0;
  if(dy>dx)
  {
    int temp=dx;
    dx = dy; 
    dy = temp;
    interchange = 1;
  }
 int e = 2*dy - dx;
 glPointSize(5.0);
 for(int i=0; i<=dx; i++)
 {
   glBegin(GL_POINTS);
   glColor3f(0.0,0.0,0.0);
   glVertex2f(x, y);
   glEnd();
   
   while(e>=0)
   {
     if(interchange == 1)
     {
       x+=s1;
     }
     else
     {
      y+=s2;
    }
    e-=2*dx;
  }
  if(interchange == 1)
  {
    y+=s2;
  }else
  {
  x+=s1;
  }
  e+=2*dy;
}
glFlush();
}

void PlotAxes()
{
  BresenhamLine(-640.0,0.0, 640.0, 0.0);
  BresenhamLine(0.0, -360.0, 0.0, 360.0);
}


void display() {
glClear(GL_COLOR_BUFFER_BIT);
PlotAxes();
switch(choice){
    case 1:
    BresenhamLine(-100, 50, -100, 150);
    break;
    case 2:
    DottedLine(-200, 250, -100, 250);
    break;
    case 3:
    DashedLine(-250, -50, -50, -25);
    break;
    case 4:
    SolidLine(50, -150, 250, -150);
    break;
    case 5:
    CenterDottedLine(50, -50, 250, -250);
    break;
    case 6:
    //pattern starts here
BresenhamLine(160,300,560,300);
BresenhamLine(160,100,560,100);
BresenhamLine(160,100,160,300);
BresenhamLine(560,100,560,300);//square outer ends here
BresenhamLine(160,200,360,300);
BresenhamLine(360,300,560,200);
BresenhamLine(160,200,360,100);
BresenhamLine(360,100,560,200);//inner diamond ends here
BresenhamLine(260,250,460,250);
BresenhamLine(260,150,460,150);
BresenhamLine(260,150,260,250);
BresenhamLine(460,150,460,250);//square inner ends here


  break;
  case 7:
  BresenhamLine(50,100,50, 150);
  BresenhamLine(50,150, 100, 150);
  BresenhamLine(100, 150, 100,100);
  
 // BresenhamLine(100, 50,150, 0);
  BresenhamLine(100, 100,150, 100);
  BresenhamLine(150, 100, 150, 150);
  
  BresenhamLine(150, 150,200, 150);
  BresenhamLine(200, 150, 200, 100);
  break;
  case 8:
  //BresenhamLine(50, 50, 175, 100);
  //BresenhamLine(175, 100, 100, 50);
 // BresenhamLine(100, 50, 125, 100);
  //BresenhamLine(125, 100, 150, 50);
  BresenhamLine(50, 50, 75, 100);   // up
BresenhamLine(75, 100, 100, 50);  // down
BresenhamLine(100, 50, 125, 100); // up
BresenhamLine(125, 100, 150, 50); // down

  break;
  
   }
glutSwapBuffers();
}

void Menu(int option)
{
  switch(option)
  {    case 1:
        choice = 1;
        break;
      case 2:
        choice = 2;
        break;
      case 3:
        choice =3;
        break;
      case 4:
        choice=4;
        break;
      case 5:
       choice=5;
        break;
      case 6:
        choice=6;
        break;
        case 7:
        choice =7;
        break;
        case 8:
        choice=8;
        break; 
    }
}

int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowSize(1280, 720);
glutCreateWindow("Bresenham Line Drawing");
MyInit();
glutCreateMenu(Menu);
glutAddMenuEntry("Bresenham Line", 1);
glutAddMenuEntry("Dotted Bresenham Line", 2);
glutAddMenuEntry("Dashed Bresenham Line", 3);
glutAddMenuEntry("Solid Bresenham Line", 4);
glutAddMenuEntry("Centre Dotted Bresenham Line", 5);
glutAddMenuEntry("Pattern", 6);
glutAddMenuEntry("Square wave", 7);
glutAddMenuEntry("Triangular wave",8);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutDisplayFunc(display);
glutMainLoop();
return 0;
}

    


  




  
    
    
   
 
  
    	
  

