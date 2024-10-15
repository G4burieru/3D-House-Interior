#include "kitchen.h"
#include "main_room.h"
#include "room1.h"

#include "functionsAux.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MIN_X -2.5 // Minimum X coordinate
#define MAX_X 0.8  // Maximum X coordinate
#define MIN_Y 0.1  // Minimum Y coordinate
#define MAX_Y 0.5  // Maximum Y coordinate
#define MIN_Z -0.5 // Minimum Z coordinate
#define MAX_Z 5.0  // Maximum Z coordinate

// Door position variables
GLfloat doorPositionX = 0.0, doorPositionZ = 0.0;
int isDoorClosed = 1; // Door state (closed = 1)
float lookAtX = 0.0f, lookAtZ = -1.0f, rotationAngle = 0.0f;
static GLdouble viewerPosition[] = {0.0, 0.2, 4.2}; // Viewer position
static GLdouble lookAtPosition[] = {0.0, 0.2, 0.0}; // Look-at position

// RGB color values
GLfloat colorRed = 0, colorGreen = 0, colorBlue = 0;

void *fontStyle = GLUT_BITMAP_HELVETICA_18; // Font style for rendering text

void renderText(float x, float y, const char *text) {
  // Set text position
  glRasterPos2f(x, y);
  // Render each character of the string
  for (unsigned int i = 0; i < strlen(text); i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
  }
}

void updateColors(int) {
  // Increment RGB values
  colorRed += 0.01;
  colorBlue += 0.001;
  colorGreen += 0.0001;

  // Reset if values exceed 1.0
  if (colorRed > 1.0)
    colorRed = 0;
  if (colorBlue > 1.0)
    colorBlue = 0;
  if (colorGreen > 1.0)
    colorGreen = 0;

  glutPostRedisplay();                 // Request display update
  glutTimerFunc(100, updateColors, 0); // Call again after 100ms
}

void openDoor(int v) {
  // Increment door position within limits
  if (doorPositionX < 0.2 && doorPositionZ < 0.2) {
    doorPositionX += 0.01;
    doorPositionZ += 0.01;
  }
  isDoorClosed = 0; // Mark door as open

  glutPostRedisplay();             // Request display update
  glutTimerFunc(100, openDoor, 0); // Call again after 100ms
}

void displayText() {
  if (isDoorClosed) {
    // Show door prompt
    renderText(-0.999, -0.500, "Press 'O' to open the door");
    glFlush(); // Force rendering
  }
}

void drawOuterCover() {
  // Set material color and properties
  glColor3f(196.0f / 255.0f, 160.0f / 255.0f, 112.0f / 255.0f);
  GLfloat matSpecular[] = {1.f, 1.f, 1.f, 1.f};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  GLfloat shininess[] = {128.0f};
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

  GLfloat normal[3];
  glBegin(GL_POLYGON);

  // Compute normal for first polygon
  GLfloat v0[] = {-1, 0.0, 3};
  GLfloat v1[] = {-1, 0.5, 3};
  GLfloat v3[] = {-1, 0.0, 4};
  GLfloat vv[] = {-1, 0.5, 4};
  FunctionAux::calculateFlatNormal(v0, v1, v3, vv, normal);

  glNormal3f(normal[0], normal[1], normal[2]); // Apply normal
  glVertex3f(v0[0], v0[1], v0[2]);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(-1, 0.5, 4);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  glBegin(GL_POLYGON);

  // Compute normal for second polygon
  GLfloat v4[] = {-3, 0.52, 3};
  GLfloat v5[] = {-3, 0.52, -1};
  GLfloat v6[] = {3, 0.52, 3};
  GLfloat vv1[] = {3, 0.52, -1};
  FunctionAux::calculateFlatNormal(v4, v5, v6, vv1, normal);
  glNormal3f(normal[0], normal[1], normal[2]); // Apply normal
  glVertex3f(-3, 0.52, 3);
  glVertex3f(-3, 0.52, -1);
  glVertex3f(3, 0.52, -1);
  glVertex3f(3, 0.52, 3);
  glEnd();

  glBegin(GL_POLYGON);

  // Compute normal for third polygon
  GLfloat v7[] = {-3, -0.02, 2.5};
  GLfloat v8[] = {-3, -0.02, -1};
  GLfloat v9[] = {3, -0.02, 2.5};
  GLfloat vv2[] = {3, -0.02, -1};
  FunctionAux::calculateFlatNormal(v7, v8, v9, vv2, normal);
  glNormal3f(normal[0], normal[1], normal[2]); // Apply normal
  glVertex3f(-3, -0.02, 2.5);
  glVertex3f(-3, -0.02, -1);
  glVertex3f(3, -0.02, -1);
  glVertex3f(3, -0.02, 2.5);
  glEnd();
}

void renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Set camera position and look direction
  gluLookAt(viewerPosition[0], viewerPosition[1], viewerPosition[2],
            viewerPosition[0] + lookAtX, lookAtPosition[1],
            viewerPosition[2] + lookAtZ, 0.0, 1.0, 0.0);

  // Display text on the scene
  glPushMatrix();
  glTranslatef(0.0, 0.2, 3.2);
  glScalef(0.5, 0.5, 0.0);
  displayText();
  glPopMatrix();

  // Draw various parts of the house
  drawOuterCover();
  drawMainDoor();
  drawRoom1();
  drawKitchen();
  drawMainRoom();

  glutSwapBuffers(); // Swap buffers for double buffering
}

void handleKeyPress(unsigned char key, int x, int y) {
  // User movement with W, A, S, D
  switch (key) {
  case 'w': // Move forward
    viewerPosition[0] += lookAtX * 0.1;
    viewerPosition[2] += lookAtZ * 0.1;
    break;

  case 's': // Move backward
    viewerPosition[0] -= lookAtX * 0.1;
    viewerPosition[2] -= lookAtZ * 0.1;
    break;

  case 'a': // Strafe left
    viewerPosition[0] -= cos(rotationAngle) * 0.01;
    viewerPosition[2] += sin(rotationAngle) * 0.01;
    break;

  case 'd': // Strafe right
    viewerPosition[0] += cos(rotationAngle) * 0.01;
    viewerPosition[2] -= sin(rotationAngle) * 0.01;
    break;

  case 'o': // Open the door
    openDoor(0);
    break;
  }

  // Collision detection for movement boundaries
  if (viewerPosition[2] <= MIN_Z)
    viewerPosition[2] = MIN_Z;
  if (viewerPosition[2] >= MAX_Z)
    viewerPosition[2] = MAX_Z;
  if (viewerPosition[0] <= MIN_X)
    viewerPosition[0] = MIN_X;
  if (viewerPosition[0] >= MAX_X)
    viewerPosition[0] = MAX_X;

  glutPostRedisplay(); // Refresh the scene
}

void handleSpecialKeyPress(int key, int x, int y) {
  float rotationSpeed = 0.04f; // Rotation speed

  switch (key) {
  case GLUT_KEY_LEFT: // Rotate left
    rotationAngle -= rotationSpeed;
    break;
  case GLUT_KEY_RIGHT: // Rotate right
    rotationAngle += rotationSpeed;
    break;
  case GLUT_KEY_UP: // Move up
    viewerPosition[1] += 0.1;

    // Collision detection for upper Y limit
    if (viewerPosition[1] >= MAX_Y) {
      viewerPosition[1] = MAX_Y;
    }
    break;
  case GLUT_KEY_DOWN: // Move down
    viewerPosition[1] -= 0.1;

    // Collision detection for lower Y limit
    if (viewerPosition[1] <= MIN_Y) {
      viewerPosition[1] = MIN_Y;
    }
    break;
  }

  // Update direction based on new rotation angle
  lookAtX = sin(rotationAngle);
  lookAtZ = -cos(rotationAngle);

  glutPostRedisplay(); // Refresh display
}

void adjustViewportSize(int width, int height) {
  if (height == 0)
    height = 1; // Avoid division by zero
  float aspectRatio = width * 1.0 / height;

  // Set viewport and adjust perspective
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0f, aspectRatio, 0.1f, 10.0f);
  glMatrixMode(GL_MODELVIEW);

  glutPostRedisplay(); // Refresh display
}

int main(int argc, char **argv) {
  // Initialize GLUT and set display mode with double buffering and RGBA colors
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);

  // Set window size and position
  glutInitWindowSize(1000, 800);
  glutInitWindowPosition(0, 0);

  // Create the main window
  glutCreateWindow("3D House Architecture");

  // Enable lighting
  glEnable(GL_LIGHTING);

  // Enable material color handling
  glEnable(GL_COLOR_MATERIAL);

  // Set material color to affect both front and back of objects
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  // Set global ambient lighting
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  float globalAmb[] = {0.5f, 0.5f, 0.5f, 1.f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

  // Set up view matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Register display and reshape functions
  glutDisplayFunc(renderScene);
  glutReshapeFunc(adjustViewportSize);

  // Set depth function and handle input events
  glDepthFunc(GL_LEQUAL);
  glutSpecialFunc(handleSpecialKeyPress);
  glutKeyboardFunc(handleKeyPress);

  // Enable transparency and depth testing
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);

  // Initialize colors and enable alpha testing
  updateColors(0);
  glAlphaFunc(GL_GREATER, 0.1);
  glEnable(GL_ALPHA_TEST);

  // Set the background color to white
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // Start the main event loop
  glutMainLoop();

  return 0;
}
