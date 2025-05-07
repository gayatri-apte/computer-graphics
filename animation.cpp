#include <GL/glut.h>
#include <cmath>

float cloudX = 0.0f;
float boatX = 0.0f;
float sunAngle = 0.0f; // For rotating sun rays

void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < num_segments; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawSun() {
    float sunX = 0.7f;
    float sunY = 0.8f;
    float radius = 0.1f;

    // Sun body
    glColor3f(1.0f, 1.0f, 0.0f);
    drawCircle(sunX, sunY, radius, 100);

    // Sun rays
    glPushMatrix();
    glTranslatef(sunX, sunY, 0.0f);
    glRotatef(sunAngle, 0.0f, 0.0f, 1.0f); // Clockwise rotation
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_LINES);
    for (int i = 0; i < 12; ++i) {
        float angle = 2.0f * 3.1415926f * i / 12;
        float x1 = 0.0f;
        float y1 = 0.0f;
        float x2 = (radius + 0.05f) * cosf(angle);
        float y2 = (radius + 0.05f) * sinf(angle);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();
    glPopMatrix();
}

void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 0.07f, 100);
    drawCircle(x + 0.08f, y, 0.07f, 100);
    drawCircle(x + 0.04f, y + 0.04f, 0.07f, 100);
}

void drawBoat(float x) {
    // Boat base
    glColor3f(0.4f, 0.2f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.1f, -0.6f);
    glVertex2f(x + 0.1f, -0.6f);
    glVertex2f(x + 0.07f, -0.65f);
    glVertex2f(x - 0.07f, -0.65f);
    glEnd();

    // Mast
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(x, -0.6f);
    glVertex2f(x, -0.45f);
    glEnd();

    // Sail
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, -0.45f);
    glVertex2f(x, -0.6f);
    glVertex2f(x + 0.05f, -0.525f);
    glEnd();
}

void drawTree(float x, float y) {
    // Trunk
    glColor3f(0.5f, 0.35f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.01f, y - 0.05f);
    glVertex2f(x + 0.01f, y - 0.05f);
    glVertex2f(x + 0.01f, y + 0.05f);
    glVertex2f(x - 0.01f, y + 0.05f);
    glEnd();

    // Leaves
    glColor3f(0.0f, 0.6f, 0.0f);
    drawCircle(x, y + 0.07f, 0.03f, 100);
    drawCircle(x - 0.02f, y + 0.05f, 0.03f, 100);
    drawCircle(x + 0.02f, y + 0.05f, 0.03f, 100);
}

void drawHouse(float x, float y) {
    // House base
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.05f, y);
    glVertex2f(x + 0.05f, y);
    glVertex2f(x + 0.05f, y + 0.05f);
    glVertex2f(x - 0.05f, y + 0.05f);
    glEnd();

    // Roof
    glColor3f(0.5f, 0.25f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - 0.05f, y + 0.05f);
    glVertex2f(x + 0.05f, y + 0.05f);
    glVertex2f(x, y + 0.08f);
    glEnd();
}

void drawScene() {
    // Sky
    glColor3f(0.5f, 0.8f, 0.92f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Sun with rotating rays
    drawSun();

    // Mountains
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.3f, 0.5f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.2f, 0.0f);
    glVertex2f(0.1f, 0.6f);
    glVertex2f(0.4f, 0.0f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.5f, 0.4f);
    glVertex2f(0.8f, 0.0f);
    glEnd();

    // Ground
    glColor3f(0.2f, 0.8f, 0.2f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(-1.0f, -0.5f);
    glEnd();

    // Water
    glColor3f(0.0f, 0.5f, 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(-1.0f, -0.5f);
    glVertex2f(1.0f, -0.5f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    // Static house and trees
    drawHouse(-0.6f, -0.3f);
    drawTree(-0.5f, -0.3f);
    drawTree(-0.4f, -0.3f);

    // Clouds
    drawCloud(-0.8f + cloudX, 0.8f);
    drawCloud(-0.4f + cloudX, 0.85f);
    drawCloud(0.0f + cloudX, 0.8f);

    // Boat
    drawBoat(-0.9f + boatX);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawScene();
    glutSwapBuffers();
}

void update(int value) {
    // Move clouds
    cloudX += 0.001f;
    if (cloudX > 2.0f) cloudX = -1.0f;

    // Move boat
    boatX += 0.001f;
    if (boatX > 2.0f) boatX = -1.5f;

    // Rotate sun rays
    sunAngle -= 1.0f; // Clockwise
    if (sunAngle < -360.0f) sunAngle += 360.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Animated Natural Scenery with Rotating Sun");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}



