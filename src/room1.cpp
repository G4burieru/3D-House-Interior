#include "room1.h"
#include <GL/glut.h>
#include <vector>
#include "functionsAux.h"

void drawLine(float x1, float z1, float x2, float z2) {
    glBegin(GL_LINES);
    glVertex3f(x1, 0.0f, z1);
    glVertex3f(x2, 0.0f, z2);
    glEnd();
}

void lines() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(0.2f);

    // Linhas horizontais
    for (float x = -0.8f; x <= 1.0f; x += 0.2f) {
        drawLine(x, 1.0f, x, -1.0f);
    }

    // Linhas verticais
    for (float z = -0.8f; z <= 1.0f; z += 0.2f) {
        drawLine(-1.0f, z, 1.0f, z);
    }
}

void drawPolygon(const std::vector<GLfloat>& vertices, const GLfloat* color) {
    GLfloat matSpecular [] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shininess[] = {16.0f};
    
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glColor3fv(color);
    glBegin(GL_POLYGON);
    for (size_t i = 0; i < vertices.size(); i += 3) {
        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
    }
    glEnd();
}

void drawCube(const GLfloat* color, float x, float y, float z, float scaleX, float scaleY, float scaleZ) {
    GLfloat matSpecular [] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat shininess[] = {16.0f};
    
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    std::vector<std::array<GLfloat, 3>> vertices= FunctionAux::calculateCubeFaceVertices(0.1, x, y, z, scaleX, scaleY, scaleZ);
    GLfloat normal[3];
    GLfloat verticeA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
    GLfloat verticeB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
    GLfloat verticeC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
    GLfloat verticeD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
    FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD, normal);
    glColor3fv(color);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scaleX, scaleY, scaleZ);
    glNormal3f(normal[0], normal[1], normal[2]);
    glutSolidCube(0.1f);
    glPopMatrix();
}

void redwall() {
    GLfloat matSpecular [] = {1.f, 1.f, 1.f, 1.f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    GLfloat shininess[] = {128.0f};
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    GLfloat normal[] = {0.0f, 0.0f, 1.0f};
    //--------------dark red top---------------------
    GLfloat darkRed[] = {0.53f, 0.12f, 0.12f};
    
    glNormal3f(normal[0], normal[1], normal[2]);
    drawPolygon({-0.98, 0.0, 1, -0.98, 0.5, 1, -0.98, 0.5, 0.9, -0.98, 0.0, 0.9}, darkRed);
    drawPolygon({-0.98, 0.5, 0.9, -0.98, 0.5, -0.2, -0.98, 0.4, -0.2, -0.98, 0.4, 0.9}, darkRed);
    drawPolygon({-0.98, 0.5, -0.3, -0.98, 0.0, -0.3, -0.98, 0.0, -0.2, -0.98, 0.5, -0.2}, darkRed);
    
    //--------------grey mid--------------
    GLfloat grey[] = {0.69f, 0.58f, 0.56f};
    glNormal3f(normal[0], normal[1], normal[2]);
    drawPolygon({-0.98, 0.0, 0.9, -0.98, 0.4, 0.9, -0.98, 0.4, 0.7, -0.98, 0.0, 0.7}, grey);
    drawPolygon({-0.98, 0.4, 0.7, -0.98, 0.4, 0.0, -0.98, 0.25, 0.0, -0.98, 0.25, 0.7}, grey);
    drawPolygon({-0.98, 0.4, -0.2, -0.98, 0.0, -0.2, -0.98, 0.0, 0.0, -0.98, 0.4, 0.0}, grey);

    //--------------black----------------
    GLfloat black[] = {0.15f, 0.11f, 0.11f};
    glNormal3f(normal[0], normal[1], normal[2]);
    drawPolygon({-0.98, 0.0, 0.7, -0.98, 0.25, 0.7, -0.98, 0.25, 0.65, -0.98, 0.0, 0.65}, black);
    drawPolygon({-0.98, 0.25, 0.65, -0.98, 0.25, 0.0, -0.98, 0.2, 0.0, -0.98, 0.2, 0.65}, black);
    drawPolygon({-0.98, 0.25, 0.0, -0.98, 0.0, 0.0, -0.98, 0.0, 0.05, -0.98, 0.25, 0.05}, black);
    normal[0] = 0.5f;
    normal[1] = 0.5f;
    normal[2] = 0.5f;
    //-------------black drawer---------
    GLfloat blackDrawerColor [] = {0.0f, 0.0f, 0.0f}; 
    glNormal3f(normal[0], normal[1], normal[2]);
    drawCube(blackDrawerColor, -0.95f, 0.06f, 0.8f, 1.1f, 0.4f, 1.5f);
    blackDrawerColor[0] = 1.0f;
    glNormal3f(normal[0], normal[1], normal[2]);
    drawCube(blackDrawerColor, -0.92f, 0.06f, 0.8f, 0.56f, 0.15f, 1.45f);


    //---------bed(1st layer)------------
    GLfloat bed1stColor [] = {0.15f, 0.11f, 0.11f};
    glNormal3f(normal[0], normal[1], normal[2]);
    drawCube(bed1stColor, -0.7f, 0.01f, 0.36f, 6.0f, 0.25f, 5.0f);
    
    //----------2nd layer)---------------
    GLfloat layer2ndColor [] = {0.17f, 0.13f, 0.12f};
    drawCube(layer2ndColor, -0.7f, 0.04f, 0.36f, 6.0f, 0.3f, 5.2f);
    
    //----------bed-----------
    GLfloat bedColor [] = {0.84f, 0.72f, 0.69f};
    glNormal3f(normal[0], normal[1], normal[2]);
    drawCube(bedColor, -0.7f, 0.065f, 0.36f, 5.9f, 0.3f, 5.1f);
    
    //--------------bedsheet----------------
    GLfloat bedsheetColor [] = {0.86f, 0.52f, 0.55f};
    glNormal3f(normal[0], normal[1], normal[2]);
    drawCube(bedsheetColor, -0.5f, 0.069f, 0.36f, 2.5f, 0.3f, 5.2f);

    //--------------pillow---------------
    GLfloat pillowColor [] = {0.86f, 0.52f, 0.55f};
    glNormal3f(normal[0], normal[1], normal[2]);
    drawCube(pillowColor, -0.9f, 0.1f, 0.5f, 1.0f, 0.2f, 1.5f);
    glNormal3f(normal[0], normal[1], normal[2]);
    drawCube(pillowColor, -0.9f, 0.1f, 0.25f, 1.0f, 0.2f, 1.5f);

    //-------light-------
    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f};
    glNormal3f(normal[0], normal[1], normal[2]);
    drawCube(lightColor, -0.98f, 0.3f, -0.1f, 0.03f, 0.07f, 0.03f);
    glNormal3f(normal[0], normal[1], normal[2]);
    drawCube(lightColor, -0.98f, 0.3f, 0.8f, 0.03f, 0.07f, 0.03f);
}


void greywall() {
  GLfloat matSpecular [] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat shininess[] = {16.0f};
    
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  std::vector<std::array<GLfloat, 3>> vertices= FunctionAux::calculateCubeFaceVertices(0.08, -0.55, 0.32, 0. - 0.9,1,1,1);
  GLfloat normal[3];
  GLfloat verticeA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD, normal);
  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.55, 0.32, 0. - 0.9);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.08);
  glPopMatrix();

  std::vector<std::array<GLfloat, 3>> vertices2= FunctionAux::calculateCubeFaceVertices(0.08, -0.42, 0.28, 0. - 0.9,1,1,1);
  GLfloat verticeE [3] = {vertices2[0][1], vertices2[0][2], vertices2[0][3]};
  GLfloat verticeF [3] = {vertices2[1][1], vertices2[1][2], vertices2[1][3]};
  GLfloat verticeG [3] = {vertices2[2][1], vertices2[2][2], vertices2[2][3]};
  GLfloat verticeH [3] = {vertices2[3][1], vertices2[3][2], vertices2[3][3]};
  FunctionAux::calculateFlatNormal(verticeE, verticeF, verticeG, verticeH, normal);
  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.42, 0.28, 0. - 0.9);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.08);
  glPopMatrix();


  vertices= FunctionAux::calculateCubeFaceVertices(0.08, -0.42, 0.28, 0. - 0.9,1,1,1);
  GLfloat verticee [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticee1 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticee2 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticee3 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticee, verticee1, verticee2, verticee3, normal);
  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.31, 0.32, 0. - 0.9);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.08);
  glPopMatrix();

  vertices= FunctionAux::calculateCubeFaceVertices(0.08,-0.2, 0.28, 0. - 0.9,1,1,1);
  GLfloat verticee4[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticee5 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticee6 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticee7 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticee4, verticee5, verticee6, verticee7, normal);
  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.2, 0.28, 0. - 0.9);
  glutSolidCube(0.08);
  glPopMatrix();
}

void wardrobe() {
  //--------------wall--------
  GLfloat matSpecular [] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat shininess[] = {16.0f};
    
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  std::vector<std::array<GLfloat, 3>> vertices= FunctionAux::calculateCubeFaceVertices(0.1, -0.99, 0.25, -0.8,0.5, 5, 4);
  GLfloat normal[3];
  GLfloat wallA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat wallB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat wallC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat wallD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(wallA, wallB, wallC, wallD, normal);
  glColor3f(0.47, 0.35, 0.26);
  glPushMatrix();
  glTranslatef(-0.99, 0.25, -0.8);
  glScalef(0.5, 5, 4);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.47, 0.35, 0.26);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, -0.99, 0.25, -0.8,0.5, 5, 4);
  GLfloat wallA1 [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat wallB1 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat wallC1 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat wallD1 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(wallA1, wallB1, wallC1, wallD1, normal);
  glPushMatrix();
  glTranslatef(0.99, 0.25, -0.8);
  glScalef(0.5, 5, 4);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //-----------top-------------

  glColor3f(0.47, 0.35, 0.26);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.0, 0.5, -0.8,20, 0.5, 4);
  GLfloat topA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat topB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat topC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat topD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(topA, topB, topC, topD, normal);
  glPushMatrix();
  glTranslatef(0.0, 0.5, -0.8);
  glScalef(20, 0.5, 4);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //-----------wardrobe-------------
  glColor3f(0.38, 0.27, 0.19);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.4, 0.2, -0.9,8, 4, 2);
  GLfloat wardrobeA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat wardrobeB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat wardrobeC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat wardrobeD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(wardrobeA, wardrobeB, wardrobeC, wardrobeD, normal);
  glPushMatrix();
  glTranslatef(0.4, 0.2, -0.9);
  glScalef(8, 4, 2);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //----------design--------------

  glColor3f(0.9, 0.9, 0.9);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.1, 0.2, -0.89,1.5, 3.5, 2);
  GLfloat designA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(designA, designB, designC, designD, normal);
  glPushMatrix();
  glTranslatef(0.1, 0.2, -0.89);
  glScalef(1.5, 3.5, 2);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.9, 0.9, 0.9);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.4, 0.2, -0.89,1.5, 3.5, 2);
  GLfloat designnA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designnB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designnC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designnD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(designnA, designnB, designnC, designnD, normal);
  glPushMatrix();
  glTranslatef(0.4, 0.2, -0.89);
  glScalef(1.5, 3.5, 2);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.9, 0.9, 0.9);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.6, 0.3, -0.89,0.7, 1.5, 2);
  GLfloat designnnA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designnnB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designnnC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designnnD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(designnnA, designnnB, designnnC, designnnD, normal);
  glPushMatrix();
  glTranslatef(0.6, 0.3, -0.89);
  glScalef(0.7, 1.5, 2);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.9, 0.9, 0.9);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.6, 0.3, -0.89,0.7, 1.5, 2);
  GLfloat designA1 [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designB1 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designC1 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designD1 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(designA1, designB1, designC1, designD1, normal);
  glPushMatrix();
  glTranslatef(0.7, 0.3, -0.89);
  glScalef(0.7, 1.5, 2);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.47, 0.35, 0.26);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.6, 0.65, 0.1, -0.89, 1.5, 2);
  GLfloat designA2 [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designB2 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designC2 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designD2 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(designA2, designB2, designC2, designD2, normal);
  glPushMatrix();
  glTranslatef(0.65, 0.1, -0.89);
  glScalef(1.8, 1.5, 2);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();
}

void sofa() {

  glColor3f(0.91, 0.91, 0.89);
  GLfloat matSpecular [] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat shininess[] = {16.0f};
    
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  std::vector<std::array<GLfloat, 3>> vertices= FunctionAux::calculateCubeFaceVertices(0.1, -0.32, 0.065, -0.3,4, 0.65, 1.7);
  GLfloat normal[3];
  GLfloat sofaA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat sofaB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat sofaC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat sofaD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(sofaA, sofaB, sofaC, sofaD, normal);
  glPushMatrix();
  glTranslatef(-0.32, 0.065, -0.3);
  glScalef(4, 0.65, 1.7);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //------base-black-----------
  glColor3f(0.09, 0.09, 0.09);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1,-0.32, 0.015, -0.3,4.1, 0.15, 1.71);
  GLfloat baseA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat baseB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat baseC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat baseD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(baseA, baseB, baseC, baseD, normal);
  glPushMatrix();
  glTranslatef(-0.32, 0.015, -0.3);
  glScalef(4.1, 0.15, 1.71);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //-------back
  glColor3f(0.19, 0.19, 0.19);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1,-0.32, 0.1, -0.36,4.1, 1.3, 0.61);
 
  GLfloat backA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat backB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat backC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat backD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(backA, backB, backC, backD, normal);
  glPushMatrix();
  glTranslatef(-0.32, 0.1, -0.36);
  glScalef(4.1, 1.3, 0.61);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //---------seat----------

  glColor3f(0.0, 0.0, 0.0);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1,-0.41, 0.092, -0.25,1.7, 0.15, 1.0);
 
  GLfloat seatA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat seatB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat seatC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat seatD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(seatA, seatB, seatC, seatD, normal);
  glPushMatrix();
  glTranslatef(-0.41, 0.092, -0.25);
  glScalef(1.7, 0.15, 1.0);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.0, 0.0, 0.0);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1,-0.21, 0.092, -0.25,1.7, 0.15, 1.0);
  GLfloat seatA1 [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat seatB1 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat seatC1 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat seatD1 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(seatA1, seatB1, seatC1, seatD1, normal);
  glPushMatrix();
  glTranslatef(-0.21, 0.092, -0.25);
  glScalef(1.7, 0.15, 1.0);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //------side rest--------

  glColor3f(0.91, 0.91, 0.89);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1,-0.55, 0.065, -0.3,1, 1.4, 1.1);
  GLfloat sideA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat sideB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat sideC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat sideD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(sideA, sideB, sideC, sideD, normal);
  glPushMatrix();
  glTranslatef(-0.55, 0.065, -0.3);
  glScalef(1, 1.4, 1.1);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();
}

void box() {
  GLfloat matSpecular [] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat shininess[] = {16.0f};
    
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  
  //----------TV -------------
  glColor3f(0.18, 0.12, 0.13);
  std::vector<std::array<GLfloat, 3>> vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.46, 0.25, 0.5,0.1, 1.5, 3);
  GLfloat normal[3];
  GLfloat tvA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat tvB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat tvC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat tvD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(tvA, tvB, tvC, tvD, normal);
  glPushMatrix();
  glTranslatef(0.46, 0.25, 0.5);
  glScalef(0.1, 1.5, 3);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.0, 0.0, 0.0);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.47, 0.25, 0.5,0.1, 1.55, 3.3);
  GLfloat tvA1 [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat tvB1 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat tvC1 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat tvD1 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(tvA1, tvB1, tvC1, tvD1, normal);
  glPushMatrix();
  glTranslatef(0.47, 0.25, 0.5);
  glScalef(0.1, 1.55, 3.3);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //--------------table-----------

  glColor3f(0.0, 0.0, 0.0);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.46, 0.1, 0.5,0.4, 0.4, 3);
  GLfloat tableA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat tableB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat tableC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat tableD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(tableA, tableB, tableC, tableD, normal);
  glPushMatrix();
  glTranslatef(0.46, 0.1, 0.5);
  glScalef(0.4, 0.4, 3);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(1.0, 0.0, 0.0);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.455, 0.1, 0.5,0.41, 0.2, 2.9);
  GLfloat tableA1 [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat tableB1 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat tableC1 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat tableD1 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(tableA1, tableB1, tableC1, tableD1, normal);
  glPushMatrix();
  glTranslatef(0.455, 0.1, 0.5);
  glScalef(0.41, 0.2, 2.9);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //-----------speaker-----------

  glColor3f(0.0, 0.0, 0.0);
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.47, 0.08, 0.2,0.1, 1.55, 0.7);
  GLfloat speakerA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat speakerB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat speakerC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat speakerD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(speakerA, speakerB, speakerC, speakerD, normal);
  glPushMatrix();
  glTranslatef(0.47, 0.08, 0.2);
  glScalef(0.1, 1.55, 0.7);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();
  vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.47, 0.08, 0.8,0.1, 1.55, 0.7);
  GLfloat speakerA1 [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat speakerB1 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat speakerC1 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat speakerD1 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(speakerA1, speakerB1, speakerC1, speakerD1, normal);
  glTranslatef(0.47, 0.08, 0.8);
  glScalef(0.1, 1.55, 0.7);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //--------cube-------------

  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  vertices= FunctionAux::calculateCubeFaceVertices(0.08, 0.47, 0.08, 0.8,0.1, 1.55, 0.7);
  GLfloat cubeA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat cubeB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat cubeC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat cubeD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(cubeA, cubeB, cubeC, cubeD, normal);
  glTranslatef(0.47, 0.4, 0.1);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.08);
  glPopMatrix();

  glColor3f(0.91, 0.91, 0.89);
  vertices= FunctionAux::calculateCubeFaceVertices(0.08, 0.47, 0.35, 0.2,1, 1, 1);
  GLfloat cubeA1 [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat cubeB1 [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat cubeC1 [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat cubeD1 [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(cubeA1, cubeB1, cubeC1, cubeD1, normal);
  glPushMatrix();
  glTranslatef(0.47, 0.35, 0.2);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.08);
  glPopMatrix();
}

void drawRoom1() {
  
  glEnable(GL_LIGHT2);
  float light2[4][4] = {
                {0.05f, 0.05f, 0.05f, 1.f}, //ambient
                {0.08f, 0.08f, 0.08f, 1.f}, //diffuse
                {0.01f, 0.01f, 0.01f, 1.f}, //specular
                {-0.2, 0.5, 0.0, 1.f} //position
                
  };
  glLightfv(GL_LIGHT2, GL_AMBIENT, &light2[0][0]);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, &light2[1][0]);
  glLightfv(GL_LIGHT2, GL_SPECULAR, &light2[2][0]);
  glLightfv(GL_LIGHT2, GL_POSITION, &light2[3][0]);
  GLfloat matSpecular [] = {1.f, 1.f, 1.f, 1.f};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  GLfloat shininess[] = {128.0f};
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  GLfloat normal[3];
  //--------------floor-----------------
  glColor3f(0.85, 0.85, 0.85);
  glBegin(GL_POLYGON);
  GLfloat v0 [] = {1, 0.0, -1};
  GLfloat v1 [] = {1, 0.0, 1};
  GLfloat v3 [] = {-1, 0.0, -1};
  FunctionAux::calculateFlatNormal(v0, v1, v3, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(1, 0.0, -1);
  glVertex3f(1, 0.0, 1);
  glVertex3f(-1, 0.0, 1);
  glVertex3f(-1, 0.0, -1);
  glEnd();

  lines();

  //--------wall(back)grey1----------------
  // glColor3f(0.54, 0.54, 0.52);
  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  GLfloat v4 [] = {1, 0.5, -1};
  GLfloat v5 [] = {1, 0.0, -1};
  GLfloat v6 [] = {-1, 0.5, -1};
  FunctionAux::calculateFlatNormal(v4, v5, v6, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(1, 0.5, -1);
  glVertex3f(1, 0.0, -1);
  glVertex3f(-1, 0.0, -1);
  glVertex3f(-1, 0.5, -1);
  glEnd();

  //----------wall(right)------
  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  GLfloat v7 [] = {1, 0.5, -1};
  GLfloat v8 [] = {1, 0.0, -1};
  GLfloat v9 [] = {1, 0.5, 1};
  FunctionAux::calculateFlatNormal(v7, v8, v9, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(1, 0.5, -1);
  glVertex3f(1, 0.0, -1);
  glVertex3f(1, 0.0, 1);
  glVertex3f(1, 0.5, 1);
  glEnd();

  //----------wall(left)red------
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  GLfloat v10 [] = {-1, 0.5, -1};
  GLfloat v11 [] = {1, 0.0, -1};
  GLfloat v12 [] = {-1, 0.5, 1};
  FunctionAux::calculateFlatNormal(v10, v11, v12, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(-1, 0.5, -1);
  glVertex3f(-1, 0.0, -1);
  glVertex3f(-1, 0.0, 1);
  glVertex3f(-1, 0.5, 1);
  glEnd();

  //----------roof------
  glColor3f(0.80, 0.60, 0.58);
  glBegin(GL_POLYGON);
  GLfloat v13 [] = {-1, 0.5, -1};
  GLfloat v14 [] = {-1, 0.5, 1};
  GLfloat v15 [] = {1, 0.5, -1};
  FunctionAux::calculateFlatNormal(v13, v14, v15, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(-1, 0.5, -1);
  glVertex3f(-1, 0.5, 1);
  glVertex3f(1, 0.5, 1);
  glVertex3f(1, 0.5, -1);
  glEnd();

  //--------wall(back)grey1----------------
  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  GLfloat v16 [] = {1, 0.5, 1};
  GLfloat v17 [] = {1, 0.27, 1};
  GLfloat v18 [] = {-1, 0.5, 1};
  FunctionAux::calculateFlatNormal(v16, v17, v18, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(1, 0.5, 1);
  glVertex3f(1, 0.27, 1);
  glVertex3f(-1, 0.27, 1);
  glVertex3f(-1, 0.5, 1);
  glEnd();

  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  GLfloat v19 [] = {0.2, 0.0, 1};
  GLfloat v20 [] = {0.2, 0.27, 1};
  GLfloat v21 [] = {-1, 0.0, 1};
  FunctionAux::calculateFlatNormal(v19, v20, v21, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.2, 0.0, 1);
  glVertex3f(0.2, 0.27, 1);
  glVertex3f(-1, 0.27, 1);
  glVertex3f(-1, 0.0, 1);
  glEnd();

  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  GLfloat v22 [] = {0.4, 0.0, 1};
  GLfloat v23 [] = {0.4, 0.27, 1};
  GLfloat v24 [] = {1, 0.0, 1};
  FunctionAux::calculateFlatNormal(v22, v23, v24, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.4, 0.0, 1);
  glVertex3f(0.4, 0.27, 1);
  glVertex3f(1, 0.27, 1);
  glVertex3f(1, 0.0, 1);
  glEnd();
  //----------------door main-------------
  glColor3f(0.01, 0.012, 0.012);
  glPushMatrix();
  glTranslatef(0.15, 0.135, 1.055);
  glRotatef(45, 0, 1, 0);
  glScalef(1.5, 2.7, 0.1);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.901, 0.9012, 0.9012);
  glPushMatrix();
  glTranslatef(0.15, 0.135, 1.055);
  glRotatef(45, 0, 1, 0);
  glScalef(1.2, 2.2, 0.11);
  glutSolidCube(0.1);
  glPopMatrix();

  //--border------

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  GLfloat v25 [] = {0.4, 0.285, 1.0101};
  GLfloat v26 [] = {0.4, 0.27, 1.0101};
  GLfloat v27 [] = {0.2, 0.285, 1.0101};
  FunctionAux::calculateFlatNormal(v25, v26, v27, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.4, 0.285, 1.0101);
  glVertex3f(0.4, 0.27, 1.0101);
  glVertex3f(0.2, 0.27, 1.0101);
  glVertex3f(0.2, 0.285, 1.0101);
  glEnd();

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  GLfloat v28 [] = {0.395, 0.0, 1.0101};
  GLfloat v29 [] = {0.395, 0.285, 1.0101};
  GLfloat v30 [] = {0.41, 0.0, 1.0101};
  FunctionAux::calculateFlatNormal(v28, v29, v30, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.395, 0.0, 1.0101);
  glVertex3f(0.395, 0.285, 1.0101);
  glVertex3f(0.41, 0.285, 1.0101);
  glVertex3f(0.41, 0.0, 1.0101);
  glEnd();

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  GLfloat v31 [] = {0.2, 0.0, 1.0101};
  GLfloat v32 [] = {0.395, 0.285, 1.0101};
  GLfloat v33 [] = {0.185, 0.0, 1.0101};
  FunctionAux::calculateFlatNormal(v31, v32, v33, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.2, 0.0, 1.0101);
  glVertex3f(0.2, 0.285, 1.0101);
  glVertex3f(0.185, 0.285, 1.0101);
  glVertex3f(0.185, 0.0, 1.0101);
  glEnd();

  // back border-----

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  GLfloat v34 [] = {0.4, 0.285, 0.999};
  GLfloat v35 [] = {0.4, 0.27, 0.999};
  GLfloat v36 [] = {0.2, 0.285, 0.999};
  FunctionAux::calculateFlatNormal(v34, v35, v36, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.4, 0.285, 0.999);
  glVertex3f(0.4, 0.27, 0.999);
  glVertex3f(0.2, 0.27, 0.999);
  glVertex3f(0.2, 0.285, 0.999);
  glEnd();

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  GLfloat v37 [] = {0.395, 0.0, 0.999};
  GLfloat v38 [] = {0.395, 0.285, 0.999};
  GLfloat v39 [] = {0.41, 0.0, 0.999};
  FunctionAux::calculateFlatNormal(v37, v38, v39, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.395, 0.0, 0.999);
  glVertex3f(0.395, 0.285, 0.999);
  glVertex3f(0.41, 0.285, 0.999);
  glVertex3f(0.41, 0.0, 0.999);
  glEnd();

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  GLfloat v40 [] = {0.2, 0.0, 0.999};
  GLfloat v41 [] = {0.2, 0.285, 0.999};
  GLfloat v42 [] = {0.185, 0.0, 0.999};
  FunctionAux::calculateFlatNormal(v40, v41, v42, normal);
    
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.2, 0.0, 0.999);
  glVertex3f(0.2, 0.285, 0.999);
  glVertex3f(0.185, 0.285, 0.999);
  glVertex3f(0.185, 0.0, 0.999);
  glEnd();

  //-------------tv walll------
  std::vector<std::array<GLfloat, 3>> vertices= FunctionAux::calculateCubeFaceVertices(0.1, 0.74, 0.25, 0.5, 5.1, 5, 9.99);
  GLfloat verticeA [3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB [3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC [3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD [3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD, normal);
  glColor3f(0.53, 0.12, 0.12);
  glPushMatrix();
  glTranslatef(0.74, 0.25, 0.5);
  glScalef(5.1, 5, 9.99);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  //---------door------------

  glColor3f(0.0, 0.0, 0.0);
  std::vector<std::array<GLfloat, 3>> vertices2= FunctionAux::calculateCubeFaceVertices(0.1, 0.74, 0.25, 0.5, 5.1, 5, 9.99);
  GLfloat verticeE [3] = {vertices2[0][1], vertices2[0][2], vertices2[0][3]};
  GLfloat verticeF [3] = {vertices2[1][1], vertices2[1][2], vertices2[1][3]};
  GLfloat verticeG [3] = {vertices2[2][1], vertices2[2][2], vertices2[2][3]};
  GLfloat verticeh [3] = {vertices2[3][1], vertices2[3][2], vertices2[3][3]};
  FunctionAux::calculateFlatNormal(verticeE, verticeF, verticeG, verticeh, normal);
  glPushMatrix();
  glTranslatef(0.74, 0.18, -0.005);
  glScalef(2, 3.5, 0.2);
  glNormal3f(normal[0], normal[1], normal[2]);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.47, 0.35, 0.26);
  glPushMatrix();
  glTranslatef(0.74, 0.18, 0.0);
  glScalef(2.1, 3.6, 0.2);
  glutSolidCube(0.1);
  glPopMatrix();

  //---------roof lamp--------------------------------

  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  glTranslatef(-0.2, 0.5, 0.0);
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(0.03, 0.41, 100, 100);
  glPopMatrix();

  redwall();

  greywall();

  box();

  wardrobe();

  sofa();

  glFlush();
}
