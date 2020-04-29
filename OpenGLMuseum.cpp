//  ========================================================================
//  COSC363: Medieval OpenGL Museum
//
//  FILE NAME: OpenGLMuseum.cpp
//  AUTHOR: Frankie Oprenario
//  ========================================================================

#include <cmath>
#include <GL/freeglut.h>
#include "loadTGA.h"

int cam_hgt = 0;
int theta = 0;
int stringAngle = -38;

float armRotation = -75.;
float t = 0.0;
bool change = true;
bool release = false;

GLuint txId[4];   //Texture ids
float angle=0, look_x, look_z=-1., eye_x, eye_z = 65;  //Camera parameters


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

//--------------------------------------------------------------------------------
void loadTexture()
{
    glGenTextures(4, txId); 	// Create 2 texture ids

    glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
    loadTGA("Cobblestone.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
    loadTGA("Mosaiac.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
    loadTGA("Wood.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, txId[3]);  //Use this texture
    loadTGA("Gate.tga");
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}


//--Draws a grid of lines on the floor plane -------------------------------

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

void drawCatapultShadow(void) {
    glColor4f(0.2, 0.2, 0.2, 1.0);

    //Four wheels
    glPushMatrix();
        glTranslatef(0., 0., -5);
        glutSolidCylinder(2.25, 0.75, 15.0, 30.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(12.5, 0., -5);
        glutSolidCylinder(2.25, 0.75, 15.0, 30.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0., 0., 5.);
        glutSolidCylinder(2.25, 0.75, 15.0, 30.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(12.5, 0., 5.);
        glutSolidCylinder(2.25, 0.75, 15.0, 30.0);
    glPopMatrix();

    //Centre axles for the wheels
    glPushMatrix();
        glTranslatef(0., 0., 0.0);
        glScalef(1.0, 1.0, 10.);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(12.5, 0., 0.0);
        glScalef(1.0, 1.0, 10.);
        glutSolidCube(1.0);
    glPopMatrix();

    //Side panels
    glPushMatrix();
        glTranslatef(7.0, 2., 4.5);
        glScalef(18.75, 3.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(7.0, 2., -3.75);
        glScalef(18.75, 3.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //Frame
    glPushMatrix();
        glTranslatef(4.25, 7., 4.5);
        glScalef(2.0, 7.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.0, 3.5, 5.0);
        glRotatef(-37.0, 0, 0, 1);
        glTranslatef(1.0, -3.5, -5.0);
        glTranslatef(0., 7., 4.5);
        glScalef(2.0, 7.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.25, 7.,-3.75);
        glScalef(2.0, 7.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0, 3.5, -3.25);
        glRotatef(-37.0, 0, 0, 1);
        glTranslatef(1.0, -3.5, 3.25);
        glTranslatef(0., 7., -3.75);
        glScalef(2.0, 7.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.75, 9.5, 0.4);
        glScalef(1.0, 2.0, 7.5);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(5.75, 9.5, 0.25);
        glScalef(1.0, 2.0, 3.5);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(4.75, 1.0, -3.75);
        glutSolidCylinder(.5, 8.0, 15.0, 30.0);
    glPopMatrix();

    //Arm
    glPushMatrix();
        glTranslatef(4.75, 1.0, 0.25);
        glRotatef(armRotation, 0, 0, 1);
        glTranslatef(-4.75, -1.0, -0.25);

        glTranslatef(4.75, 7.0, 0.25);
        glScalef(1.0, 13.0, 2.0);
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

void drawBoulderShadow(void) {

    struct objectPoint distance = throwBall();
    glColor4f(0.2, 0.2, 0.2, 1.0);

    glPushMatrix();
        glTranslatef(4.75, 1.0, 0.25);
        glRotatef(armRotation, 0, 0, 1);
        glTranslatef(-4.75, -1.0, -0.25);

        glTranslatef(2.5 + distance.dx, distance.dy, 0.25);
        glutSolidSphere(1.75, 10.0, 10.0);
    glPopMatrix();
}

void drawPendulum(void) {

    //frame
    glColor3f(0.5, 0.35, 0.1);
    glPushMatrix();
        glTranslatef(5., 8., 0.);
        glScalef(1.5, 14.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //top
    glPushMatrix();
        glTranslatef(5., 14.5, 2.5);
        glScalef(1.5, 1.0, 5.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //base
    glPushMatrix();
        glTranslatef(5., 0., 0.);
        glScalef(6.0, 2.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //ring
    glColor3f(0.4, 0.4, 0.4);
    glPushMatrix();
        glTranslatef(5., 13.25, 3.5);
        glRotatef(90, 0, 1, 0);
        glutSolidTorus(0.3, 0.6, 5., 15.0);
    glPopMatrix();

    //string
    glColor3f(0., 0., 0.);
    glPushMatrix();
        glTranslatef(5., 12.75, 3.5);
        glutSolidTorus(0.15, 0.3, 5., 15.0);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(5., 12.35, 3.5);
        glRotatef(stringAngle, 0, 0, 1);
        glTranslatef(-5., -12.35, -3.5);

        glTranslatef(5., 12.35, 3.5);
        glRotatef(90, 1, 0, 0);
        glutSolidCylinder(0.1, 8., 8., 20.);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(5., 12.35, 3.5);
        glRotatef(stringAngle, 0, 0, 1);
        glTranslatef(-5., -12.35, -3.5);

        glTranslatef(5., 4.35, 3.5);
        glRotatef(90, 1, 0, 0);
        glutSolidSphere(0.5, 15., 20);
    glPopMatrix();
}

void drawPendulumShadow(void) {

    //frame
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glPushMatrix();
        glTranslatef(5., 8., 0.);
        glScalef(1.5, 14.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //top
    glPushMatrix();
        glTranslatef(5., 14.5, 2.5);
        glScalef(1.5, 1.0, 5.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //base
    glPushMatrix();
        glTranslatef(5., 0., 0.);
        glScalef(6.0, 2.0, 2.0);
        glutSolidCube(1.0);
    glPopMatrix();

    //ring
    glPushMatrix();
        glTranslatef(5., 13.25, 3.5);
        glRotatef(90, 0, 1, 0);
        glutSolidTorus(0.3, 0.6, 5., 15.0);
    glPopMatrix();

    //string
    glColor3f(0., 0., 0.);
    glPushMatrix();
        glTranslatef(5., 12.75, 3.5);
        glutSolidTorus(0.15, 0.3, 5., 15.0);
    glPopMatrix();


    glPushMatrix();
        glTranslatef(5., 12.35, 3.5);
        glRotatef(stringAngle, 0, 0, 1);
        glTranslatef(-5., -12.35, -3.5);

        glTranslatef(5., 12.35, 3.5);
        glRotatef(90, 1, 0, 0);
        glutSolidCylinder(0.1, 8., 8., 20.);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(5., 12.35, 3.5);
        glRotatef(stringAngle, 0, 0, 1);
        glTranslatef(-5., -12.35, -3.5);

        glTranslatef(5., 4.35, 3.5);
        glRotatef(90, 1, 0, 0);
        glutSolidSphere(0.5, 15., 20);
    glPopMatrix();
}

void drawThrone(void) {
    glColor3f(0.5, 0.35, 0.1);
    glPushMatrix();
        glTranslatef(0., 5.75, 0.);
        glScalef(6.5, 13., 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0., 3.75, 3.);
        glScalef(6.5, 1.0, 5.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0., 1.25, 5.);
        glScalef(6.5, 4.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0., 12.25, -0.5);
        glScalef(1., 1.5, 1.);
        glutSolidCylinder(3.25, 1., 20., 20.);
    glPopMatrix();

}

void drawThroneShadow(void) {
    glColor4f(0.2, 0.2, 0.2, 1.0);
    glPushMatrix();
        glTranslatef(0., 5.75, 0.);
        glScalef(6.5, 13., 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0., 3.75, 3.);
        glScalef(6.5, 1.0, 5.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0., 1.25, 5.);
        glScalef(6.5, 4.0, 1.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0., 12.25, -0.5);
        glScalef(1., 1.5, 1.);
        glutSolidCylinder(3.25, 1., 20., 20.);
    glPopMatrix();
}

void drawOutdoorFloor(void) {
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);   //Facing +y (Top side)
        glVertex3f(-55, -1., 0);
        glVertex3f(55, -1., 0);
        glVertex3f(55, -1., 30);
        glVertex3f(-55, -1., 30);
    glEnd();
}

void drawFlooring(void) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[1]);
    glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);   //Facing +y (Top side)
        glTexCoord2f(0.0, 0.0); glVertex3f(-55, -1., 0);
        glTexCoord2f(5.0, 0.0); glVertex3f(55, -1., 0);
        glTexCoord2f(5.0, 3.0); glVertex3f(55, -1., -60);
        glTexCoord2f(0.0, 3.0); glVertex3f(-55, -1., -60);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void drawWalls() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture

    glBegin(GL_QUADS);
        //Back Wall
        glNormal3f(0.0, 0.0, 1.0);
        glTexCoord2f(0.0, 2.0); glVertex3f(-55, 35, -60);
        glTexCoord2f(0.0, 0.0); glVertex3f(-55, -1, -60);
        glTexCoord2f(3.0, 0.0); glVertex3f(55, -1, -60);
        glTexCoord2f(3.0, 2.0); glVertex3f(55, 35, -60);

        //Front Wall
        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(0.0, 2.0); glVertex3f(-55, 35, 0);
        glTexCoord2f(0.0, 0.0); glVertex3f(-55, -1, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(-10, -1, 0);
        glTexCoord2f(1.0, 2.0); glVertex3f(-10, 35, 0);

        glNormal3f(0.0, 0.0, -1.0);
        glTexCoord2f(0.0, 2.0); glVertex3f(10, 35, 0);
        glTexCoord2f(0.0, 0.0); glVertex3f(10, -1, 0);
        glTexCoord2f(1.0, 0.0); glVertex3f(55, -1, 0);
        glTexCoord2f(1.0, 2.0); glVertex3f(55, 35, 0);

        //Left Wall
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.0, 2.0); glVertex3f(-55, 35, -60);
        glTexCoord2f(0.0, 0.0); glVertex3f(-55, -1, -60);
        glTexCoord2f(1.0, 0.0); glVertex3f(-55, -1, 0);
        glTexCoord2f(1.0, 2.0); glVertex3f(-55, 35, 0);

        //Right Wall
        glNormal3f(0.0, -1.0, 0.0);
        glTexCoord2f(0.0, 2.0); glVertex3f(55, 35, -60);
        glTexCoord2f(0.0, 0.0); glVertex3f(55, -1, -60);
        glTexCoord2f(1.0, 0.0); glVertex3f(55, -1, 0);
        glTexCoord2f(1.0, 2.0); glVertex3f(55, 35, 0);
        glEnd();
    glDisable(GL_TEXTURE_2D);

    //Roof
    glColor3f(0.5, 0.35, 0.1);
    glBegin(GL_QUADS);
        glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-55, 35, 0);
        glVertex3f(55, 35, 0);
        glVertex3f(55, 35, -60);
        glVertex3f(-55, 35, -60);
    glEnd();
}

void drawDoor(void) {

    glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, txId[3]);

        glBegin(GL_QUADS);
        glNormal3f(0.0, 0.0, 1.0);   //Facing +z (Front side)
            glTexCoord2f(0.0, 0.0); glVertex3f(-12, 18, 1);
            glTexCoord2f(0.0, 1.0); glVertex3f(12, 18, 1);
            glTexCoord2f(1.0, 1.0); glVertex3f(12, 35, 1);
            glTexCoord2f(1.0, 0.0); glVertex3f(-12, 35, 1);

        glNormal3f(0.0, 0.0, -1.0);   //Facing +z (Front side)
            glTexCoord2f(0.0, 0.0); glVertex3f(-12, 18, 1);
            glTexCoord2f(0.0, 1.0); glVertex3f(12, 18, 1);
            glTexCoord2f(1.0, 1.0); glVertex3f(12, 35, 1);
            glTexCoord2f(1.0, 0.0); glVertex3f(-12, 35, 1);
        glEnd();

    glDisable(GL_TEXTURE_2D);

    glColor3f(0.5, 0.35, 0.1);
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0, 0.0);   //Facing +z (Front side)
        glVertex3f(-12, 18, 1);
        glVertex3f(-12, 18, 0);
        glVertex3f(-12, 35, 0);
        glVertex3f(-12, 35, 1);

    glNormal3f(1.0, 0.0, 0.0);   //Facing +z (Front side)
        glVertex3f(12, 18, 1);
        glVertex3f(12, 18, 0);
        glVertex3f(12, 35, 0);
        glVertex3f(12, 35, 1);

    glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-12, 18, 1);
        glVertex3f(12, 18, 1);
        glVertex3f(12, 18, 0);
        glVertex3f(-12, 18, 0);

    glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-12, 35, 1);
        glVertex3f(12, 35, 1);
        glVertex3f(12, 35, 0);
        glVertex3f(-12, 35, 0);

    glEnd();
}

void myTimer(int value) {

    //Releasing the boulder from the catapult when pressed
    if (release) {
        if (armRotation < -15) {
            armRotation += 3.5;
        } else {
            if (t >= 0.0 && t <= 3.10) {
                t += 0.05;
            }
        }
    }


    //Changing the swinging of the pendulum
    if (change) {
        stringAngle += 4.;
        if (stringAngle > 39) {
            change = false;
        }
    } else {
        stringAngle -= 4.;
        if (stringAngle < -39) {
            change = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(60, myTimer, 0);
}

void special(int key, int x, int y)
{
    switch(key) {
        case GLUT_KEY_LEFT:
            angle -= 0.1;
        break;
        case GLUT_KEY_RIGHT:
            angle += 0.1;
        break;
        case GLUT_KEY_DOWN:
        //Move backward
            eye_x -= 0.2*sin(angle);
            eye_z += 0.2*cos(angle);
        break;
        case GLUT_KEY_UP:
        //Move forward
            eye_x += 0.2*sin(angle);
            eye_z -= 0.2*cos(angle);
        break;
        case GLUT_KEY_F2:
        //Releasing the catapult
            release = true;
        break;
    }

    look_x = eye_x + 100*sin(angle);
    look_z = eye_z - 100*cos(angle);

    glutPostRedisplay();
}

//--Display: ---------------------------------------------------------------
//--This is the main display module containing function calls for generating
//--the scene.
void display(void)
{
    float lpos1[4] = {0., 35., -45., 1.0};  //light's position
    float shadowMat[16] = {lpos1[1], 0, 0, 0, lpos1[0], 0, -lpos1[2], -1, 0, 0, lpos1[1], 0, 0, 0, 0, lpos1[1]};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_x, 8, eye_z,  look_x, 8, look_z,   0, 1, 0);
    glLightfv(GL_LIGHT0,GL_POSITION, lpos1);   //Set light position

    glDisable(GL_LIGHTING);

    drawFlooring();
    drawOutdoorFloor();
    drawWalls();
    drawDoor();

    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(23., 2.25, -40.);
        glColor4f(0.2, 0.2, 0.2, 1.0);
        drawCatapultShadow();
        drawBoulderShadow();
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(23., 2.25, -40.);
        drawCatapult();
        drawBoulder();
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(40., -1., -15.);
        glRotatef(-90, 0, 1, 0);
        drawPendulumShadow();
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(40., 1., -15.);
        glRotatef(-90, 0, 1, 0);
        drawPendulum();
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(-40., -1., -15.);
        glRotatef(90, 0, 1, 0);
        drawThroneShadow();
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(-40., 0., -15.);
        glRotatef(90, 0, 1, 0);
        drawThrone();
    glPopMatrix();

    glFlush();
}


//----------------------------------------------------------------------
void initialize(void)
{
        loadTexture();
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
    glutInitWindowSize(1000, 1000);
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
