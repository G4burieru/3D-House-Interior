#include "main_room.h"
#include "functionsAux.h"
#include <GL/glut.h>

void drawCubeMainRoom(float x, float y, float z, float scaleX, float scaleY,
                      float scaleZ, const float *color) {

  // Define specular material and shininess
  GLfloat matSpecular[] = {color[0], color[1], color[2]};
  GLfloat shininess[] = {1.0f};

  // Set material properties for specular reflection
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // Calculate vertices of the cube
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, x, y, z, scaleX, scaleY,
                                             scaleZ);

  GLfloat normal[3]; // Normal vector for lighting
  GLfloat verticeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate the normal for the cube's face
FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD, normal);

  glColor3fv(color);                           // Set cube color
  glPushMatrix();                              // Save current matrix state
  glTranslatef(x, y, z);                       // Move to specified position
  glScalef(scaleX, scaleY, scaleZ);            // Scale the cube
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1f);                         // Draw the cube
  glPopMatrix();                               // Restore previous matrix state
}

void drawPolygonMainRoom(GLfloat vertices[4][3], GLfloat color[3]) {

  // Define specular material color and shininess
  GLfloat matSpecular[] = {color[0], color[1], color[2]};
  GLfloat shininess[] = {1.0f};
  GLfloat normal[3]; // Array for normal vectors

  // Set material properties
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // Calculate the normal for the polygon
  FunctionAux::calculateNormal(vertices[0], vertices[1], vertices[3], normal);

  glBegin(GL_POLYGON);                         // Start drawing the polygon
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting

  // Define the vertices of the polygon
  for (int i = 0; i < 4; i++) {
    glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
  }

  glEnd(); // End drawing the polygon
}

void mainRoomTv() {
  // Define colors
  const float colorWhite[] = {0.9f, 0.9f, 0.9f};
  const float colorShadow[] = {0.0f, 0.01f, 0.0f};
  const float colorLine[] = {0.990f, 0.99901f, 0.9909f};
  const float colorDark[] = {0.0990f, 0.099901f, 0.09909f};
  const float colorGray[] = {0.64f, 0.64f, 0.64f};

  // TV stand
  drawCubeMainRoom(0.96f, 0.2f, 1.73f, 0.1f, 4.0f, 7.0f, colorWhite);

  // Shadow
  drawCubeMainRoom(0.97f, 0.2f, 1.73f, 0.001f, 4.0f, 7.0f, colorShadow);

  // TV
  drawCubeMainRoom(0.9596f, 0.2f, 1.73f, 0.1f, 1.5f, 3.0f, colorDark);

  // Speaker
  drawCubeMainRoom(0.9596f, 0.075f, 2.0f, 0.6f, 1.5f, 0.5f, colorDark);
  drawCubeMainRoom(0.9599f, 0.075f, 2.0f, 0.6f, 1.52f, 0.52f, colorGray);
  drawCubeMainRoom(0.9596f, 0.075f, 1.47f, 0.6f, 1.5f, 0.5f, colorDark);
  drawCubeMainRoom(0.9599f, 0.075f, 1.47f, 0.6f, 1.52f, 0.52f, colorGray);
}

void msofa() {
  // Define colors
  const float colorBase[] = {0.9f, 0.9f, 0.9f};
  const float colorLayer2[] = {0.85f, 0.85f, 0.85f};
  const float colorRest[] = {0.95f, 0.95f, 0.95f};
  const float colorPillow[] = {0.5f, 0.8f, 0.85f};
  const float colorTable[] = {0.95f, 0.95f, 0.95f};
  const float colorTableBase[] = {0.85f, 0.85f, 0.85f};
  const float colorFloor[] = {0.05f, 0.08f, 0.085f};

  // Base
  drawCubeMainRoom(0.0f, 0.002f, 1.7f, 1.2f, 0.5f, 3.0f, colorBase);
  drawCubeMainRoom(0.0f, 0.002f, 2.1f, 1.2f, 0.5f, 3.0f, colorBase);
  drawCubeMainRoom(0.065f, 0.002f, 2.2f, 2.5f, 0.5f, 1.2f, colorBase);
  drawCubeMainRoom(0.065f, 0.002f, 1.6f, 2.5f, 0.5f, 1.2f, colorBase);

  // Layer 2
  drawCubeMainRoom(0.0f, 0.05f, 1.7f, 1.2f, 0.5f, 3.0f, colorLayer2);
  drawCubeMainRoom(0.0f, 0.05f, 2.1f, 1.2f, 0.5f, 3.0f, colorLayer2);
  drawCubeMainRoom(0.065f, 0.05f, 2.2f, 2.5f, 0.5f, 1.2f, colorLayer2);
  drawCubeMainRoom(0.065f, 0.05f, 1.6f, 2.5f, 0.5f, 1.2f, colorLayer2);

  // Rest
  drawCubeMainRoom(-0.06f, 0.05f, 1.7f, 0.4f, 1.5f, 3.1f, colorRest);
  drawCubeMainRoom(-0.06f, 0.05f, 2.115f, 0.4f, 1.5f, 3.1f, colorRest);

  // Draw pillows at specified positions with correct rotation
  float pillowPositions[] = {1.7f, 1.8f, 1.6f,
                             2.0f, 2.1f, 2.2f}; // Positions of the pillows

  for (int i = 0; i < 6; ++i) {
    glPushMatrix(); // Save the current transformation matrix
    glTranslatef(-0.03f, 0.115f,
                 pillowPositions[i]); // Translate to pillow position
    glScalef(0.2f, 0.5f, 0.5f);       // Scale the pillow
    glRotatef(45, 1, 0, 0);           // Rotate for correct orientation
    drawCubeMainRoom(0, 0, 0, 1, 1, 1, colorPillow); // Draw the pillow
    glPopMatrix(); // Restore the previous transformation matrix
  }

  // Table
  drawCubeMainRoom(0.3f, 0.045f, 1.9f, 1.5f, 0.8f, 1.5f, colorTable);
  drawCubeMainRoom(0.3f, 0.005f, 1.9f, 1.55f, 0.2f, 1.55f, colorTableBase);

  // Floor
  drawCubeMainRoom(0.15f, 0.0005f, 1.9f, 7.0f, 0.1f, 10.0f, colorFloor);
}

void mainRoomPainting() {

  // Define colors
  const float white[] = {0.95f, 0.95f, 0.95f};
  const float red[] = {1.0f, 0.0f, 0.0f};
  const float black[] = {0.01f, 0.01f, 0.01f};
  const float darkGray[] = {0.095f, 0.095f, 0.095f};

  // 1st row
  drawCubeMainRoom(-0.47f, 0.4f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // White border
  drawCubeMainRoom(-0.47f, 0.4f, 1.041f, 0.8f, 0.8f, 0.01f,
                   red); // Red interior

  drawCubeMainRoom(-0.3f, 0.4f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // White border
  drawCubeMainRoom(-0.3f, 0.4f, 1.041f, 0.8f, 0.8f, 0.01f,
                   black); // Black interior

  // 2nd row
  drawCubeMainRoom(-0.47f, 0.25f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // White border
  drawCubeMainRoom(-0.47f, 0.25f, 1.041f, 0.8f, 0.8f, 0.01f,
                   black); // Black interior

  drawCubeMainRoom(-0.3f, 0.25f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // White border
  drawCubeMainRoom(-0.3f, 0.25f, 1.041f, 0.8f, 0.8f, 0.01f,
                   red); // Red interior

  // 3rd row
  drawCubeMainRoom(-0.47f, 0.1f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // White border
  drawCubeMainRoom(-0.47f, 0.1f, 1.041f, 0.8f, 0.8f, 0.01f,
                   red); // Red interior

  drawCubeMainRoom(-0.3f, 0.1f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // White border
  drawCubeMainRoom(-0.3f, 0.1f, 1.041f, 0.8f, 0.8f, 0.01f,
                   black); // Black interior

  // Big painting
  drawCubeMainRoom(-0.7f, 0.25f, 1.04f, 2.0f, 2.0f, 0.01f,
                   white); // White layer
  drawCubeMainRoom(-0.7f, 0.25f, 1.041f, 1.7f, 1.7f, 0.01f,
                   darkGray); // Dark gray layer
  drawCubeMainRoom(-0.7f, 0.25f, 1.042f, 1.4f, 1.4f, 0.01f, red); // Red layer
  drawCubeMainRoom(-0.7f, 0.25f, 1.043f, 1.1f, 1.1f, 0.01f,
                   white); // Inner white layer

  // Vertical lines
  drawCubeMainRoom(-0.32f, 0.25f, 1.04f, 0.03f, 5.0f, 0.01f,
                   white); // Vertical line
  drawCubeMainRoom(-0.28f, 0.25f, 1.04f, 0.03f, 5.0f, 0.01f,
                   white); // Vertical line
  drawCubeMainRoom(-0.45f, 0.25f, 1.04f, 0.03f, 5.0f, 0.01f,
                   white); // Vertical line
  drawCubeMainRoom(-0.49f, 0.25f, 1.04f, 0.03f, 5.0f, 0.01f,
                   white); // Vertical line
}

void mainRoomBase() {
  // Cyan walls
  glColor3f(0.5f, 0.8f, 0.85f);
  GLfloat color[] = {0.5f, 0.8f, 0.85f};
  GLfloat rightWall[4][3] = {{0.985f, 0.5f, 1.0f},
                             {0.985f, 0.5f, 4.6f},
                             {0.985f, 0.0f, 4.6f},
                             {0.985f, 0.0f, 1.0f}};
  drawPolygonMainRoom(rightWall, color);

  // Floor base
  glColor3f(0.85f, 0.8f, 0.85f);
  color[0] = 0.85f;
  color[1] = 0.8f;
  color[2] = 0.85f;
  GLfloat lowerFloor[4][3] = {{-1.0f, 0.0f, 1.0f},
                              {1.0f, 0.0f, 1.0f},
                              {1.0f, 0.0f, 3.0f},
                              {-1.0f, 0.0f, 3.0f}};
  drawPolygonMainRoom(lowerFloor, color);

  GLfloat upperFloor[4][3] = {{-1.0f, 0.5f, 1.0f},
                              {1.0f, 0.5f, 1.0f},
                              {1.0f, 0.5f, 3.0f},
                              {-1.0f, 0.5f, 3.0f}};
  drawPolygonMainRoom(upperFloor, color);

  // White wall sections
  glColor3f(0.9f, 0.9f, 0.9f);
  color[0] = 0.9f;
  color[1] = 0.9f;
  color[2] = 0.9f;
  GLfloat upperWall[4][3] = {{1.0f, 0.5f, 1.01f},
                             {1.0f, 0.27f, 1.01f},
                             {-1.0f, 0.27f, 1.01f},
                             {-1.0f, 0.5f, 1.01f}};
  drawPolygonMainRoom(upperWall, color);

  GLfloat leftWall[4][3] = {{0.2f, 0.0f, 1.01f},
                            {0.2f, 0.27f, 1.01f},
                            {-1.0f, 0.27f, 1.01f},
                            {-1.0f, 0.0f, 1.01f}};
  drawPolygonMainRoom(leftWall, color);

  GLfloat rightWall2[4][3] = {{0.4f, 0.0f, 1.01f},
                              {0.4f, 0.27f, 1.01f},
                              {1.0f, 0.27f, 1.01f},
                              {1.0f, 0.0f, 1.01f}};
  drawPolygonMainRoom(rightWall2, color);

  // Black background section
  glColor3f(0.09f, 0.09f, 0.09f);
  color[0] = 0.09f;
  color[1] = 0.09f;
  color[2] = 0.09f;
  GLfloat blackBackground[4][3] = {{-0.2f, 0.0f, 1.011f},
                                   {-0.2f, 0.5f, 1.011f},
                                   {-0.9f, 0.5f, 1.011f},
                                   {-0.9f, 0.0f, 1.011f}};
  drawPolygonMainRoom(blackBackground, color);

  // Entrance section
  glColor3f(0.95f, 0.95f, 0.95f);
  color[0] = 0.95f;
  color[1] = 0.95f;
  color[2] = 0.95f;
  GLfloat entranceLeft[4][3] = {{-0.7f, 0.0f, 3.0f},
                                {-1.0f, 0.0f, 3.0f},
                                {-1.0f, 0.5f, 3.0f},
                                {-0.7f, 0.5f, 3.0f}};
  drawPolygonMainRoom(entranceLeft, color);

  GLfloat entranceRight[4][3] = {{-0.4f, 0.0f, 3.0f},
                                 {1.0f, 0.0f, 3.0f},
                                 {1.0f, 0.5f, 3.0f},
                                 {-0.4f, 0.5f, 3.0f}};
  drawPolygonMainRoom(entranceRight, color);

  GLfloat entranceTop[4][3] = {{-0.7f, 0.3f, 3.0f},
                               {-0.4f, 0.3f, 3.0f},
                               {-0.4f, 0.5f, 3.0f},
                               {-0.7f, 0.5f, 3.0f}};
  drawPolygonMainRoom(entranceTop, color);
}

void mainRoomTop() {
  // Color definitions
  const float brown[] = {0.34f, 0.25f, 0.13f};
  const float white[] = {0.9985f, 0.9985f, 0.9985f};

  // First large brown cube
  drawCubeMainRoom(0.0f, 0.49f, 1.9f, 3.0f, 0.3f, 5.0f, brown);

  // First smaller white cube
  drawCubeMainRoom(0.0f, 0.488f, 1.9f, 2.7f, 0.3f, 4.5f, white);

  // Second large brown cube
  drawCubeMainRoom(0.35f, 0.49f, 1.9f, 3.0f, 0.3f, 5.0f, brown);

  // Second smaller white cube
  drawCubeMainRoom(0.35f, 0.488f, 1.9f, 2.7f, 0.3f, 4.5f, white);
}

void drawMainRoom() {
  // Enable lighting
  glEnable(GL_LIGHT1);
  float light1[4][4] = {
      {0.1f, 0.1f, 0.1f, 1.f},    // Ambient
      {0.08f, 0.08f, 0.08f, 1.f}, // Diffuse
      {0.01f, 0.01f, 0.01f, 1.f}, // Specular
      {0.0f, 0.488f, 1.9f, 1.f}   // Position
  };

  // Set light properties
  glLightfv(GL_LIGHT1, GL_AMBIENT, &light1[0][0]);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, &light1[1][0]);
  glLightfv(GL_LIGHT1, GL_SPECULAR, &light1[2][0]);
  glLightfv(GL_LIGHT1, GL_POSITION, &light1[3][0]);

  // Draw main room components
  mainRoomBase();
  mainRoomTop();
  mainRoomTv();
  mainRoomPainting();
  msofa();
}

void drawMainDoor() {
  // Draw door panels
  glColor3f(0.095, 0.095, 0.095);
  glBegin(GL_POLYGON);
  glVertex3f(-0.7, 0.3, 3);
  glVertex3f(-0.55 - doorPositionX, 0.3, 3 + doorPositionZ);
  glVertex3f(-0.55 - doorPositionX, 0.0, 3 + doorPositionZ);
  glVertex3f(-0.7, 0.0, 3);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-0.4, 0.3, 3);
  glVertex3f(-0.55 + doorPositionX, 0.3, 3 + doorPositionZ);
  glVertex3f(-0.55 + doorPositionX, 0.0, 3 + doorPositionZ);
  glVertex3f(-0.4, 0.0, 3);
  glEnd();

  // Draw door border
  glColor3f(0.23, 0.20, 0.23);
  glBegin(GL_POLYGON);
  glVertex3f(-0.401, 0.3, 3.01);
  glVertex3f(-0.38, 0.3, 3.01);
  glVertex3f(-0.38, 0.0, 3.01);
  glVertex3f(-0.401, 0.0, 3.01);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-0.699, 0.3, 3.01);
  glVertex3f(-0.72, 0.3, 3.01);
  glVertex3f(-0.72, 0.0, 3.01);
  glVertex3f(-0.699, 0.0, 3.01);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-0.38, 0.299, 3.01);
  glVertex3f(-0.72, 0.299, 3.01);
  glVertex3f(-0.72, 0.32, 3.01);
  glVertex3f(-0.38, 0.32, 3.01);
  glEnd();

  if (isDoorClosed) {
    // Draw door design
    glColor3f(0.35, 0.34, 0.35);
    glBegin(GL_POLYGON);
    glVertex3f(-0.65, 0.2, 3.01);
    glVertex3f(-0.6, 0.2, 3.01);
    glVertex3f(-0.6, 0.1, 3.01);
    glVertex3f(-0.65, 0.1, 3.01);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.45, 0.2, 3.01);
    glVertex3f(-0.5, 0.2, 3.01);
    glVertex3f(-0.5, 0.1, 3.01);
    glVertex3f(-0.45, 0.1, 3.01);
    glEnd();

    // Draw door lines
    glColor3f(0.9095, 0.9095, 0.9095);
    glBegin(GL_POLYGON);
    glVertex3f(-0.45, 0.099, 3.01);
    glVertex3f(-0.55, 0.099, 3.01);
    glVertex3f(-0.55, 0.1, 3.01);
    glVertex3f(-0.45, 0.1, 3.01);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.45, 0.3, 3.02);
    glVertex3f(-0.449, 0.3, 3.02);
    glVertex3f(-0.449, 0.05, 3.02);
    glVertex3f(-0.45, 0.05, 3.02);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.65, 0.2, 3.02);
    glVertex3f(-0.55, 0.2, 3.02);
    glVertex3f(-0.55, 0.201, 3.02);
    glVertex3f(-0.65, 0.201, 3.02);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.65, 0.0, 3.02);
    glVertex3f(-0.651, 0.0, 3.02);
    glVertex3f(-0.651, 0.25, 3.02);
    glVertex3f(-0.65, 0.25, 3.02);
    glEnd();
  }
}
