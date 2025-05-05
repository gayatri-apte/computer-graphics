#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

struct point {
    float x, y;
};

vector<point> polygonPoints;
int windowWidth = 800, windowHeight = 600;

point MultiplyMatrixWithPoint(float matrix[3][3], point p) {
    point result;
    result.x = matrix[0][0] * p.x + matrix[0][1] * p.y + matrix[0][2];
    result.y = matrix[1][0] * p.x + matrix[1][1] * p.y + matrix[1][2];
    return result;
}

void drawPolygon() {
    if (polygonPoints.empty()) return;

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (const auto& point : polygonPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glPointSize(5.0);
    glBegin(GL_POINTS);
    for (const auto& point : polygonPoints) {
        glVertex2f(point.x, point.y);
    }
    glEnd();
}

void drawAxes() {
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawPolygon();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        point p;
        p.x = (2.0f * x / windowWidth) - 1.0f;
        p.y = 1.0f - (2.0f * y / windowHeight);
        polygonPoints.push_back(p);
        glutPostRedisplay();
    }
}

// Transformation functions

void Translation(float tx, float ty, float matrix[3][3]) {
    matrix[0][0] = 1.0f; matrix[0][1] = 0.0f; matrix[0][2] = tx;
    matrix[1][0] = 0.0f; matrix[1][1] = 1.0f; matrix[1][2] = ty;
    matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = 1.0f;
}

void Scaling(float sx, float sy, float matrix[3][3]) {
    matrix[0][0] = sx;   matrix[0][1] = 0.0f; matrix[0][2] = 0.0f;
    matrix[1][0] = 0.0f; matrix[1][1] = sy;   matrix[1][2] = 0.0f;
    matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = 1.0f;
}

void Rotation(float angle, float matrix[3][3]) {
    float radians = angle * M_PI / 180.0;
    matrix[0][0] = cos(radians);  matrix[0][1] = -sin(radians); matrix[0][2] = 0.0f;
    matrix[1][0] = sin(radians);  matrix[1][1] = cos(radians);  matrix[1][2] = 0.0f;
    matrix[2][0] = 0.0f;          matrix[2][1] = 0.0f;          matrix[2][2] = 1.0f;
}

void Reflection(char axis, float matrix[3][3]) {
    if (axis == 'x' || axis == 'X') {
        matrix[0][0] = 1.0f; matrix[0][1] = 0.0f; matrix[0][2] = 0.0f;
        matrix[1][0] = 0.0f; matrix[1][1] = -1.0f; matrix[1][2] = 0.0f;
    } else {
        matrix[0][0] = -1.0f; matrix[0][1] = 0.0f; matrix[0][2] = 0.0f;
        matrix[1][0] = 0.0f;  matrix[1][1] = 1.0f; matrix[1][2] = 0.0f;
    }
    matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = 1.0f;
}

void Shearing(float sh, char axis, float matrix[3][3]) {
    matrix[0][0] = 1.0f; matrix[0][1] = (axis == 'y' || axis == 'Y') ? sh : 0.0f; matrix[0][2] = 0.0f;
    matrix[1][0] = (axis == 'x' || axis == 'X') ? sh : 0.0f; matrix[1][1] = 1.0f; matrix[1][2] = 0.0f;
    matrix[2][0] = 0.0f; matrix[2][1] = 0.0f; matrix[2][2] = 1.0f;
}

void applyTransformation(float matrix[3][3]) {
    for (auto& point : polygonPoints) {
        point = MultiplyMatrixWithPoint(matrix, point);
    }
}

void transformationMenu(int choice) {
    if (polygonPoints.empty()) {
        cout << "Please add points to the polygon first." << endl;
        return;
    }

    float matrix[3][3] = { 0 };
    switch (choice) {
        case 1: {
            float tx, ty;
            cout << "Enter translation (tx ty): ";
            cin >> tx >> ty;
            Translation(tx, ty, matrix);
            break;
        }
        case 2: {
            float sx, sy;
            cout << "Enter scaling (sx sy): ";
            cin >> sx >> sy;
            Scaling(sx, sy, matrix);
            break;
        }
        case 3: {
            float angle;
            cout << "Enter rotation angle: ";
            cin >> angle;
            Rotation(angle, matrix);
            break;
        }
        case 4: {
            char axis;
            cout << "Enter reflection axis (x/y): ";
            cin >> axis;
            Reflection(axis, matrix);
            break;
        }
        case 5: {
            float sh;
            char axis;
            cout << "Enter shear factor and axis (value x/y): ";
            cin >> sh >> axis;
            Shearing(sh, axis, matrix);
            break;
        }
        case 6: {
            polygonPoints.clear();
            cout << "Polygon reset. Add new points." << endl;
            break;
        }
    }

    if (choice >= 1 && choice <= 5) {
        applyTransformation(matrix);
    }

    glutPostRedisplay();
}

void MyInit() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("2D Polygon Transformations");

    MyInit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutCreateMenu(transformationMenu);
    glutAddMenuEntry("1. Translation", 1);
    glutAddMenuEntry("2. Scaling", 2);
    glutAddMenuEntry("3. Rotation", 3);
    glutAddMenuEntry("4. Reflection", 4);
    glutAddMenuEntry("5. Shearing", 5);
    glutAddMenuEntry("6. Reset Polygon", 6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    cout << "INSTRUCTIONS:" << endl;
    cout << "Left-click: Add vertices of polygon" << endl;
    cout << "Right-click: Open transformation menu" << endl;

    glutMainLoop();
    return 0;
}

