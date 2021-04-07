#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include <cmath>

using namespace std;
using namespace glm;

struct Vertex
{
    Vertex(const vec3& position, const vec3& normal)
        : position(position)
        , normal(normal)
    {}
    vec3 position;
    vec3 normal;
};

// spin the Points array around the Z axis.
// Points.x will become the radius, and Points.y will become the height
// Points should be sorted by y-coordinate
vector< Vertex > Lathe(const vector< vec2 >& Points, unsigned int segments = 128)
{
    // precalculate circle points
    vector< vec2 > cirPoints;
    for (unsigned int i = 0; i <= segments; ++i)
    {
        float angle = (i / (float)segments) * 3.14159f * 2.0f;
        cirPoints.push_back(vec2(cos(angle), sin(angle)));
    }

    // fill each layer
    typedef vector< vec3 > Layer;
    typedef vector< Layer > Layers;
    Layers layers(Points.size(), Layer(cirPoints.size()));
    for (size_t i = 0; i < Points.size(); ++i)
    {
        for (unsigned int j = 0; j < cirPoints.size(); ++j)
        {
            layers[i][j] = vec3(cirPoints[j] * Points[i].x, Points[i].y);
        }
    }

    // move through layers generating triangles
    vector< Vertex > verts;
    for (size_t i = 1; i < layers.size(); ++i)
    {
        const Layer& prvLayer = layers[i - 1];
        const Layer& curLayer = layers[i - 0];
        for (size_t j = 1; j < cirPoints.size(); ++j)
        {
            //    upper = cur layer
            //        UL -- UR  
            // left   | 0 /  |  right 
            // = j-1  |  / 1 |  = j-0
            //        LL -- LR  
            //    lower = prv layer
            const vec3& LL = prvLayer[j - 1]; // lower-left
            const vec3& LR = prvLayer[j - 0]; // lower-right
            const vec3& UL = curLayer[j - 1]; // upper-left
            const vec3& UR = curLayer[j - 0]; // upper-right

            // triangle0: LL -> UR -> UL
            const vec3 normal0 = normalize(cross(UR - LL, UL - LL));
            verts.push_back(Vertex(LL, normal0));
            verts.push_back(Vertex(UR, normal0));
            verts.push_back(Vertex(UL, normal0));

            // triangle1: LL -> LR -> UR
            const vec3 normal1 = normalize(cross(LR - LL, UL - LL));
            verts.push_back(Vertex(LL, normal1));
            verts.push_back(Vertex(LR, normal1));
            verts.push_back(Vertex(UR, normal1));
        }
    }

    return verts;
}

// mouse state
int btn;
ivec2 startMouse;
ivec2 startRotate, currentRotate;

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        btn = button;
        startMouse = ivec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
        startRotate = currentRotate;
    }
}

void motion(int x, int y)
{
    ivec2 curMouse(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
    if (btn == GLUT_LEFT_BUTTON)
    {
        currentRotate = startRotate + (curMouse - startMouse);
    }
    glutPostRedisplay();
}

vector< Vertex > model;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double w = glutGet(GLUT_WINDOW_WIDTH);
    double h = glutGet(GLUT_WINDOW_HEIGHT);
    double ar = w / h;
    gluPerspective(60, ar, 0.1, 40);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -10);

    glPushMatrix();
    glRotatef(currentRotate.x % 360, 0, 1, 0);
    glRotatef(-currentRotate.y % 360, 1, 0, 0);

    // draw model
    if (!model.empty())
    {
        glColor3ub(223, 244, 0);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(3, GL_FLOAT, sizeof(Vertex), &model[0].position);
        glNormalPointer(GL_FLOAT, sizeof(Vertex), &model[0].normal);
        glDrawArrays(GL_TRIANGLES, 0, model.size());
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
    }

    // draw bounding cube
    glDisable(GL_LIGHTING);
    glColor3ub(255, 255, 255);
    glutWireCube(7);
    glEnable(GL_LIGHTING);

    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    vector< vec2 > Points;
    Points.push_back(vec2(0, -1));
    Points.push_back(vec2(-2, -1));
    Points.push_back(vec2(-2, 0.1-1));
    Points.push_back(vec2(-1.5,0.2-1));
    Points.push_back(vec2(-1,0.3-1));
    Points.push_back(vec2(-0.5,0.4-1));
    Points.push_back(vec2(-0.5,1.6-1));
    Points.push_back(vec2(-1,1.7-1));
    Points.push_back(vec2(-1.5,1.8-1));
    Points.push_back(vec2(-1.7,2-1));
    Points.push_back(vec2(-1.8,2.2-1));
    Points.push_back(vec2(-2,2.8-1));
    Points.push_back(vec2(-1.9,4-1));
    Points.push_back(vec2(-1.85,4-1));
    Points.push_back(vec2(-1.85,2.2-1));
    Points.push_back(vec2(-1.5,2.1-1));
    Points.push_back(vec2(0,2-1));
    model = Lathe(Points);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("GLUT");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glEnable(GL_DEPTH_TEST);

    // set up lighting
    glShadeModel(GL_SMOOTH);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glEnable(GL_LIGHTING);

    // set up "headlamp"-like light
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat position[] = { 0, 1, 1, 0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    glutMainLoop();
    return 0;
}