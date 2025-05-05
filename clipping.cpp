#include<GL/glut.h>
#include<stdio.h>
#include<vector>

#define LEFT 0
#define RIGHT 1
#define BOTTOM 3
#define TOP 4

using namespace std;

float xmin = -100, ymin = -100, xmax = 100, ymax = 100;
bool clippedFlag = false;

struct point
{ 
   float x, y;
};

vector<point> polygon;
vector<point> clipped;

// Function to draw a polygon from given set of points
void drawPolygon(const vector<point>& poly)
{
  glBegin(GL_LINE_LOOP);
  for(auto p : poly)
    glVertex2f(p.x, p.y);
  glEnd();
}

// Function to compute intersection point with a clipping edge
point intersect(point a, point b, int edge)
{
    point p;
    float m = (b.x - a.x != 0) ? (b.y - a.y) / (b.x - a.x) : 0;
    switch(edge)
    {
      case LEFT:
        p.x = xmin;
        p.y = a.y + m * (xmin - a.x);
        break;
      case RIGHT:
        p.x = xmax;
        p.y = a.y + m * (xmax - a.x);
        break;
      case BOTTOM:
        p.y = ymin;
        p.x = (m != 0) ? a.x + (ymin - a.y) / m : a.x;
        break;
      case TOP:
        p.y = ymax;
        p.x = (m != 0) ? a.x + (ymax - a.y) / m : a.x;
        break;
    }
    return p;
}

// Function to check if point is inside the clipping boundary
bool inside(point p, int edge)
{
    switch(edge)
    {
      case LEFT: return p.x >= xmin;
      case RIGHT: return p.x <= xmax;
      case BOTTOM: return p.y >= ymin;
      case TOP: return p.y <= ymax;
    }
    return true;
}

// Function to clip polygon against a single edge
void clipEdge(int edge)
{
    vector<point> input = clipped;
    clipped.clear();
   
    for(size_t i = 0; i < input.size(); i++)
    {
        point curr = input[i];
        point prev = input[(i + input.size() - 1) % input.size()];
        bool currIn = inside(curr, edge);
        bool prevIn = inside(prev, edge);
     
        if(prevIn && currIn)
        {
            clipped.push_back(curr);
        }
        else if(prevIn && !currIn)
        {
            clipped.push_back(intersect(prev, curr, edge));
        }
        else if(!prevIn && currIn)
        {
            clipped.push_back(intersect(prev, curr, edge));
            clipped.push_back(curr);
        }
    }
}

// Function to apply Sutherland-Hodgman polygon clipping algorithm
void suthHodgman()
{
    clipped = polygon;
    clipEdge(LEFT);
    clipEdge(RIGHT);
    clipEdge(BOTTOM);
    clipEdge(TOP);
}

// Display callback function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
   
    if(!clippedFlag)
    {
        glColor3f(0.0, 0.0, 1.0);
        drawPolygon(polygon);
    }
    else
    {
        glColor3f(0.0, 1.0, 0.0);
        drawPolygon(clipped);
    }
    glFlush();
}

// Keyboard input handler
void keyboard(unsigned char key , int x , int y)
{
    if(key == 'c' || key == 'C')
    { 
        suthHodgman();
        clippedFlag = true;
        glutPostRedisplay();
    }
}

// Function to initialize OpenGL settings
void MyInit()
{
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-320, 320, -240, 240);
}

// Main function
int main(int argc, char** argv)
{
    int n;
    printf("Enter no.of vertices of polygon: ");
    scanf("%d", &n);
  
    for(int i = 0; i < n; i++)
    {
        point p;
        printf("Enter x and y for vertex %d: ", i + 1);
        scanf("%f%f", &p.x, &p.y);
        polygon.push_back(p);
    }

    printf("\nPress 'c' in the window to clip the polygon...\n");

    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("POLYGON CLIPPING");

    MyInit();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}


