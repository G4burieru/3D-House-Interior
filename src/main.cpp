#include "room1.h"
#include "main_room.h"
#include "kitchen.h"

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

GLfloat doorPositionX = 0.0, doorPositionZ = 0.0;
int isDoorClosed = 1;
float lookAtX = 0.0f, lookAtZ = -1.0f, rotationAngle = 0.0f;
static GLdouble viewerPosition[] = {0.0, 0.2, 4.2};
static GLdouble lookAtPosition[] = {0.0, 0.2, 0.0};
GLfloat colorRed = 0, colorGreen = 0, colorBlue = 0;

void *fontStyle = GLUT_BITMAP_HELVETICA_18;

void renderText(float x, float y, const char *text) {
    glRasterPos2f(x, y);
    for (unsigned int i = 0; i < strlen(text); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
    }
}

void updateColors(int) {
    colorRed += 0.01;
    colorBlue += 0.001;
    colorGreen += 0.0001;
    
    if (colorRed > 1.0) colorRed = 0;
    if (colorBlue > 1.0) colorBlue = 0;
    if (colorGreen > 1.0) colorGreen = 0;

    glutPostRedisplay();
    glutTimerFunc(100, updateColors, 0);
}

void openDoor(int v) {
    if (doorPositionX < 0.2 && doorPositionZ < 0.2) {
        doorPositionX += 0.01;
        doorPositionZ += 0.01;
    }
    isDoorClosed = 0;

    glutPostRedisplay();
    glutTimerFunc(100, openDoor, 0);
}

void displayText() {
    if (isDoorClosed) {
        renderText(-0.999, -0.500, "Press 'O' to open the door");
        glFlush();
    }
}

void drawOuterCover() {
    glColor3f(0.095, 0.095, 0.095);
    glBegin(GL_POLYGON);
    glVertex3f(-1, 0.0, 3);
    glVertex3f(-1, 0.5, 3);
    glVertex3f(-1, 0.5, 4);
    glVertex3f(-1, 0.0, 4);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-3, 0.52, 3);
    glVertex3f(-3, 0.52, -1);
    glVertex3f(3, 0.52, -1);
    glVertex3f(3, 0.52, 3);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-3, -0.02, 2.5);
    glVertex3f(-3, -0.02, -1);
    glVertex3f(3, -0.02, -1);
    glVertex3f(3, -0.02, 2.5);
    glEnd();
}

void renderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(viewerPosition[0], viewerPosition[1], viewerPosition[2], 
              viewerPosition[0] + lookAtX, lookAtPosition[1], 
              viewerPosition[2] + lookAtZ, 0.0, 1.0, 0.0);
    
    glPushMatrix();
    glTranslatef(0.0, 0.2, 3.2);
    glScalef(0.5, 0.5, 0.0);
    displayText();
    glPopMatrix();

    drawOuterCover();
    drawMainDoor();
    drawRoom1();
    //drawRoom2();
    drawKitchen();
    drawMainRoom();
    
    glutSwapBuffers();
}

void handleKeyPress(unsigned char key, int x, int y) {
    // User movement with W, A, S, D
    switch (key) {
        case 'w':  // Forward
            viewerPosition[0] += lookAtX * 0.1;
            viewerPosition[2] += lookAtZ * 0.1;
            break;
        case 's':  // Backward
            viewerPosition[0] -= lookAtX * 0.1;
            viewerPosition[2] -= lookAtZ * 0.1;
            break;
        case 'a':  // Left
            viewerPosition[0] -= cos(rotationAngle) * 0.01;
            viewerPosition[2] += sin(rotationAngle) * 0.01;
            break;
        case 'd':  // Right
            viewerPosition[0] += cos(rotationAngle) * 0.01;
            viewerPosition[2] -= sin(rotationAngle) * 0.01;
            break;
        case 'o':  // Open the door
            openDoor(0);
            break;
    }
    glutPostRedisplay();
}

void handleSpecialKeyPress(int key, int x, int y) {
    float rotationSpeed = 0.04f;  // Rotation speed

    switch (key) {
        case GLUT_KEY_LEFT:  // Turn left
            rotationAngle -= rotationSpeed;
            break;
        case GLUT_KEY_RIGHT: // Turn right
            rotationAngle += rotationSpeed;
            break;

        case GLUT_KEY_PAGE_UP: // Move up
            viewerPosition[1] += 0.1;
            break;
        case GLUT_KEY_PAGE_DOWN: // Move down
            viewerPosition[1] -= 0.1;
            break;
    }

    // Update the look direction based on the new rotation angle
    lookAtX = sin(rotationAngle);
    lookAtZ = -cos(rotationAngle);


    glutPostRedisplay();
}


void adjustViewportSize(int width, int height) {
    if (height == 0) height = 1;
    float aspectRatio = width * 1.0 / height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0f, aspectRatio, 0.1f, 10.0f);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);
    glutInitWindowSize(1000, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("3D House Architecture");

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutDisplayFunc(renderScene);
    glutReshapeFunc(adjustViewportSize);
    glDepthFunc(GL_LEQUAL);
    glutSpecialFunc(handleSpecialKeyPress);
    glutKeyboardFunc(handleKeyPress);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    
    updateColors(0);
    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);
    
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glutMainLoop();
    
    return 0;
}
