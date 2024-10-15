#include "room1.h"
#include "main_room.h"
#include "kitchen.h"

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "functionsAux.h"
#include <iostream>


#define MIN_X -2.5 //constantes minima para o valor da coordenada X
#define MAX_X 0.8  //constantes maxima para o valor da coordenada X
#define MIN_Y 0.1 //constantes minima para o valor da coordenada Y
#define MAX_Y 0.5  //constantes maximas para o valor da coordenada Y
#define MIN_Z -0.5 //constantes minima para o valor da coordenada Z
#define MAX_Z 5.0 //constantes maximas para o valor da coordenada Z


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
    glColor3f( 196.0f / 255.0f, 160.0f/255.0f, 112.0f/255.0f);
    GLfloat matSpecular [] = {1.f, 1.f, 1.f, 1.f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    GLfloat shininess[] = {128.0f};
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);


    GLfloat normal[3];
    glBegin(GL_POLYGON);

    /* Calculando as normais */
    /* Estamos fazendo aqui sempre V1 - V0 e V3-V0
     * depois fazendo o produto */
    
    GLfloat v0 [] = {-1, 0.0, 3};
    GLfloat v1 [] = {-1, 0.5, 3};
    GLfloat v3 [] = {-1, 0.0, 4};
    GLfloat vv [] = {-1,0.5, 4};
    FunctionAux::calculateFlatNormal(v0, v1, v3, vv, normal);
    
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3f(v0[0], v0[1], v0[2]);
    glVertex3f(v1[0], v1[1], v1[2]);
    glVertex3f(-1, 0.5, 4);
    glVertex3f(v3[0], v3[1], v3[2]);
    glEnd();

    glBegin(GL_POLYGON);
    
    GLfloat v4 [] = {-3, 0.52, 3};
    GLfloat v5 [] = {-3, 0.52, -1};
    GLfloat v6 [] = {3, 0.52, 3};
    GLfloat vv1 [] = {3, 0.52, -1};
    FunctionAux::calculateFlatNormal(v4, v5,v6,vv1, normal);
    glNormal3f(normal[0], normal[1], normal[2]);
    glVertex3f(-3, 0.52, 3);
    glVertex3f(-3, 0.52, -1);
    glVertex3f(3, 0.52, -1);
    glVertex3f(3, 0.52, 3);
    glEnd();

    glBegin(GL_POLYGON);
   
    GLfloat v7 [] = {-3, -0.02, 2.5};
    GLfloat v8 [] = {-3, -0.02, -1};
    GLfloat v9 [] = {3, -0.02, 2.5};
    GLfloat vv2 [] = {3, -0.02, -1};
    FunctionAux::calculateFlatNormal(v7, v8, v9, vv2,normal);
    glNormal3f(normal[0], normal[1], normal[2]);
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
    if(viewerPosition[2]  <= MIN_Z){     //se a nova posição for maior que o limite de Z então redefinimos com o valor pro limite
        viewerPosition[2] = MIN_Z;
    }
    if(viewerPosition[2] >= MAX_Z){     //se a nova posição for maior que o limite de Z então redefinimos com o valor pro limite (colisao)
        viewerPosition[2] = MAX_Z;
    }
    if(viewerPosition[0] <= MIN_X){ 
        viewerPosition[0] = MIN_X;
    }
    if(viewerPosition[0] >= MAX_X){     //se a nova posição for maior que o limite superior de X então redefinimos com o valor pro limite
        viewerPosition[0] = MAX_X;
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

        case GLUT_KEY_UP: // Move up
            viewerPosition[1] += 0.1;

            if(viewerPosition[1] >= MAX_Y){     //implementando colisao no sentido Y
            	viewerPosition[1] = MAX_Y;
            }
            break;
        case GLUT_KEY_DOWN: // Move down
            viewerPosition[1] -= 0.1;

            if(viewerPosition[1] <= MIN_Y){     //implementando colisao no sentido Y
            	viewerPosition[1] = MIN_Y;
            }
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
    
    /* Definição de iluminação */
    glEnable(GL_LIGHTING);
    /* Inicializa para manter a cor do material*/
    glEnable(GL_COLOR_MATERIAL);
    /* Aplica iluminação difusa e ambiente apenas na parte da frente e atrás do objeto*/
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    /* Definição da luz global ambiente para aumentar o brilho dos objetos por padrão*/
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    float globalAmb [] = {0.5f, 0.5f, 0.5f, 1.f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);
   
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
