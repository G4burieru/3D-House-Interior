#include "room1.h"
#include <GL/glut.h>
#include <vector>


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
    glColor3fv(color);
    glBegin(GL_POLYGON);
    for (size_t i = 0; i < vertices.size(); i += 3) {
        glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
    }
    glEnd();
}

void drawCube(const GLfloat* color, float x, float y, float z, float scaleX, float scaleY, float scaleZ) {
    glColor3fv(color);
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(scaleX, scaleY, scaleZ);
    glutSolidCube(0.1f);
    glPopMatrix();
}

void redwall() {
    //--------------dark red top---------------------
    GLfloat darkRed[] = {0.53f, 0.12f, 0.12f};
    drawPolygon({-0.98, 0.0, 1, -0.98, 0.5, 1, -0.98, 0.5, 0.9, -0.98, 0.0, 0.9}, darkRed);
    drawPolygon({-0.98, 0.5, 0.9, -0.98, 0.5, -0.2, -0.98, 0.4, -0.2, -0.98, 0.4, 0.9}, darkRed);
    drawPolygon({-0.98, 0.5, -0.3, -0.98, 0.0, -0.3, -0.98, 0.0, -0.2, -0.98, 0.5, -0.2}, darkRed);
    
    //--------------grey mid--------------
    GLfloat grey[] = {0.69f, 0.58f, 0.56f};
    drawPolygon({-0.98, 0.0, 0.9, -0.98, 0.4, 0.9, -0.98, 0.4, 0.7, -0.98, 0.0, 0.7}, grey);
    drawPolygon({-0.98, 0.4, 0.7, -0.98, 0.4, 0.0, -0.98, 0.25, 0.0, -0.98, 0.25, 0.7}, grey);
    drawPolygon({-0.98, 0.4, -0.2, -0.98, 0.0, -0.2, -0.98, 0.0, 0.0, -0.98, 0.4, 0.0}, grey);

    //--------------black----------------
    GLfloat black[] = {0.15f, 0.11f, 0.11f};
    drawPolygon({-0.98, 0.0, 0.7, -0.98, 0.25, 0.7, -0.98, 0.25, 0.65, -0.98, 0.0, 0.65}, black);
    drawPolygon({-0.98, 0.25, 0.65, -0.98, 0.25, 0.0, -0.98, 0.2, 0.0, -0.98, 0.2, 0.65}, black);
    drawPolygon({-0.98, 0.25, 0.0, -0.98, 0.0, 0.0, -0.98, 0.0, 0.05, -0.98, 0.25, 0.05}, black);

    //-------------black drawer---------
    GLfloat blackDrawerColor [] = {0.0f, 0.0f, 0.0f}; 
    drawCube(blackDrawerColor, -0.95f, 0.06f, 0.8f, 1.1f, 0.4f, 1.5f);
    blackDrawerColor[0] = 1.0f;
    drawCube(blackDrawerColor, -0.92f, 0.06f, 0.8f, 0.56f, 0.15f, 1.45f);

    //---------bed(1st layer)------------
    GLfloat bed1stColor [] = {0.15f, 0.11f, 0.11f};
    drawCube(bed1stColor, -0.7f, 0.01f, 0.36f, 6.0f, 0.25f, 5.0f);
    
    //----------2nd layer)---------------
    GLfloat layer2ndColor [] = {0.17f, 0.13f, 0.12f};
    drawCube(layer2ndColor, -0.7f, 0.04f, 0.36f, 6.0f, 0.3f, 5.2f);
    
    //----------bed-----------
    GLfloat bedColor [] = {0.84f, 0.72f, 0.69f};
    drawCube(bedColor, -0.7f, 0.065f, 0.36f, 5.9f, 0.3f, 5.1f);
    
    //--------------bedsheet----------------
    GLfloat bedsheetColor [] = {0.86f, 0.52f, 0.55f};
    drawCube(bedsheetColor, -0.5f, 0.069f, 0.36f, 2.5f, 0.3f, 5.2f);

    //--------------pillow---------------
    GLfloat pillowColor [] = {0.86f, 0.52f, 0.55f};
    drawCube(pillowColor, -0.9f, 0.1f, 0.5f, 1.0f, 0.2f, 1.5f);
    drawCube(pillowColor, -0.9f, 0.1f, 0.25f, 1.0f, 0.2f, 1.5f);

    //-------light-------
    GLfloat lightColor[] = {1.0f, 1.0f, 1.0f};
    drawCube(lightColor, -0.98f, 0.3f, -0.1f, 0.03f, 0.07f, 0.03f);
    drawCube(lightColor, -0.98f, 0.3f, 0.8f, 0.03f, 0.07f, 0.03f);
}


void greywall() {
  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.55, 0.32, 0. - 0.9);
  glutSolidCube(0.08);
  glPopMatrix();

  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.42, 0.28, 0. - 0.9);
  glutSolidCube(0.08);
  glPopMatrix();

  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.31, 0.32, 0. - 0.9);
  glutSolidCube(0.08);
  glPopMatrix();

  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.2, 0.28, 0. - 0.9);
  glutSolidCube(0.08);
  glPopMatrix();
}

void wardrobe() {
  //--------------wall--------
  glColor3f(0.47, 0.35, 0.26);
  glPushMatrix();
  glTranslatef(-0.99, 0.25, -0.8);
  glScalef(0.5, 5, 4);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.47, 0.35, 0.26);
  glPushMatrix();
  glTranslatef(0.99, 0.25, -0.8);
  glScalef(0.5, 5, 4);
  glutSolidCube(0.1);
  glPopMatrix();

  //-----------top-------------

  glColor3f(0.47, 0.35, 0.26);
  glPushMatrix();
  glTranslatef(0.0, 0.5, -0.8);
  glScalef(20, 0.5, 4);
  glutSolidCube(0.1);
  glPopMatrix();

  //-----------wardrobe-------------
  glColor3f(0.38, 0.27, 0.19);
  glPushMatrix();
  glTranslatef(0.4, 0.2, -0.9);
  glScalef(8, 4, 2);
  glutSolidCube(0.1);
  glPopMatrix();

  //----------design--------------

  glColor3f(0.9, 0.9, 0.9);
  glPushMatrix();
  glTranslatef(0.1, 0.2, -0.89);
  glScalef(1.5, 3.5, 2);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.9, 0.9, 0.9);
  glPushMatrix();
  glTranslatef(0.4, 0.2, -0.89);
  glScalef(1.5, 3.5, 2);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.9, 0.9, 0.9);
  glPushMatrix();
  glTranslatef(0.6, 0.3, -0.89);
  glScalef(0.7, 1.5, 2);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.9, 0.9, 0.9);
  glPushMatrix();
  glTranslatef(0.7, 0.3, -0.89);
  glScalef(0.7, 1.5, 2);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.47, 0.35, 0.26);
  glPushMatrix();
  glTranslatef(0.65, 0.1, -0.89);
  glScalef(1.8, 1.5, 2);
  glutSolidCube(0.1);
  glPopMatrix();
}

void sofa() {

  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.32, 0.065, -0.3);
  glScalef(4, 0.65, 1.7);
  glutSolidCube(0.1);
  glPopMatrix();

  //------base-black-----------
  glColor3f(0.09, 0.09, 0.09);
  glPushMatrix();
  glTranslatef(-0.32, 0.015, -0.3);
  glScalef(4.1, 0.15, 1.71);
  glutSolidCube(0.1);
  glPopMatrix();

  //-------back
  glColor3f(0.19, 0.19, 0.19);
  glPushMatrix();
  glTranslatef(-0.32, 0.1, -0.36);
  glScalef(4.1, 1.3, 0.61);
  glutSolidCube(0.1);
  glPopMatrix();

  //---------seat----------

  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(-0.41, 0.092, -0.25);
  glScalef(1.7, 0.15, 1.0);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(-0.21, 0.092, -0.25);
  glScalef(1.7, 0.15, 1.0);
  glutSolidCube(0.1);
  glPopMatrix();

  //------side rest--------

  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(-0.55, 0.065, -0.3);
  glScalef(1, 1.4, 1.1);
  glutSolidCube(0.1);
  glPopMatrix();
}

void box() {

  //----------TV -------------
  glColor3f(0.18, 0.12, 0.13);
  glPushMatrix();
  glTranslatef(0.46, 0.25, 0.5);
  glScalef(0.1, 1.5, 3);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(0.47, 0.25, 0.5);
  glScalef(0.1, 1.55, 3.3);
  glutSolidCube(0.1);
  glPopMatrix();

  //--------------table-----------

  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(0.46, 0.1, 0.5);
  glScalef(0.4, 0.4, 3);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(1.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(0.455, 0.1, 0.5);
  glScalef(0.41, 0.2, 2.9);
  glutSolidCube(0.1);
  glPopMatrix();

  //-----------speaker-----------

  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(0.47, 0.08, 0.2);
  glScalef(0.1, 1.55, 0.7);
  glutSolidCube(0.1);
  glPopMatrix();

  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(0.47, 0.08, 0.8);
  glScalef(0.1, 1.55, 0.7);
  glutSolidCube(0.1);
  glPopMatrix();

  //--------cube-------------

  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(0.47, 0.4, 0.1);
  glutSolidCube(0.08);
  glPopMatrix();

  glColor3f(0.91, 0.91, 0.89);
  glPushMatrix();
  glTranslatef(0.47, 0.35, 0.2);
  glutSolidCube(0.08);
  glPopMatrix();
}

void drawRoom1() {

  /*glColor3f(1.0, 0.0, 1.0);
 glPushMatrix();
 glutSolidCube(2);
 glPopMatrix();*/
  //--------------floor-----------------
  glColor3f(0.85, 0.85, 0.85);
  glBegin(GL_POLYGON);
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
  glVertex3f(1, 0.5, -1);
  glVertex3f(1, 0.0, -1);
  glVertex3f(-1, 0.0, -1);
  glVertex3f(-1, 0.5, -1);
  glEnd();

  //----------wall(right)------
  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  glVertex3f(1, 0.5, -1);
  glVertex3f(1, 0.0, -1);
  glVertex3f(1, 0.0, 1);
  glVertex3f(1, 0.5, 1);
  glEnd();

  //----------wall(left)red------
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex3f(-1, 0.5, -1);
  glVertex3f(-1, 0.0, -1);
  glVertex3f(-1, 0.0, 1);
  glVertex3f(-1, 0.5, 1);
  glEnd();

  //----------roof------
  glColor3f(0.80, 0.60, 0.58);
  glBegin(GL_POLYGON);
  glVertex3f(-1, 0.5, -1);
  glVertex3f(-1, 0.5, 1);
  glVertex3f(1, 0.5, 1);
  glVertex3f(1, 0.5, -1);
  glEnd();

  //--------wall(back)grey1----------------
  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  glVertex3f(1, 0.5, 1);
  glVertex3f(1, 0.27, 1);
  glVertex3f(-1, 0.27, 1);
  glVertex3f(-1, 0.5, 1);
  glEnd();

  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  glVertex3f(0.2, 0.0, 1);
  glVertex3f(0.2, 0.27, 1);
  glVertex3f(-1, 0.27, 1);
  glVertex3f(-1, 0.0, 1);
  glEnd();

  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
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
  glVertex3f(0.4, 0.285, 1.0101);
  glVertex3f(0.4, 0.27, 1.0101);
  glVertex3f(0.2, 0.27, 1.0101);
  glVertex3f(0.2, 0.285, 1.0101);
  glEnd();

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  glVertex3f(0.395, 0.0, 1.0101);
  glVertex3f(0.395, 0.285, 1.0101);
  glVertex3f(0.41, 0.285, 1.0101);
  glVertex3f(0.41, 0.0, 1.0101);
  glEnd();

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  glVertex3f(0.2, 0.0, 1.0101);
  glVertex3f(0.2, 0.285, 1.0101);
  glVertex3f(0.185, 0.285, 1.0101);
  glVertex3f(0.185, 0.0, 1.0101);
  glEnd();

  // back border-----

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  glVertex3f(0.4, 0.285, 0.999);
  glVertex3f(0.4, 0.27, 0.999);
  glVertex3f(0.2, 0.27, 0.999);
  glVertex3f(0.2, 0.285, 0.999);
  glEnd();

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  glVertex3f(0.395, 0.0, 0.999);
  glVertex3f(0.395, 0.285, 0.999);
  glVertex3f(0.41, 0.285, 0.999);
  glVertex3f(0.41, 0.0, 0.999);
  glEnd();

  glColor3f(0.38, 0.27, 0.19);
  glBegin(GL_POLYGON);
  glVertex3f(0.2, 0.0, 0.999);
  glVertex3f(0.2, 0.285, 0.999);
  glVertex3f(0.185, 0.285, 0.999);
  glVertex3f(0.185, 0.0, 0.999);
  glEnd();

  //-------------tv walll------
  glColor3f(0.53, 0.12, 0.12);
  glPushMatrix();
  glTranslatef(0.74, 0.25, 0.5);
  glScalef(5.1, 5, 9.99);
  glutSolidCube(0.1);
  glPopMatrix();

  //---------door------------

  glColor3f(0.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef(0.74, 0.18, -0.005);
  glScalef(2, 3.5, 0.2);
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
