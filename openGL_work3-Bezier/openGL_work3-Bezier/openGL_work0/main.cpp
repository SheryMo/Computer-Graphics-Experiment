#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

static float min[] = { -1.0, -1.0, -1.0 };
static float max[] = { 1.0, 1.0, 1.0 };
static float pointMax[3], pointMin[3];
static int windowWidth, windowHeight;

static GLfloat points[1000][3];
static int numPoints = 0;
static int selectedPoint = -1;

void pointInit(int x, int y, GLfloat& fx, GLfloat& fy)
{
    fx = pointMin[0] + (float)x / (float)windowWidth *
        (pointMax[0] - pointMin[0]);

    fy = pointMin[1] + (float)(windowHeight - y) / (float)windowHeight *
        (pointMax[1] - pointMin[1]);
}

/**
 * The display callback
 */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(1.0, 0.7, 0.0);
    glPointSize(3.);
    //curve.
    // Create and draw the curves for every 4 points
    for (int i = 0; (i + 3) < numPoints; i += 3) {

        glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &points[i][0]);
        // Draw the curve
        glBegin(GL_POINTS);  
        {
            for (int i = 0; i < 100; i++) {
                glEvalCoord1f(((float)i) / 100.0);
            }
        }
        glEnd();
    }
    //points.
    // Show the points
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < numPoints; i++) {
            if (i == selectedPoint) {
                glColor3f(1.0, 0.0, 1.0);
                glVertex3f(points[i][0], points[i][1], points[i][2]);
            }
            else {
                glColor3f(0.0, 1.0, 0.0);
                glVertex3f(points[i][0], points[i][1], points[i][2]);
            }
        }
        glEnd();
    }
    // Connect the points (using a piecewise linear curve)
    if (numPoints >= 2) {
        glColor3f(0.75, 0.75, 0.75);
        glBegin(GL_LINE_STRIP);
        {
            for (int i = 0; i < numPoints; i++) {
                glVertex3f(points[i][0], points[i][1], points[i][2]);
            }
        }
        glEnd();
    }
    glFlush();
    glutSwapBuffers();
}


void motion(int x, int y) {
    GLfloat fx, fy;

    pointInit(x, y, fx, fy);

    if (selectedPoint >= 0) {
        points[selectedPoint][0] = fx;
        points[selectedPoint][1] = fy;

        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y) {
    GLfloat fx, fy;

    pointInit(x, y, fx, fy);

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            points[numPoints][0] = fx;
            points[numPoints][1] = fy;
            points[numPoints][2] = 0.;

            numPoints++;

            glutPostRedisplay();
        }
    }
}

void reshape(int width, int height) {
    float max3D, min3D;
    GLfloat aspect;
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    min3D = min[0];
    max3D = max[0];
    for (int i = 1; i < 3; i++) {
        if (min[i] < min3D)
            min3D = min[i];
        if (max[i] > max3D)
            max3D = max[i];
    }
    if (fabs(min3D) > max3D)
        max3D = fabs(min3D);
    min3D = -max3D;
    if (width <= height) {
        aspect = (GLfloat)height / (GLfloat)width;
        pointMin[0] = min3D;
        pointMax[0] = max3D;
        pointMin[1] = min3D * aspect;
        pointMax[1] = max3D * aspect;
        pointMin[2] = min3D;
        pointMax[2] = max3D;
    }
    else {
        aspect = (GLfloat)width / (GLfloat)height;
        pointMin[0] = min3D * aspect;
        pointMax[0] = max3D * aspect;
        pointMin[1] = min3D;
        pointMax[1] = max3D;
        pointMin[2] = min3D;
        pointMax[2] = max3D;
    }
    glOrtho(pointMin[0], pointMax[0], pointMin[1], pointMax[1], pointMin[2],
        pointMax[2]);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
    windowWidth = 500;
    windowHeight = 500;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Bezier Curves");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MAP1_VERTEX_3);
    glutMainLoop();
}