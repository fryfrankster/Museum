//  ========================================================================
//  COSC363: Computer Graphics (2020);  University of Canterbury.
//
//  FILE NAME: OpenGLMuseum.cpp
//  See Lab01.pdf for details
//  ========================================================================

#include <cmath>
#include <GL/freeglut.h>

int cam_hgt = 0;
int theta = 0;
int stringAngle = 45;

float armRotation = -75.;
float t = 0.0;


struct objectPoint {
    float dx;
    float dy;
};

struct objectPoint throwBall() {
    struct objectPoint distance;

    float initHeight = 13.5;
    int alpha = 20;
    float g = 9.82;
    float vel = 19.4;

    float vx = vel * cos(alpha * (M_PI / 180));
    float vy = vel * sin(alpha * (M_PI / 180));

    distance.dx = -(vx * t);
    distance.dy = initHeight + vy * t - g  * pow(t, 2) / 2;

    return distance;
}



//--Draws a grid of lines on the floor plane -------------------------------
void drawFloor()
{
    glColor3f(0., 0.5,  0.);			//Floor colour

    for(int i = -50; i <= 50; i ++)
    {
        glBegin(GL_LINES);			//A set of grid lines on the xz-plane
            glVertex3f(-50, -0.75, i);
            glVertex3f(50, -0.75, i);
            glVertex3f(i, -0.75, -50);
            glVertex3f(i, -0.75, 50);
        glEnd();
    }
}

void drawCatapult(void) {
    //Four wheels
    glPushMatrix();
        glTranslatef(0., 0., -5);
        glColor3f(0.4, 0.4, 0.4);
        glutSolidCylinder(2.25, 0.75, 15.0, 30.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(12.5, 0., -5);
        glColor3f(0.4, 0.4, 0.4);
        glutSolidCylinder(2.25, 0.75, 15.0, 30.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0., 0., 5.);
        glColor3f(0.4, 0.4, 0.4);
        glutSolidCylinder(2.25, 0.75, 15.0, 30.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(12.5, 0., 5.);
        glColor3f(0.4, 0.4, 0.4);
        glutSolidCylinder(2.25, 0.75, 15.0, 30.0);
    glPopMatrix();

    //Centre axles for the wheels
    glPushMatrix();
        glTranslatef(0., 0., 0.0);
        glScalef(1.0, 1.0, 10.);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(12.5, 0., 0.0);
        glScalef(1.0, 1.0, 10.);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    //Side panels
    glPushMatrix();
        glTranslatef(7.0, 2., 4.5);
        glScalef(18.75, 3.0, 1.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(7.0, 2., -3.75);
        glScalef(18.75, 3.0, 1.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    //Frame
    glPushMatrix();
        glTranslatef(4.25, 7., 4.5);
        glScalef(2.0, 7.0, 1.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.0, 3.5, 5.0);
        glRotatef(-37.0, 0, 0, 1);
        glTranslatef(1.0, -3.5, -5.0);
        glTranslatef(0., 7., 4.5);
        glScalef(2.0, 7.0, 1.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.25, 7.,-3.75);
        glScalef(2.0, 7.0, 1.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0, 3.5, -3.25);
        glRotatef(-37.0, 0, 0, 1);
        glTranslatef(1.0, -3.5, 3.25);
        glTranslatef(0., 7., -3.75);
        glScalef(2.0, 7.0, 1.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.75, 9.5, 0.4);
        glScalef(1.0, 2.0, 7.5);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(5.75, 9.5, 0.25);
        glScalef(1.0, 2.0, 3.5);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.75, 1.0, -3.75);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCylinder(.5, 8.0, 15.0, 30.0);
    glPopMatrix();

    //Arm
    glPushMatrix();
        glTranslatef(4.75, 1.0, 0.25);
        glRotatef(armRotation, 0, 0, 1);
        glTranslatef(-4.75, -1.0, -0.25);

        glTranslatef(4.75, 7.0, 0.25);
        glScalef(1.0, 13.0, 2.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();
}

void drawBoulder(void) {

    struct objectPoint distance = throwBall();

    glPushMatrix();
        glTranslatef(4.75, 1.0, 0.25);
        glRotatef(armRotation, 0, 0, 1);
        glTranslatef(-4.75, -1.0, -0.25);

        glTranslatef(2.5 + distance.dx, distance.dy, 0.25);
        glColor3f(0.4, 0.4, 0.4);
        glutSolidSphere(1.75, 10.0, 10.0);
    glPopMatrix();
}

void drawPendulum(void) {
    //frame
    glPushMatrix();
        glTranslatef(5., 8., 0.);
        glScalef(1.5, 14.0, 1.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    //top
    glPushMatrix();
        glTranslatef(5., 14.5, 2.5);
        glScalef(1.5, 1.0, 5.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    //base
    glPushMatrix();
        glTranslatef(5., 0., 0.);
        glScalef(6.0, 2.0, 2.0);
        glColor3f(0.5, 0.35, 0.1);
        glutSolidCube(1.0);
    glPopMatrix();

    //ring
    glPushMatrix();
        glTranslatef(5., 13.25, 3.5);
        glRotatef(90, 0, 1, 0);
        glColor3f(0.4, 0.4, 0.4);
        glutSolidTorus(0.3, 0.6, 5., 15.0);
    glPopMatrix();

    //string

    glPushMatrix();
        glTranslatef(5., 12.75, 3.5);
        glColor3f(0., 0., 0.);
        glutSolidTorus(0.15, 0.3, 5., 15.0);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(5., 12.35, 3.5);
        glRotatef(stringAngle, 0, 0, 1);
        glTranslatef(-5., -12.35, -3.5);

        glTranslatef(5., 12.35, 3.5);
        glRotatef(90, 1, 0, 0);
        glColor3f(0., 0., 0.);
        glutSolidCylinder(0.1, 8., 8., 20.);
    glPopMatrix();
}

void myTimer(int value) {
    if (armRotation < -15) {
        armRotation += 3.5;
    } else {
        t += .05;
    }
    glutPostRedisplay();
    glutTimerFunc(60, myTimer, 0);
}

//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display(void)
{
    float lpos[4] = {0., 10., 10., 1.0};  //light's position

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(30 * sin(theta * (M_PI / 180)), cam_hgt, 30 * cos(theta * (M_PI / 180)), 0, 0, 0, 0, 1, 0);  //Camera position and orientation
    glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

    glDisable(GL_LIGHTING);			//Disable lighting when drawing floor.
    drawFloor();

    glEnable(GL_LIGHTING);			//Enable lighting when drawing the teapot
    glColor3f(0.0, 1.0, 1.0);

    glPushMatrix();
        glTranslatef(10., 0., -18.);
        drawCatapult();
        drawBoulder();
    glPopMatrix();

    drawPendulum();

    glFlush();
}

//--Special keyboard event callbackfunction---------
void special(int key, int x, int y) {
    if(key == GLUT_KEY_UP) cam_hgt++;
    else if(key == GLUT_KEY_DOWN) cam_hgt--;
    else if(key == GLUT_KEY_RIGHT) theta++;
    else if(key == GLUT_KEY_LEFT) theta--;
    glutPostRedisplay();
}

//----------------------------------------------------------------------
void initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glEnable(GL_LIGHTING);		//Enable OpenGL states
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 10.0, 1000.0);   //Camera Frustum
}


//  ------- Main: Initialize glut window and register call backs -------
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Museum");
    initialize();
    glutDisplayFunc(display);
    glutSpecialFunc(special);
    glutTimerFunc(60, myTimer, 0);
    glutMainLoop();
    return 0;
}


//When the ball reaches y = 0.5, it would have hit the ground.
//therefore initial height is 14
//range is 45.5
