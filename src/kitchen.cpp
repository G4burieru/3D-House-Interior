#include "kitchen.h"
#include "functionsAux.h"
#include <GL/glut.h>
#include <iostream>
#include <vector>

// function that draws any cube in the kitchen
void drawCubeKitchen(float x, float y, float z, float sx, float sy, float sz,
                     const float color[3]) {

  // defining material reflection properties
  GLfloat matSpecular[] = {color[0], color[1], color[2]};
  GLfloat shininess[] = {128.0f};
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // this function calculates the cube's vertices from a central coordinate
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, x, y, z, sx, sy, sz);

  // assigning to another variable the previously obtained kitchen cube vertices
  GLfloat verticeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // calculating the normal for lighting
  GLfloat normal[3];
  FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD,
                                   normal);

  glColor3f(color[0], color[1], color[2]);
  glPushMatrix();
  glTranslatef(x, y, z);
  glScalef(sx, sy, sz);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1f);
  glPopMatrix();
}

void drawPolygonKitchen(const float color[3], const float vertices[][3],
                        int vertexCount) {

  // defining material reflection properties
  glColor3f(color[0], color[1], color[2]);
  GLfloat matSpecular[] = {color[0], color[1], color[2]};
  GLfloat shininess[] = {128.0f};
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // calculating the normal
  GLfloat normal[3];
  FunctionAux::calculateFlatNormal(vertices[0], vertices[1], vertices[2],
                                   vertices[3], normal);

  // draws any polygon according to the number and position of the vertices
  // passed to the function
  glBegin(GL_POLYGON);
  glNormal3f(normal[0], normal[1], normal[2]);
  for (int i = 0; i < vertexCount; ++i) {
    glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
  }
  glEnd();
}

// drawing the kitchen cabinet
void drawKitchenCabinet() {
  const float colorDarkGray[] = {0.22f, 0.22f, 0.22f};
  const float colorLightBrown[] = {0.85f, 0.69f, 0.35f};
  const float colorLightGray[] = {0.85f, 0.81f, 0.72f};
  const float colorBlack[] = {0.1f, 0.1f, 0.1f};
  const float colorWhite[] = {0.9f, 0.9f, 0.9f};
  const float colorBlackAccent[] = {0.05f, 0.05f, 0.05f};

  // Front
  drawCubeKitchen(-2.7f, 0.17f, 1.585f, 5.0f, 3.5f, 1.6f, colorDarkGray);
  drawCubeKitchen(-1.7f, 0.17f, 1.585f, 5.0f, 3.5f, 1.6f, colorDarkGray);
  drawCubeKitchen(-2.2f, 0.11f, 1.585f, 5.0f, 2.5f, 1.6f, colorLightBrown);

  // Back
  drawCubeKitchen(-2.9f, 0.06f, 2.25f, 2.0f, 2.0f, 10.0f, colorLightGray);
  drawCubeKitchen(-2.9f, 0.166f, 2.25f, 2.0f, 0.1f, 10.0f, colorBlack);
  drawCubeKitchen(-2.88f, 0.0f, 2.25f, 2.0f, 0.1f, 10.0f, colorBlack);
  drawCubeKitchen(-2.9f, 0.06f, 2.755f, 2.0f, 2.1f, 0.1f, colorLightGray);

  // Side
  drawCubeKitchen(-1.8f, 0.06f, 2.93f, 7.0f, 2.0f, 1.6f, colorDarkGray);
  drawCubeKitchen(-1.4f, 0.06f, 2.7f, 1.6f, 2.0f, 6.0f, colorDarkGray);

  // White accents
  drawCubeKitchen(-1.32f, 0.07f, 2.71f, 0.1f, 0.8f, 5.5f, colorWhite);
  drawCubeKitchen(-1.485f, 0.07f, 2.71f, 0.1f, 0.8f, 5.5f, colorWhite);
  drawCubeKitchen(-1.83f, 0.07f, 2.85f, 5.6f, 0.8f, 0.1f, colorWhite);

  // Black accents
  drawCubeKitchen(-1.8f, 0.165f, 2.93f, 7.0f, 0.1f, 1.75f, colorBlackAccent);
  drawCubeKitchen(-1.4f, 0.165f, 2.7f, 1.75f, 0.1f, 6.0f, colorBlackAccent);
}

void drawDetails() {
  const float colorBlack[] = {0.1f, 0.1f, 0.1f};
  const float colorWhite[] = {0.9f, 0.9f, 0.9f};

  // Draw fridge door's dividers
  drawCubeKitchen(-1.59f, 0.17f, 1.672f, 0.01f, 3.5f, 0.05f, colorWhite);
  drawCubeKitchen(-1.8f, 0.17f, 1.672f, 0.01f, 3.5f, 0.05f, colorWhite);
  drawCubeKitchen(-2.6f, 0.17f, 1.672f, 0.01f, 3.5f, 0.05f, colorWhite);
  drawCubeKitchen(-2.8f, 0.17f, 1.672f, 0.01f, 3.5f, 0.05f, colorWhite);

  // Draw black lines
  drawCubeKitchen(-2.1f, 0.11f, 1.672f, 0.01f, 2.5f, 0.05f, colorBlack);
  drawCubeKitchen(-2.3f, 0.11f, 1.672f, 0.01f, 2.5f, 0.05f, colorBlack);

  // Draw black detail on the drawers wall
  drawCubeKitchen(-3.0f, 0.44f, 2.25f, 0.1f, 1.2f, 15.0f, colorBlack);
  drawCubeKitchen(-3.0f, 0.2f, 2.88f, 0.1f, 4.0f, 2.5f, colorBlack);

  // Draw drawer's dividers
  drawCubeKitchen(-2.79f, 0.08f, 2.25f, 0.05f, 0.05f, 10.0f, colorBlack);
  drawCubeKitchen(-2.8f, 0.06f, 2.5f, 0.05f, 2.1f, 0.05f, colorBlack);
  drawCubeKitchen(-2.8f, 0.06f, 2.25f, 0.05f, 2.1f, 0.05f, colorBlack);
  drawCubeKitchen(-2.8f, 0.06f, 2.1f, 0.05f, 2.1f, 0.05f, colorBlack);
  drawCubeKitchen(-2.8f, 0.06f, 1.95f, 0.05f, 2.1f, 0.05f, colorBlack);
}

void drawHandles() {

  // Set color for handles
  const float colorHandle[] = {0.5f, 0.5f, 0.5f};

  // Small cabinet handles
  drawCubeKitchen(-2.8f, 0.13f, 2.45f, 0.05f, 0.15f, 0.55f, colorHandle);
  drawCubeKitchen(-2.8f, 0.06f, 2.45f, 0.05f, 0.15f, 0.55f, colorHandle);
  drawCubeKitchen(-2.8f, 0.06f, 2.55f, 0.05f, 0.15f, 0.55f, colorHandle);
  drawCubeKitchen(-2.8f, 0.13f, 2.55f, 0.05f, 0.15f, 0.55f, colorHandle);
  drawCubeKitchen(-2.8f, 0.13f, 2.05f, 0.05f, 0.15f, 0.55f, colorHandle);
  drawCubeKitchen(-2.8f, 0.06f, 2.05f, 0.05f, 0.15f, 0.55f, colorHandle);
  drawCubeKitchen(-2.8f, 0.06f, 2.15f, 0.05f, 0.15f, 0.55f, colorHandle);
  drawCubeKitchen(-2.8f, 0.13f, 2.15f, 0.05f, 0.15f, 0.55f, colorHandle);
  drawCubeKitchen(-2.8f, 0.13f, 1.9f, 0.05f, 0.15f, 0.55f, colorHandle);
  drawCubeKitchen(-2.8f, 0.06f, 1.9f, 0.05f, 0.15f, 0.55f, colorHandle);

  // Tall cabinet handles
  drawCubeKitchen(-2.36f, 0.21f, 1.671f, 0.5f, 0.15f, 0.05f, colorHandle);
  drawCubeKitchen(-2.0f, 0.21f, 1.671f, 0.5f, 0.15f, 0.05f, colorHandle);
  drawCubeKitchen(-1.85f, 0.3f, 1.671f, 0.5f, 0.15f, 0.05f, colorHandle);
  drawCubeKitchen(-1.535f, 0.3f, 1.671f, 0.5f, 0.15f, 0.05f, colorHandle);
  drawCubeKitchen(-2.65f, 0.3f, 1.671f, 0.5f, 0.15f, 0.05f, colorHandle);
  drawCubeKitchen(-2.55f, 0.3f, 1.671f, 0.5f, 0.15f, 0.05f, colorHandle);
  drawCubeKitchen(-1.63f, 0.19f, 1.671f, 0.15f, 0.5f, 0.05f, colorHandle);
}

// Drawing the oven
void drawOven() {
  const float gray[3] = {0.58f, 0.58f, 0.58f};
  const float darkGray[3] = {0.058f, 0.058f, 0.058f};

  // First cube
  drawCubeKitchen(-2.2, 0.07, 1.68, 1.93, 1.0, 0.01, gray);

  // Second cube
  drawCubeKitchen(-2.2, 0.07, 1.681, 1.92, 0.7, 0.01, darkGray);

  // Third cube
  drawCubeKitchen(-2.2, 0.18, 1.68, 1.93, 1.0, 0.01, gray);

  // Fourth cube
  drawCubeKitchen(-2.2, 0.18, 1.681, 1.92, 0.7, 0.01, darkGray);

  // Fifth cube
  drawCubeKitchen(-2.2, 0.18, 1.682, 1.5, 0.4, 0.01, gray);
}

void drawCabinetChair() {
  GLUquadricObj *quadratic;
  quadratic = gluNewQuadric(); // Create a new quadric object

  glColor3f(0.58, 0.56, 0.56); // Color for the chair leg
  glPushMatrix();
  glTranslatef(-1.8, 0.13, 2.63);                       // Position the leg
  glRotatef(90, 1, 0, 0);                               // Rotate to vertical
  gluCylinder(quadratic, 0.01, 0.005, 0.125, 100, 100); // Draw leg
  glPopMatrix();

  glColor3f(0.09, 0.09, 0.09); // Color for the seat
  glPushMatrix();
  glTranslatef(-1.8, 0.01, 2.63);  // Position the seat
  glScalef(1, 0.15, 1);            // Flatten for seat
  glutSolidSphere(0.04, 100, 100); // Draw seat
  glPopMatrix();

  glColor3f(0.85, 0.69, 0.35); // Color for back support
  glPushMatrix();
  glTranslatef(-1.8, 0.15, 2.63);                     // Position back support
  glRotatef(90, 1, 0, 0);                             // Rotate to vertical
  gluCylinder(quadratic, 0.05, 0.05, 0.02, 100, 100); // Draw support
  glPopMatrix();

  glColor3f(0.85, 0.69, 0.35); // Color for back cushion
  glPushMatrix();
  glTranslatef(-1.8, 0.15, 2.63);  // Position cushion
  glScalef(1, 0.15, 1);            // Flatten for cushion
  glutSolidSphere(0.05, 100, 100); // Draw cushion
  glPopMatrix();

  glColor3f(0.85, 0.69, 0.35); // Color for leg detail
  glPushMatrix();
  glTranslatef(-1.8, 0.13, 2.63);                       // Position detail
  glRotatef(90, 1, 0, 0);                               // Rotate to vertical
  gluCylinder(quadratic, 0.01, 0.009, 0.035, 100, 100); // Draw detail
  glPopMatrix();
}

void kitchenBase() {
  // Define colors
  const float brown[3] = {0.68f, 0.54f, 0.32f};
  const float lightGray[3] = {0.9f, 0.9f, 0.9f};
  const float gray[3] = {0.85f, 0.8f, 0.85f};
  const float blue[3] = {0.68f, 0.8f, 0.9f};
  const float black[3] = {0.0f, 0.0f, 0.0f};
  const float white[3] = {0.95f, 0.98f, 0.985f};

    //definindo os vertices e desenhando o piso da cozinha 
  float vertices1[][3] = {
      {-1, 0.0, 3}, {-3, 0.0, 3}, {-3, 0.0, 1.5}, {-1, 0.0, 1.5}};
  drawPolygonKitchen(brown, vertices1, 4);         

  //definindo os vertices e desenhando paredes internas da cozinha
  float vertices2[][3] = {
      {-3, 0.0, 1.5}, {-1, 0.0, 1.5}, {-1, 0.5, 1.5}, {-3, 0.5, 1.5}};
  drawPolygonKitchen(lightGray, vertices2, 4);
  float vertices3[][3] = {
      {-3, 0.0, 3}, {-1, 0.0, 3}, {-1, 0.5, 3}, {-3, 0.5, 3}};
  drawPolygonKitchen(lightGray, vertices3, 4);
  float vertices5[][3] = {
      {-3, 0.0, 1.5}, {-3, 0.5, 1.5}, {-3, 0.5, 3}, {-3, 0.0, 3}};
  drawPolygonKitchen(lightGray, vertices5, 4);

   //desenhando o teto
  float vertices4[][3] = {
      {-1, 0.5, 3}, {-3, 0.5, 3}, {-3, 0.5, 1.5}, {-1, 0.5, 1.5}};
  drawPolygonKitchen(gray, vertices4, 4);

   //desenha a parede da entrada da cozinha
  float vertices6[][3] = {
      {-1, 0.0, 1.5}, {-1, 0.5, 1.5}, {-1, 0.5, 1.85}, {-1, 0.0, 1.85}};
  drawPolygonKitchen(blue, vertices6, 4);
  float vertices7[][3] = {
      {-1, 0.0, 1.5}, {-1, 0.5, 1.5}, {-1, 0.5, 0.85}, {-1, 0.0, 0.85}};
  drawPolygonKitchen(blue, vertices7, 4);
  float vertices8[][3] = {
      {-1, 0.35, 1.5}, {-1, 0.5, 1.5}, {-1, 0.5, 3}, {-1, 0.35, 3}};
  drawPolygonKitchen(blue, vertices8, 4);

  //detalhes brancos na parede de entrada
  glColor3f(white[0], white[1], white[2]);
  for (float yOffset = 0.14f; yOffset <= 0.4f; yOffset += 0.135f) {
    glPushMatrix();
    glTranslatef(-0.99, yOffset, 1.66);
    glScalef(0.1, 1, 1.5);
    glutSolidCube(0.1);
    glPopMatrix();
  }
}

//funcao principal que desenha todos os detalhes da cozinha
void drawKitchen() {

  glEnable(GL_LIGHT3); // Enable light source 3
  float light3[4][4] = {
      {0.05f, 0.05f, 0.05f, 1.f}, // Ambient light
      {0.08f, 0.08f, 0.08f, 1.f}, // Diffuse light
      {0.01f, 0.01f, 0.01f, 1.f}, // Specular light
      {-1.8, 0.13, 2.63, 1.f}     // Light position
  };
  // Set light properties
  glLightfv(GL_LIGHT3, GL_AMBIENT, &light3[0][0]);
  glLightfv(GL_LIGHT3, GL_DIFFUSE, &light3[1][0]);
  glLightfv(GL_LIGHT3, GL_SPECULAR, &light3[2][0]);
  glLightfv(GL_LIGHT3, GL_POSITION, &light3[3][0]);

  GLfloat matSpecular[] = {1.f, 1.f, 1.f, 1.f}; // Material specular color
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  GLfloat shininess[] = {128.0f}; // Material shininess
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

  kitchenBase(); // Draw the kitchen base

  glPushMatrix();
  glTranslatef(-0.2, 0.0, 0.0); // Position for the chair
  drawCabinetChair();           // Draw the cabinet chair
  glPopMatrix();

  drawCabinetChair();   // Draw another cabinet chair
  drawKitchenCabinet(); // Draw the kitchen cabinet
  drawOven();           // Draw the oven
  drawHandles();        // Draw handles
  drawDetails();        // Draw additional details
}
