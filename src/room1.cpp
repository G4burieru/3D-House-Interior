#include "room1.h"
#include "functionsAux.h"
#include <GL/glut.h>
#include <vector>

void drawLine(float x1, float z1, float x2, float z2) {
  // Start drawing lines
  glBegin(GL_LINES);

  // Specify the start vertex
  glVertex3f(x1, 0.0f, z1);

  // Specify the end vertex
  glVertex3f(x2, 0.0f, z2);

  // End drawing
  glEnd();
}

void lines() {
  glColor3f(0.0f, 0.0f, 0.0f); // Set line color to black
  glLineWidth(0.2f);           // Set line width

  // Draw horizontal lines
  for (float x = -0.8f; x <= 1.0f; x += 0.2f) {
    drawLine(x, 1.0f, x, -1.0f); // Draw line at current x position
  }

  // Draw vertical lines
  for (float z = -0.8f; z <= 1.0f; z += 0.2f) {
    drawLine(-1.0f, z, 1.0f, z); // Draw line at current z position
  }
}

void drawPolygon(const std::vector<GLfloat> &vertices, const GLfloat *color) {
  GLfloat matSpecular[] = {color[0], color[1], color[2],
                           1.0f}; // Specular material color
  GLfloat shininess[] = {1.0f};   // Material shininess

  glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Set material shininess
  glMaterialfv(GL_FRONT, GL_SPECULAR,
               matSpecular); // Set material specular color
  glColor3fv(color);         // Set polygon color
  glBegin(GL_POLYGON);       // Start drawing polygon
  for (size_t i = 0; i < vertices.size(); i += 3) {
    glVertex3f(vertices[i], vertices[i + 1],
               vertices[i + 2]); // Specify vertex positions
  }
  glEnd(); // Finish drawing
}

void drawCube(const GLfloat *color, float x, float y, float z, float scaleX,
              float scaleY, float scaleZ) {
  GLfloat matSpecular[] = {color[0], color[1], color[2],
                           1.0f}; // Specular material color
  GLfloat shininess[] = {1.0f};   // Material shininess

  glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Set material shininess
  glMaterialfv(GL_FRONT, GL_SPECULAR,
               matSpecular); // Set material specular color

  // Calculate cube face vertices
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, x, y, z, scaleX, scaleY,
                                             scaleZ);
  GLfloat normal[3]; // Normal vector for lighting
  GLfloat verticeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD,
                                   normal); // Calculate flat normal

  glColor3fv(color);                           // Set cube color
  glPushMatrix();                              // Save current matrix
  glTranslatef(x, y, z);                       // Translate to position
  glScalef(scaleX, scaleY, scaleZ);            // Scale cube
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1f);                         // Draw solid cube
  glPopMatrix();                               // Restore previous matrix
}

void redwall() {
  // Set up specular material properties
  GLfloat matSpecular[] = {1.f, 1.f, 1.f, 1.f}; // Specular color
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  GLfloat shininess[] = {128.0f}; // Shininess factor
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

  GLfloat normal[] = {0.0f, 0.0f, 1.0f}; // Normal vector for the surfaces

  //--------------dark red top---------------------
  GLfloat darkRed[] = {0.53f, 0.12f, 0.12f}; // Dark red color for the top
  glNormal3f(normal[0], normal[1], normal[2]);
  drawPolygon({-0.98, 0.0, 1, -0.98, 0.5, 1, -0.98, 0.5, 0.9, -0.98, 0.0, 0.9},
              darkRed);
  drawPolygon(
      {-0.98, 0.5, 0.9, -0.98, 0.5, -0.2, -0.98, 0.4, -0.2, -0.98, 0.4, 0.9},
      darkRed);
  drawPolygon(
      {-0.98, 0.5, -0.3, -0.98, 0.0, -0.3, -0.98, 0.0, -0.2, -0.98, 0.5, -0.2},
      darkRed);

  //--------------grey mid--------------
  GLfloat grey[] = {0.69f, 0.58f, 0.56f}; // Grey color for the middle section
  glNormal3f(normal[0], normal[1], normal[2]);
  drawPolygon(
      {-0.98, 0.0, 0.9, -0.98, 0.4, 0.9, -0.98, 0.4, 0.7, -0.98, 0.0, 0.7},
      grey);
  drawPolygon(
      {-0.98, 0.4, 0.7, -0.98, 0.4, 0.0, -0.98, 0.25, 0.0, -0.98, 0.25, 0.7},
      grey);
  drawPolygon(
      {-0.98, 0.4, -0.2, -0.98, 0.0, -0.2, -0.98, 0.0, 0.0, -0.98, 0.4, 0.0},
      grey);

  //--------------black----------------
  GLfloat black[] = {0.15f, 0.11f, 0.11f}; // Black color for the lower section
  glNormal3f(normal[0], normal[1], normal[2]);
  drawPolygon(
      {-0.98, 0.0, 0.7, -0.98, 0.25, 0.7, -0.98, 0.25, 0.65, -0.98, 0.0, 0.65},
      black);
  drawPolygon(
      {-0.98, 0.25, 0.65, -0.98, 0.25, 0.0, -0.98, 0.2, 0.0, -0.98, 0.2, 0.65},
      black);
  drawPolygon(
      {-0.98, 0.25, 0.0, -0.98, 0.0, 0.0, -0.98, 0.0, 0.05, -0.98, 0.25, 0.05},
      black);

  //-------------black drawer---------
  GLfloat blackDrawerColor[] = {0.0f, 0.0f, 0.0f};
  glNormal3f(0.5f, 0.5f, 0.5f); // Normal for drawer surfaces
  drawCube(blackDrawerColor, -0.95f, 0.06f, 0.8f, 1.1f, 0.4f,
           1.5f);             // Main drawer
  blackDrawerColor[0] = 1.0f; // Change to white color for the smaller drawer
  drawCube(blackDrawerColor, -0.92f, 0.06f, 0.8f, 0.56f, 0.15f,
           1.45f); // Smaller drawer

  //---------bed(1st layer)------------
  GLfloat bed1stColor[] = {0.15f, 0.11f,
                           0.11f}; // Color for the first layer of the bed
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(bed1stColor, -0.7f, 0.01f, 0.36f, 6.0f, 0.25f,
           5.0f); // First layer of the bed

  //----------2nd layer)---------------
  GLfloat layer2ndColor[] = {0.17f, 0.13f,
                             0.12f}; // Color for the second layer of the bed
  drawCube(layer2ndColor, -0.7f, 0.04f, 0.36f, 6.0f, 0.3f,
           5.2f); // Second layer of the bed

  //----------bed-----------
  GLfloat bedColor[] = {0.84f, 0.72f, 0.69f}; // Color for the bed
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(bedColor, -0.7f, 0.065f, 0.36f, 5.9f, 0.3f, 5.1f); // Main bed

  //--------------bedsheet----------------
  GLfloat bedsheetColor[] = {0.86f, 0.52f, 0.55f}; // Color for the bedsheet
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(bedsheetColor, -0.5f, 0.069f, 0.36f, 2.5f, 0.3f,
           5.2f); // Draw bedsheet

  //--------------pillow---------------
  GLfloat pillowColor[] = {0.86f, 0.52f, 0.55f}; // Color for the pillow
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(pillowColor, -0.9f, 0.1f, 0.5f, 1.0f, 0.2f, 1.5f);  // First pillow
  drawCube(pillowColor, -0.9f, 0.1f, 0.25f, 1.0f, 0.2f, 1.5f); // Second pillow

  //-------light-------
  GLfloat lightColor[] = {1.0f, 1.0f, 1.0f}; // Color for the light
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(lightColor, -0.98f, 0.3f, -0.1f, 0.03f, 0.07f,
           0.03f); // Light on one side
  drawCube(lightColor, -0.98f, 0.3f, 0.8f, 0.03f, 0.07f,
           0.03f); // Light on the other side
}

void greywall() {
  // Define material properties for specular highlights
  GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat shininess[] = {16.0f};

  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // Draw the first cube
  {
    std::vector<std::array<GLfloat, 3>> vertices =
        FunctionAux::calculateCubeFaceVertices(0.08, -0.55, 0.32, 0.0f - 0.9, 1,
                                               1, 1);
    GLfloat normal[3];
    GLfloat verticeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
    GLfloat verticeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
    GLfloat verticeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
    GLfloat verticeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

    // Calculate normal for the cube face
    FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD,
                                     normal);

    glColor3f(0.91, 0.91, 0.89); // Set color
    glPushMatrix();
    glTranslatef(-0.55, 0.32, 0.0f - 0.9);       // Translate to position
    glNormal3f(normal[0], normal[1], normal[2]); // Set normal
    glutSolidCube(0.08);                         // Draw cube
    glPopMatrix();
  }

  // Draw the second cube
  {
    std::vector<std::array<GLfloat, 3>> vertices2 =
        FunctionAux::calculateCubeFaceVertices(0.08, -0.42, 0.28, 0.0f - 0.9, 1,
                                               1, 1);
    GLfloat normal[3];
    GLfloat verticeE[3] = {vertices2[0][1], vertices2[0][2], vertices2[0][3]};
    GLfloat verticeF[3] = {vertices2[1][1], vertices2[1][2], vertices2[1][3]};
    GLfloat verticeG[3] = {vertices2[2][1], vertices2[2][2], vertices2[2][3]};
    GLfloat verticeH[3] = {vertices2[3][1], vertices2[3][2], vertices2[3][3]};

    // Calculate normal for the cube face
    FunctionAux::calculateFlatNormal(verticeE, verticeF, verticeG, verticeH,
                                     normal);

    glColor3f(0.91, 0.91, 0.89); // Set color
    glPushMatrix();
    glTranslatef(-0.42, 0.28, 0.0f - 0.9);       // Translate to position
    glNormal3f(normal[0], normal[1], normal[2]); // Set normal
    glutSolidCube(0.08);                         // Draw cube
    glPopMatrix();
  }

  // Draw the third cube
  {
    std::vector<std::array<GLfloat, 3>> vertices =
        FunctionAux::calculateCubeFaceVertices(0.08, -0.42, 0.28, 0.0f - 0.9, 1,
                                               1, 1);
    GLfloat normal[3];
    GLfloat verticee[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
    GLfloat verticee1[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
    GLfloat verticee2[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
    GLfloat verticee3[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

    // Calculate normal for the cube face
    FunctionAux::calculateFlatNormal(verticee, verticee1, verticee2, verticee3,
                                     normal);

    glColor3f(0.91, 0.91, 0.89); // Set color
    glPushMatrix();
    glTranslatef(-0.31, 0.32, 0.0f - 0.9);       // Translate to position
    glNormal3f(normal[0], normal[1], normal[2]); // Set normal
    glutSolidCube(0.08);                         // Draw cube
    glPopMatrix();
  }

  // Draw the fourth cube
  {
    std::vector<std::array<GLfloat, 3>> vertices =
        FunctionAux::calculateCubeFaceVertices(0.08, -0.2, 0.28, 0.0f - 0.9, 1,
                                               1, 1);
    GLfloat normal[3];
    GLfloat verticee4[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
    GLfloat verticee5[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
    GLfloat verticee6[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
    GLfloat verticee7[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

    // Calculate normal for the cube face
    FunctionAux::calculateFlatNormal(verticee4, verticee5, verticee6, verticee7,
                                     normal);

    glColor3f(0.91, 0.91, 0.89); // Set color
    glPushMatrix();
    glTranslatef(-0.2, 0.28, 0.0f - 0.9); // Translate to position
    glutSolidCube(0.08);                  // Draw cube
    glPopMatrix();
  }
}

void wardrobe() {
  //-------------- Wall Configuration --------
  GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Specular color
  GLfloat shininess[] = {16.0f}; // Shininess value for material

  glMaterialfv(GL_FRONT, GL_SHININESS, shininess); // Set material shininess
  glMaterialfv(GL_FRONT, GL_SPECULAR,
               matSpecular); // Set material specular color

  // Calculate wall vertices
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, -0.99, 0.25, -0.8, 0.5, 5, 4);

  GLfloat normal[3]; // Array to store calculated normal vector
  GLfloat wallA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat wallB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat wallC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat wallD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate and set normal for the wall
  FunctionAux::calculateFlatNormal(wallA, wallB, wallC, wallD, normal);

  // Set wall color and draw the left wall
  glColor3f(0.47, 0.35, 0.26);
  glPushMatrix();
  glTranslatef(-0.99, 0.25, -0.8);             // Translate to position
  glScalef(0.5, 5, 4);                         // Scale to wall dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the wall
  glPopMatrix();

  // Draw the right wall
  glColor3f(0.47, 0.35, 0.26);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, -0.99, 0.25, -0.8, 0.5, 5, 4);
  GLfloat wallA1[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat wallB1[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat wallC1[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat wallD1[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate and set normal for the right wall
  FunctionAux::calculateFlatNormal(wallA1, wallB1, wallC1, wallD1, normal);

  glPushMatrix();
  glTranslatef(0.99, 0.25, -0.8);              // Translate to position
  glScalef(0.5, 5, 4);                         // Scale to wall dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the wall
  glPopMatrix();

  //----------- Top Surface ---------
  glColor3f(0.47, 0.35, 0.26);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.0, 0.5, -0.8, 20, 0.5, 4);
  GLfloat topA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat topB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat topC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat topD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate and set normal for the top
  FunctionAux::calculateFlatNormal(topA, topB, topC, topD, normal);

  glPushMatrix();
  glTranslatef(0.0, 0.5, -0.8);                // Translate to position
  glScalef(20, 0.5, 4);                        // Scale to top dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the top surface
  glPopMatrix();

  //----------- Wardrobe Body ---------
  glColor3f(0.38, 0.27, 0.19);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.4, 0.2, -0.9, 8, 4, 2);
  GLfloat wardrobeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat wardrobeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat wardrobeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat wardrobeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate and set normal for the wardrobe body
  FunctionAux::calculateFlatNormal(wardrobeA, wardrobeB, wardrobeC, wardrobeD,
                                   normal);

  glPushMatrix();
  glTranslatef(0.4, 0.2, -0.9);                // Translate to position
  glScalef(8, 4, 2);                           // Scale to wardrobe dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the wardrobe
  glPopMatrix();

  //---------- Design Elements ---------
  glColor3f(0.9, 0.9, 0.9);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.1, 0.2, -0.89, 1.5, 3.5, 2);
  GLfloat designA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate and set normal for the design element
  FunctionAux::calculateFlatNormal(designA, designB, designC, designD, normal);

  glPushMatrix();
  glTranslatef(0.1, 0.2, -0.89);               // Translate to position
  glScalef(1.5, 3.5, 2);                       // Scale to design dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the design element
  glPopMatrix();

  // Draw the second design element
  glColor3f(0.9, 0.9, 0.9);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.4, 0.2, -0.89, 1.5, 3.5, 2);
  GLfloat designnA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designnB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designnC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designnD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate and set normal for the second design element
  FunctionAux::calculateFlatNormal(designnA, designnB, designnC, designnD,
                                   normal);

  glPushMatrix();
  glTranslatef(0.4, 0.2, -0.89);               // Translate to position
  glScalef(1.5, 3.5, 2);                       // Scale to design dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the second design element
  glPopMatrix();

  // Draw the third design element
  glColor3f(0.9, 0.9, 0.9);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.1, 0.2, -0.79, 1.5, 3.5, 2);
  GLfloat designnnA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designnnB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designnnC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designnnD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate and set normal for the third design element
  FunctionAux::calculateFlatNormal(designnnA, designnnB, designnnC, designnnD,
                                   normal);

  glPushMatrix();
  glTranslatef(0.1, 0.2, -0.79);               // Translate to position
  glScalef(1.5, 3.5, 2);                       // Scale to design dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the third design element
  glPopMatrix();
}

void sofa() {
  // Set the color and material properties for the sofa
  glColor3f(0.91, 0.91, 0.89);                      // Light gray color
  GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Specular color
  GLfloat shininess[] = {16.0f}; // Shininess factor for material

  // Apply material properties for specular highlights
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // Create vertices for the main body of the sofa
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, -0.32, 0.065, -0.3, 4, 0.65,
                                             1.7);
  GLfloat normal[3]; // Array to store calculated normal vectors

  // Define corners of the main sofa body for normal calculation
  GLfloat sofaA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat sofaB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat sofaC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat sofaD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate the normal for lighting
  FunctionAux::calculateFlatNormal(sofaA, sofaB, sofaC, sofaD, normal);

  // Draw the main sofa body
  glPushMatrix();
  glTranslatef(-0.32, 0.065, -0.3);            // Translate to position
  glScalef(4, 0.65, 1.7);                      // Scale to dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the sofa body
  glPopMatrix();

  //------ Draw the black base of the sofa ---------
  glColor3f(0.09, 0.09, 0.09); // Dark color for the base
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.32, 0.015, -0.3,
                                                    4.1, 0.15, 1.71);

  // Define corners of the base for normal calculation
  GLfloat baseA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat baseB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat baseC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat baseD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate the normal for lighting
  FunctionAux::calculateFlatNormal(baseA, baseB, baseC, baseD, normal);

  // Draw the base
  glPushMatrix();
  glTranslatef(-0.32, 0.015, -0.3);            // Translate to position
  glScalef(4.1, 0.15, 1.71);                   // Scale to dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the base
  glPopMatrix();

  //------- Draw the back of the sofa -----------
  glColor3f(0.19, 0.19, 0.19); // Dark gray color for the back
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.32, 0.1, -0.36, 4.1,
                                                    1.3, 0.61);

  // Define corners of the back for normal calculation
  GLfloat backA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat backB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat backC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat backD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate the normal for lighting
  FunctionAux::calculateFlatNormal(backA, backB, backC, backD, normal);

  // Draw the back
  glPushMatrix();
  glTranslatef(-0.32, 0.1, -0.36);             // Translate to position
  glScalef(4.1, 1.3, 0.61);                    // Scale to dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the back
  glPopMatrix();

  //--------- Draw the seat of the sofa ----------
  glColor3f(0.0, 0.0, 0.0); // Black color for the seat
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.41, 0.092, -0.25,
                                                    1.7, 0.15, 1.0);

  // Define corners of the seat for normal calculation
  GLfloat seatA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat seatB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat seatC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat seatD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate the normal for lighting
  FunctionAux::calculateFlatNormal(seatA, seatB, seatC, seatD, normal);

  // Draw the seat
  glPushMatrix();
  glTranslatef(-0.41, 0.092, -0.25);           // Translate to position
  glScalef(1.7, 0.15, 1.0);                    // Scale to dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the seat
  glPopMatrix();

  // Draw an additional seat part
  glColor3f(0.0, 0.0, 0.0); // Black color for the additional seat
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.21, 0.092, -0.25,
                                                    1.7, 0.15, 1.0);

  // Define corners of the additional seat for normal calculation
  GLfloat seatA1[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat seatB1[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat seatC1[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat seatD1[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate the normal for lighting
  FunctionAux::calculateFlatNormal(seatA1, seatB1, seatC1, seatD1, normal);

  // Draw the additional seat
  glPushMatrix();
  glTranslatef(-0.21, 0.092, -0.25);           // Translate to position
  glScalef(1.7, 0.15, 1.0);                    // Scale to dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the additional seat
  glPopMatrix();

  //------ Draw the side rest of the sofa --------
  glColor3f(0.91, 0.91, 0.89); // Light gray color for the side rest
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.55, 0.065, -0.3, 1,
                                                    1.4, 1.1);

  // Define corners of the side rest for normal calculation
  GLfloat sideA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat sideB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat sideC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat sideD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calculate the normal for lighting
  FunctionAux::calculateFlatNormal(sideA, sideB, sideC, sideD, normal);

  // Draw the side rest
  glPushMatrix();
  glTranslatef(-0.55, 0.065, -0.3);            // Translate to position
  glScalef(1, 1.4, 1.1);                       // Scale to dimensions
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal for lighting
  glutSolidCube(0.1);                          // Draw the side rest
  glPopMatrix();
}

void drawRoom1() {

  glEnable(GL_LIGHT2); // Enable light source 2
  float light2[4][4] = {
      {0.1f, 0.1f, 0.1f, 1.f},    // Ambient light
      {0.08f, 0.08f, 0.08f, 1.f}, // Diffuse light
      {0.01f, 0.01f, 0.01f, 1.f}, // Specular light
      {-0.2, 0.5, 0.0, 1.f}       // Light position
  };
  // Set light properties
  glLightfv(GL_LIGHT2, GL_AMBIENT, &light2[0][0]);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, &light2[1][0]);
  glLightfv(GL_LIGHT2, GL_SPECULAR, &light2[2][0]);
  glLightfv(GL_LIGHT2, GL_POSITION, &light2[3][0]);

  GLfloat shininess[] = {128.0f}; // Material shininess
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  GLfloat normal[3];

  //-------------- Floor -----------------
  glColor3f(0.85, 0.85, 0.85);                   // Floor color
  GLfloat matSpecular[] = {0.85f, 0.85f, 0.85f}; // Floor specular
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  glBegin(GL_POLYGON);                                  // Start floor polygon
  GLfloat v0[] = {1, 0.0, -1};                          // Vertex 0
  GLfloat v1[] = {1, 0.0, 1};                           // Vertex 1
  GLfloat v3[] = {-1, 0.0, -1};                         // Vertex 3
  FunctionAux::calculateFlatNormal(v0, v1, v3, normal); // Calculate normal
  glNormal3f(normal[0], normal[1], normal[2]);          // Set normal
  glVertex3f(1, 0.0, -1);                               // Vertex 0
  glVertex3f(1, 0.0, 1);                                // Vertex 1
  glVertex3f(-1, 0.0, 1);                               // Vertex 2
  glVertex3f(-1, 0.0, -1);                              // Vertex 3
  glEnd();                                              // End floor polygon

  lines(); // Draw additional lines

  //-------- desenha a parede de trás do quarto ----------------
  glColor3f(0.69, 0.58, 0.56);                           // cor
  GLfloat matSpecularWallBack[] = {0.69f, 0.58f, 0.56f}; // iluminacao
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularWallBack);
  glBegin(GL_POLYGON);          // Start back wall polygon
  GLfloat v4[] = {1, 0.5, -1};  // Vertex 4
  GLfloat v5[] = {1, 0.0, -1};  // Vertex 5
  GLfloat v6[] = {-1, 0.5, -1}; // Vertex 6
  FunctionAux::calculateFlatNormal(v4, v5, v6, normal); // Calculate normal
  glNormal3f(normal[0], normal[1], normal[2]);          // Set normal
  glVertex3f(1, 0.5, -1);                              
  glVertex3f(1, 0.0, -1);                              
  glVertex3f(-1, 0.0, -1);                              
  glVertex3f(-1, 0.5, -1);                             
  glEnd();            

  //---------- desenha a parede da direita do quarto -------------
  glColor3f(0.69, 0.58, 0.56);                            // Wall color
  GLfloat matSpecularWallRight[] = {0.69f, 0.58f, 0.56f}; // Wall specular
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularWallRight);
  glBegin(GL_POLYGON);         // Start right wall polygon
  GLfloat v7[] = {1, 0.5, -1}; // Vertex 8
  GLfloat v8[] = {1, 0.0, -1}; // Vertex 9
  GLfloat v9[] = {1, 0.5, 1};  // Vertex 10
  FunctionAux::calculateFlatNormal(v7, v8, v9, normal); // Calculate normal
  glNormal3f(normal[0], normal[1], normal[2]);          // Set normal
  glVertex3f(1, 0.5, -1);                               // Vertex 8
  glVertex3f(1, 0.0, -1);                               // Vertex 9
  glVertex3f(1, 0.0, 1);                                // Vertex 11
  glVertex3f(1, 0.5, 1);                                // Vertex 12
  glEnd(); // End right wall polygon

  //---------- Wall (Left) --------------
  glColor3f(1.0, 0.0, 0.0);                         // Wall color
  GLfloat matSpecularWallLeft[] = {1.0f, 0.f, 0.f}; // Wall specular
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularWallLeft);
  glBegin(GL_POLYGON);           // Start left wall polygon
  GLfloat v10[] = {-1, 0.5, -1}; // Vertex 13
  GLfloat v11[] = {1, 0.0, -1};  // Vertex 14
  GLfloat v12[] = {-1, 0.5, 1};  // Vertex 15
  FunctionAux::calculateFlatNormal(v10, v11, v12, normal); // Calculate normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Set normal
  glVertex3f(-1, 0.5, -1);                                 // Vertex 13
  glVertex3f(-1, 0.0, -1);                                 // Vertex 14
  glVertex3f(-1, 0.0, 1);                                  // Vertex 15
  glVertex3f(-1, 0.5, 1);                                  // Vertex 16
  glEnd(); // End left wall polygon

  //---------- Roof ---------------------
  glColor3f(0.80, 0.60, 0.58);                    // Roof color
  GLfloat matSpecularRoof[] = {0.80, 0.60, 0.58}; // Roof specular
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularRoof);
  glBegin(GL_POLYGON);                                     // Start roof polygon
  GLfloat v13[] = {-1, 0.5, -1};                           // Vertex 17
  GLfloat v14[] = {-1, 0.5, 1};                            // Vertex 18
  GLfloat v15[] = {1, 0.5, -1};                            // Vertex 19
  FunctionAux::calculateFlatNormal(v13, v14, v15, normal); // Calculate normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Set normal
  glVertex3f(-1, 0.5, -1);                                 // Vertex 17
  glVertex3f(-1, 0.5, 1);                                  // Vertex 18
  glVertex3f(1, 0.5, 1);                                   // Vertex 20
  glVertex3f(1, 0.5, -1);                                  // Vertex 21
  glEnd();                                                 // End roof polygon
  //--------wall(back)grey1----------------
  // Set color and material for the back wall
  glColor3f(0.69, 0.58, 0.56);
  GLfloat matSpecularWallBackG[] = {0.69, 0.58, 0.56};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularWallBackG);

  //Draw first wall polygon
  glBegin(GL_POLYGON);
  GLfloat v16[] = {1, 0.5, 1};                             // Vertex 1
  GLfloat v17[] = {1, 0.27, 1};                            // Vertex 2
  GLfloat v18[] = {-1, 0.5, 1};                            // Vertex 3
  FunctionAux::calculateFlatNormal(v16, v17, v18, normal); // Calculate normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Set normal
  glVertex3f(1, 0.5, 1);                                   // Define vertices
  glVertex3f(1, 0.27, 1);
  glVertex3f(-1, 0.27, 1);
  glVertex3f(-1, 0.5, 1);
  glEnd();

  // Draw second wall polygon
  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  GLfloat v19[] = {0.2, 0.0, 1};                           // Vertex 1
  GLfloat v20[] = {0.2, 0.27, 1};                          // Vertex 2
  GLfloat v21[] = {-1, 0.0, 1};                            // Vertex 3
  FunctionAux::calculateFlatNormal(v19, v20, v21, normal); // Calculate normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Set normal
  glVertex3f(0.2, 0.0, 1);                                 // Define vertices
  glVertex3f(0.2, 0.27, 1);
  glVertex3f(-1, 0.27, 1);
  glVertex3f(-1, 0.0, 1);
  glEnd();

  // Draw third wall polygon
  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  GLfloat v22[] = {0.4, 0.0, 1};                           // Vertex 1
  GLfloat v23[] = {0.4, 0.27, 1};                          // Vertex 2
  GLfloat v24[] = {1, 0.0, 1};                             // Vertex 3
  FunctionAux::calculateFlatNormal(v22, v23, v24, normal); // Calculate normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Set normal
  glVertex3f(0.4, 0.0, 1);                                 // Define vertices
  glVertex3f(0.4, 0.27, 1);
  glVertex3f(1, 0.27, 1);
  glVertex3f(1, 0.0, 1);
  glEnd();

  //----------------door main-------------
  // Set color and material for the main door
  glColor3f(0.01, 0.012, 0.012);
  GLfloat matSpeculardoorMain[] = {0.01, 0.012, 0.012};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpeculardoorMain);
  glPushMatrix(); // Save current transformation state

  // Calculate and transform vertices for the door
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.15, 0.135, 1.055, 1.5, 2.7,
                                             0.1);
  GLfloat verticeA2[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB2[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC2[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD2[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticeA2, verticeB2, verticeC2, verticeD2,
                                   normal);    // Calculate normal
  glTranslatef(0.15, 0.135, 1.055);            // Position door
  glRotatef(45, 0, 1, 0);                      // Rotate door
  glScalef(1.5, 2.7, 0.1);                     // Scale door
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal
  glutSolidCube(0.1);                          // Draw door as solid cube
  glPopMatrix(); // Restore previous transformation state

  // Set color and material for the second door
  glColor3f(0.901, 0.9012, 0.9012);
  GLfloat matSpeculardoorMain1[] = {0.901, 0.9012, 0.9012};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpeculardoorMain1);
  glPushMatrix(); // Save current transformation state

  // Calculate and transform vertices for the second door
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, 0.15, 0.135, 1.055,
                                                    1.2, 2.2, 0.11);
  GLfloat verticeA1[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB1[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC1[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD1[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticeA1, verticeB1, verticeC1, verticeD1,
                                   normal);    // Calculate normal
  glTranslatef(0.15, 0.135, 1.055);            // Position second door
  glRotatef(45, 0, 1, 0);                      // Rotate second door
  glScalef(1.2, 2.2, 0.11);                    // Scale second door
  glNormal3f(normal[0], normal[1], normal[2]); // Set normal
  glutSolidCube(0.1);                          // Draw second door as solid cube
  glPopMatrix(); // Restore previous transformation state

  //---front door border frame (polygonal shapes)---

  glColor3f(0.38, 0.27, 0.19); // Set brownish color for the door border
  GLfloat matSpeculardoorBorder[] = {
      0.38, 0.27, 0.19}; // Material specular properties for the door border
  glMaterialfv(GL_FRONT, GL_SPECULAR,
               matSpeculardoorBorder); // Apply material properties

  // Front top part of the border
  glBegin(GL_POLYGON);
  GLfloat v25[] = {0.4, 0.285, 1.0101}; // Top-right vertex
  GLfloat v26[] = {0.4, 0.27, 1.0101};  // Bottom-right vertex
  GLfloat v27[] = {0.2, 0.285, 1.0101}; // Top-left vertex
  FunctionAux::calculateFlatNormal(v25, v26, v27,
                                   normal); // Calculate normal for shading
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.4, 0.285, 1.0101); // Set vertices for polygon
  glVertex3f(0.4, 0.27, 1.0101);
  glVertex3f(0.2, 0.27, 1.0101);
  glVertex3f(0.2, 0.285, 1.0101);
  glEnd();

  // Left vertical side of the border
  glColor3f(0.38, 0.27, 0.19); // Reapply border color
  glBegin(GL_POLYGON);
  GLfloat v28[] = {0.395, 0.0, 1.0101};   // Bottom-left vertex
  GLfloat v29[] = {0.395, 0.285, 1.0101}; // Top-left vertex
  GLfloat v30[] = {0.41, 0.0, 1.0101};    // Bottom-right vertex
  FunctionAux::calculateFlatNormal(v28, v29, v30,
                                   normal); // Calculate normal for shading
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.395, 0.0, 1.0101); // Set vertices for polygon
  glVertex3f(0.395, 0.285, 1.0101);
  glVertex3f(0.41, 0.285, 1.0101);
  glVertex3f(0.41, 0.0, 1.0101);
  glEnd();

  // Right vertical side of the border
  glColor3f(0.38, 0.27, 0.19); // Reapply border color
  glBegin(GL_POLYGON);
  GLfloat v31[] = {0.2, 0.0, 1.0101};     // Bottom-left vertex
  GLfloat v32[] = {0.395, 0.285, 1.0101}; // Top-right vertex
  GLfloat v33[] = {0.185, 0.0, 1.0101};   // Bottom-right vertex
  FunctionAux::calculateFlatNormal(v31, v32, v33,
                                   normal); // Calculate normal for shading
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.2, 0.0, 1.0101); // Set vertices for polygon
  glVertex3f(0.2, 0.285, 1.0101);
  glVertex3f(0.185, 0.285, 1.0101);
  glVertex3f(0.185, 0.0, 1.0101);
  glEnd();

  //---back door border frame (mirroring front frame)---

  // Back top part of the border
  glColor3f(0.38, 0.27, 0.19); // Reapply border color
  glBegin(GL_POLYGON);
  GLfloat v34[] = {0.4, 0.285, 0.999}; // Top-right vertex
  GLfloat v35[] = {0.4, 0.27, 0.999};  // Bottom-right vertex
  GLfloat v36[] = {0.2, 0.285, 0.999}; // Top-left vertex
  FunctionAux::calculateFlatNormal(v34, v35, v36,
                                   normal); // Calculate normal for shading
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.4, 0.285, 0.999); // Set vertices for polygon
  glVertex3f(0.4, 0.27, 0.999);
  glVertex3f(0.2, 0.27, 0.999);
  glVertex3f(0.2, 0.285, 0.999);
  glEnd();

  // Back left vertical side of the border
  glColor3f(0.38, 0.27, 0.19); // Reapply border color
  glBegin(GL_POLYGON);
  GLfloat v37[] = {0.395, 0.0, 0.999};   // Bottom-left vertex
  GLfloat v38[] = {0.395, 0.285, 0.999}; // Top-left vertex
  GLfloat v39[] = {0.41, 0.0, 0.999};    // Bottom-right vertex
  FunctionAux::calculateFlatNormal(v37, v38, v39,
                                   normal); // Calculate normal for shading
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.395, 0.0, 0.999); // Set vertices for polygon
  glVertex3f(0.395, 0.285, 0.999);
  glVertex3f(0.41, 0.285, 0.999);
  glVertex3f(0.41, 0.0, 0.999);
  glEnd();

  // Back right vertical side of the border
  glColor3f(0.38, 0.27, 0.19); // Reapply border color
  glBegin(GL_POLYGON);
  GLfloat v40[] = {0.2, 0.0, 0.999};   // Bottom-left vertex
  GLfloat v41[] = {0.2, 0.285, 0.999}; // Top-left vertex
  GLfloat v42[] = {0.185, 0.0, 0.999}; // Bottom-right vertex
  FunctionAux::calculateFlatNormal(v40, v41, v42,
                                   normal); // Calculate normal for shading
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.2, 0.0, 0.999); // Set vertices for polygon
  glVertex3f(0.2, 0.285, 0.999);
  glVertex3f(0.185, 0.285, 0.999);
  glVertex3f(0.185, 0.0, 0.999);
  glEnd();
  //-------------tv wall------
  // Calculate vertices for the TV wall, normal vector is calculated for flat
  // shading
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, 0.74, 0.25, 0.5, 5.1,
                                                    5, 9.99);
  GLfloat verticeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD,
                                   normal);

  // Set color and material properties for the TV wall
  glColor3f(0.53, 0.12, 0.12);
  GLfloat matSpeculardoortvWall[] = {0.53, 0.12, 0.12};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpeculardoortvWall);
;

  //---------door------------
  // Calculate vertices for the door, normal vector is calculated for flat
  // shading
  glColor3f(0.0f, 0.0f, 0.0f);
  std::vector<std::array<GLfloat, 3>> vertices2 =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.74, 0.25, 0.5, 5.1, 5,
                                             9.99);
  GLfloat verticeE[3] = {vertices2[0][1], vertices2[0][2], vertices2[0][3]};
  GLfloat verticeF[3] = {vertices2[1][1], vertices2[1][2], vertices2[1][3]};
  GLfloat verticeG[3] = {vertices2[2][1], vertices2[2][2], vertices2[2][3]};
  GLfloat verticeh[3] = {vertices2[3][1], vertices2[3][2], vertices2[3][3]};
  FunctionAux::calculateFlatNormal(verticeE, verticeF, verticeG, verticeh,
                                   normal);

  //---------roof lamp------------
  // Draw a torus-shaped roof lamp
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  glTranslatef(-0.2, 0.5, 0.0);
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(0.03, 0.41, 100, 100);
  glPopMatrix();

  // Call functions to render other objects (walls, box, wardrobe, sofa)
  redwall();
  greywall();
  wardrobe();
  sofa();

  // Flush to ensure all OpenGL commands are executed
  glFlush();
}
