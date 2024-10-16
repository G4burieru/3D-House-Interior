#include "room1.h"
#include "functionsAux.h"
#include <GL/glut.h>
#include <vector>

void drawLine(float x1, float z1, float x2, float z2) {
  // Começa a desenhar linhas
  glBegin(GL_LINES);

  // Especifica o vértice inicial
  glVertex3f(x1, 0.0f, z1);

  // Especifica o vértice final
  glVertex3f(x2, 0.0f, z2);

  // Termina o desenho
  glEnd();
}

void lines() {
  glColor3f(0.0f, 0.0f, 0.0f); // Define a cor da linha como preta
  glLineWidth(0.2f);           // Define a largura da linha

  // Desenha linhas horizontais
  for (float x = -0.8f; x <= 1.0f; x += 0.2f) {
    drawLine(x, 1.0f, x, -1.0f); // Desenha linha na posição x atual
  }

  // Desenha linhas verticais
  for (float z = -0.8f; z <= 1.0f; z += 0.2f) {
    drawLine(-1.0f, z, 1.0f, z); // Desenha linha na posição z atual
  }
}

void drawPolygon(const std::vector<GLfloat> &vertices, const GLfloat *color) {
  GLfloat matSpecular[] = {color[0], color[1], color[2],
                           1.0f}; // Cor do material especular
  GLfloat shininess[] = {1.0f};   // Brilho do material

  glMaterialfv(GL_FRONT, GL_SHININESS,
               shininess); // Define o brilho do material
  glMaterialfv(GL_FRONT, GL_SPECULAR,
               matSpecular); // Define a cor especular do material
  glColor3fv(color);         // Define a cor do polígono
  glBegin(GL_POLYGON);       // Começa a desenhar o polígono
  for (size_t i = 0; i < vertices.size(); i += 3) {
    glVertex3f(vertices[i], vertices[i + 1],
               vertices[i + 2]); // Especifica as posições dos vértices
  }
  glEnd(); // Finaliza o desenho
}

void drawCube(const GLfloat *color, float x, float y, float z, float scaleX,
              float scaleY, float scaleZ) {
  GLfloat matSpecular[] = {color[0], color[1], color[2],
                           1.0f}; // Cor do material especular
  GLfloat shininess[] = {1.0f};   // Brilho do material

  glMaterialfv(GL_FRONT, GL_SHININESS,
               shininess); // Define o brilho do material
  glMaterialfv(GL_FRONT, GL_SPECULAR,
               matSpecular); // Define a cor especular do material

  // Calcula os vértices das faces do cubo
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, x, y, z, scaleX, scaleY,
                                             scaleZ);
  GLfloat normal[3]; // Vetor normal para iluminação
  GLfloat verticeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD,
                                   normal); // Calcula a normal plana

  glColor3fv(color);                // Define a cor do cubo
  glPushMatrix();                   // Salva a matriz atual
  glTranslatef(x, y, z);            // Translada para a posição
  glScalef(scaleX, scaleY, scaleZ); // Escala o cubo
  glNormal3f(normal[0], normal[1],
             normal[2]); // Define a normal para iluminação
  glutSolidCube(0.1f);   // Desenha um cubo sólido
  glPopMatrix();         // Restaura a matriz anterior
}

void redwall() {
  // Configurar propriedades do material especular
  GLfloat matSpecular[] = {1.f, 1.f, 1.f, 1.f}; // Cor especular
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  GLfloat shininess[] = {128.0f}; // Fator de brilho
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

  GLfloat normal[] = {0.0f, 0.0f, 1.0f}; // Vetor normal para as superfícies

  //--------------cima vermelho escuro---------------------
  GLfloat darkRed[] = {0.53f, 0.12f,
                       0.12f}; // Cor vermelho escuro para a parte superior
  glNormal3f(normal[0], normal[1], normal[2]);
  drawPolygon({-0.98, 0.0, 1, -0.98, 0.5, 1, -0.98, 0.5, 0.9, -0.98, 0.0, 0.9},
              darkRed);
  drawPolygon(
      {-0.98, 0.5, 0.9, -0.98, 0.5, -0.2, -0.98, 0.4, -0.2, -0.98, 0.4, 0.9},
      darkRed);
  drawPolygon(
      {-0.98, 0.5, -0.3, -0.98, 0.0, -0.3, -0.98, 0.0, -0.2, -0.98, 0.5, -0.2},
      darkRed);

  //--------------meio cinza--------------
  GLfloat grey[] = {0.69f, 0.58f, 0.56f}; // Cor cinza para a seção do meio
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

  //--------------preto----------------
  GLfloat black[] = {0.15f, 0.11f, 0.11f}; // Cor preta para a seção inferior
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

  //-------------gaveta preta---------
  GLfloat blackDrawerColor[] = {0.0f, 0.0f, 0.0f};
  glNormal3f(0.5f, 0.5f, 0.5f); // Normal para superfícies da gaveta
  drawCube(blackDrawerColor, -0.95f, 0.06f, 0.8f, 1.1f, 0.4f,
           1.5f);             // Gaveta principal
  blackDrawerColor[0] = 1.0f; // Mudar para a cor branca para a gaveta menor
  drawCube(blackDrawerColor, -0.92f, 0.06f, 0.8f, 0.56f, 0.15f,
           1.45f); // Gaveta menor

  //---------cama (1ª camada)------------
  GLfloat bed1stColor[] = {0.15f, 0.11f,
                           0.11f}; // Cor para a primeira camada da cama
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(bed1stColor, -0.7f, 0.01f, 0.36f, 6.0f, 0.25f,
           5.0f); // Primeira camada da cama

  //----------2ª camada)---------------
  GLfloat layer2ndColor[] = {0.17f, 0.13f,
                             0.12f}; // Cor para a segunda camada da cama
  drawCube(layer2ndColor, -0.7f, 0.04f, 0.36f, 6.0f, 0.3f,
           5.2f); // Segunda camada da cama

  //----------cama-----------
  GLfloat bedColor[] = {0.84f, 0.72f, 0.69f}; // Cor para a cama
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(bedColor, -0.7f, 0.065f, 0.36f, 5.9f, 0.3f, 5.1f); // Cama principal

  //--------------coberta----------------
  GLfloat bedsheetColor[] = {0.86f, 0.52f, 0.55f}; // Cor para a coberta
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(bedsheetColor, -0.5f, 0.069f, 0.36f, 2.5f, 0.3f,
           5.2f); // Desenhar coberta

  //--------------travesseiro---------------
  GLfloat pillowColor[] = {0.86f, 0.52f, 0.55f}; // Cor para o travesseiro
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(pillowColor, -0.9f, 0.1f, 0.5f, 1.0f, 0.2f,
           1.5f); // Primeiro travesseiro
  drawCube(pillowColor, -0.9f, 0.1f, 0.25f, 1.0f, 0.2f,
           1.5f); // Segundo travesseiro

  //-------luz-------
  GLfloat lightColor[] = {1.0f, 1.0f, 1.0f}; // Cor para a luz
  glNormal3f(normal[0], normal[1], normal[2]);
  drawCube(lightColor, -0.98f, 0.3f, -0.1f, 0.03f, 0.07f,
           0.03f); // Luz de um lado
  drawCube(lightColor, -0.98f, 0.3f, 0.8f, 0.03f, 0.07f,
           0.03f); // Luz do outro lado
}

void greywall() {
  // Definir propriedades do material para reflexos especulares
  GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
  GLfloat shininess[] = {16.0f};

  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // Desenhar o primeiro cubo
  {
    std::vector<std::array<GLfloat, 3>> vertices =
        FunctionAux::calculateCubeFaceVertices(0.08, -0.55, 0.32, 0.0f - 0.9, 1,
                                               1, 1);
    GLfloat normal[3];
    GLfloat verticeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
    GLfloat verticeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
    GLfloat verticeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
    GLfloat verticeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

    // Calcular normal para a face do cubo
    FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD,
                                     normal);

    glColor3f(0.91, 0.91, 0.89); // Definir cor
    glPushMatrix();
    glTranslatef(-0.55, 0.32, 0.0f - 0.9);       // Traduzir para a posição
    glNormal3f(normal[0], normal[1], normal[2]); // Definir normal
    glutSolidCube(0.08);                         // Desenhar cubo
    glPopMatrix();
  }

  // Desenhar o segundo cubo
  {
    std::vector<std::array<GLfloat, 3>> vertices2 =
        FunctionAux::calculateCubeFaceVertices(0.08, -0.42, 0.28, 0.0f - 0.9, 1,
                                               1, 1);
    GLfloat normal[3];
    GLfloat verticeE[3] = {vertices2[0][1], vertices2[0][2], vertices2[0][3]};
    GLfloat verticeF[3] = {vertices2[1][1], vertices2[1][2], vertices2[1][3]};
    GLfloat verticeG[3] = {vertices2[2][1], vertices2[2][2], vertices2[2][3]};
    GLfloat verticeH[3] = {vertices2[3][1], vertices2[3][2], vertices2[3][3]};

    // Calcular normal para a face do cubo
    FunctionAux::calculateFlatNormal(verticeE, verticeF, verticeG, verticeH,
                                     normal);

    glColor3f(0.91, 0.91, 0.89); // Definir cor
    glPushMatrix();
    glTranslatef(-0.42, 0.28, 0.0f - 0.9);       // Traduzir para a posição
    glNormal3f(normal[0], normal[1], normal[2]); // Definir normal
    glutSolidCube(0.08);                         // Desenhar cubo
    glPopMatrix();
  }

  // Desenhar o terceiro cubo
  {
    std::vector<std::array<GLfloat, 3>> vertices =
        FunctionAux::calculateCubeFaceVertices(0.08, -0.42, 0.28, 0.0f - 0.9, 1,
                                               1, 1);
    GLfloat normal[3];
    GLfloat verticee[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
    GLfloat verticee1[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
    GLfloat verticee2[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
    GLfloat verticee3[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

    // Calcular normal para a face do cubo
    FunctionAux::calculateFlatNormal(verticee, verticee1, verticee2, verticee3,
                                     normal);

    glColor3f(0.91, 0.91, 0.89); // Definir cor
    glPushMatrix();
    glTranslatef(-0.31, 0.32, 0.0f - 0.9);       // Traduzir para a posição
    glNormal3f(normal[0], normal[1], normal[2]); // Definir normal
    glutSolidCube(0.08);                         // Desenhar cubo
    glPopMatrix();
  }

  // Desenhar o quarto cubo
  {
    std::vector<std::array<GLfloat, 3>> vertices =
        FunctionAux::calculateCubeFaceVertices(0.08, -0.2, 0.28, 0.0f - 0.9, 1,
                                               1, 1);
    GLfloat normal[3];
    GLfloat verticee4[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
    GLfloat verticee5[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
    GLfloat verticee6[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
    GLfloat verticee7[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

    // Calcular normal para a face do cubo
    FunctionAux::calculateFlatNormal(verticee4, verticee5, verticee6, verticee7,
                                     normal);

    glColor3f(0.91, 0.91, 0.89); // Definir cor
    glPushMatrix();
    glTranslatef(-0.2, 0.28, 0.0f - 0.9); // Traduzir para a posição
    glutSolidCube(0.08);                  // Desenhar cubo
    glPopMatrix();
  }
}

void wardrobe() {
  //-------------- Configuração da Parede --------
  GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Cor especular
  GLfloat shininess[] = {16.0f}; // Valor de brilho do material

  glMaterialfv(GL_FRONT, GL_SHININESS,
               shininess); // Define o brilho do material
  glMaterialfv(GL_FRONT, GL_SPECULAR,
               matSpecular); // Define a cor especular do material

  // Calcular vértices da parede
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, -0.99, 0.25, -0.8, 0.5, 5, 4);

  GLfloat normal[3]; // Array para armazenar o vetor normal calculado
  GLfloat wallA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat wallB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat wallC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat wallD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcular e definir o normal para a parede
  FunctionAux::calculateFlatNormal(wallA, wallB, wallC, wallD, normal);

  // Definir a cor da parede e desenhar a parede esquerda
  glColor3f(0.47, 0.35, 0.26);
  glPushMatrix();
  glTranslatef(-0.99, 0.25, -0.8); // Transladar para a posição
  glScalef(0.5, 5, 4);             // Escalar para as dimensões da parede
  glNormal3f(normal[0], normal[1],
             normal[2]); // Definir o normal para a iluminação
  glutSolidCube(0.1);    // Desenhar a parede
  glPopMatrix();

  // Desenhar a parede direita
  glColor3f(0.47, 0.35, 0.26);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, -0.99, 0.25, -0.8, 0.5, 5, 4);
  GLfloat wallA1[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat wallB1[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat wallC1[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat wallD1[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcular e definir o normal para a parede direita
  FunctionAux::calculateFlatNormal(wallA1, wallB1, wallC1, wallD1, normal);

  glPushMatrix();
  glTranslatef(0.99, 0.25, -0.8); // Transladar para a posição
  glScalef(0.5, 5, 4);            // Escalar para as dimensões da parede
  glNormal3f(normal[0], normal[1],
             normal[2]); // Definir o normal para a iluminação
  glutSolidCube(0.1);    // Desenhar a parede
  glPopMatrix();

  //----------- Superfície Superior ---------
  glColor3f(0.47, 0.35, 0.26);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.0, 0.5, -0.8, 20, 0.5, 4);
  GLfloat topA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat topB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat topC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat topD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcular e definir o normal para a parte superior
  FunctionAux::calculateFlatNormal(topA, topB, topC, topD, normal);

  glPushMatrix();
  glTranslatef(0.0, 0.5, -0.8); // Transladar para a posição
  glScalef(20, 0.5, 4);         // Escalar para as dimensões superiores
  glNormal3f(normal[0], normal[1],
             normal[2]); // Definir o normal para a iluminação
  glutSolidCube(0.1);    // Desenhar a superfície superior
  glPopMatrix();

  //----------- Corpo do Guarda-Roupa ---------
  glColor3f(0.38, 0.27, 0.19);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.4, 0.2, -0.9, 8, 4, 2);
  GLfloat wardrobeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat wardrobeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat wardrobeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat wardrobeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcular e definir o normal para o corpo do guarda-roupa
  FunctionAux::calculateFlatNormal(wardrobeA, wardrobeB, wardrobeC, wardrobeD,
                                   normal);

  glPushMatrix();
  glTranslatef(0.4, 0.2, -0.9); // Transladar para a posição
  glScalef(8, 4, 2);            // Escalar para as dimensões do guarda-roupa
  glNormal3f(normal[0], normal[1],
             normal[2]); // Definir o normal para a iluminação
  glutSolidCube(0.1);    // Desenhar o guarda-roupa
  glPopMatrix();

  //---------- Elementos de Design ---------
  glColor3f(0.9, 0.9, 0.9);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.1, 0.2, -0.89, 1.5, 3.5, 2);
  GLfloat designA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcular e definir o normal para o elemento de design
  FunctionAux::calculateFlatNormal(designA, designB, designC, designD, normal);

  glPushMatrix();
  glTranslatef(0.1, 0.2, -0.89); // Transladar para a posição
  glScalef(1.5, 3.5, 2);         // Escalar para as dimensões do design
  glNormal3f(normal[0], normal[1],
             normal[2]); // Definir o normal para a iluminação
  glutSolidCube(0.1);    // Desenhar o elemento de design
  glPopMatrix();

  // Desenhar o segundo elemento de design
  glColor3f(0.9, 0.9, 0.9);
  vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.4, 0.2, -0.89, 1.5, 3.5, 2);
  GLfloat designnA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat designnB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat designnC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat designnD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcular e definir o normal para o segundo elemento de design
  FunctionAux::calculateFlatNormal(designnA, designnB, designnC, designnD,
                                   normal);

  glPushMatrix();
  glTranslatef(0.4, 0.2, -0.89); // Transladar para a posição
  glScalef(1.5, 3.5, 2);         // Escalar para as dimensões do design
  glNormal3f(normal[0], normal[1],
             normal[2]); // Definir o normal para a iluminação
  glutSolidCube(0.1);    // Desenhar o segundo elemento de design
  glPopMatrix();
}

void sofa() {
  // Define a cor e propriedades do material para o sofá
  glColor3f(0.91, 0.91, 0.89);                      // Cor cinza claro
  GLfloat matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f}; // Cor especular
  GLfloat shininess[] = {16.0f}; // Fator de brilho do material

  // Aplica propriedades do material para realces especulares
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // Cria vértices para o corpo principal do sofá
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, -0.32, 0.065, -0.3, 4, 0.65,
                                             1.7);
  GLfloat normal[3]; // Array para armazenar vetores normais calculados

  // Define os cantos do corpo principal do sofá para cálculo da normal
  GLfloat sofaA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat sofaB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat sofaC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat sofaD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcula a normal para iluminação
  FunctionAux::calculateFlatNormal(sofaA, sofaB, sofaC, sofaD, normal);

  // Desenha o corpo principal do sofá
  glPushMatrix();
  glTranslatef(-0.32, 0.065, -0.3); // Translada para a posição
  glScalef(4, 0.65, 1.7);           // Escala para as dimensões
  glNormal3f(normal[0], normal[1],
             normal[2]); // Define a normal para iluminação
  glutSolidCube(0.1);    // Desenha o corpo do sofá
  glPopMatrix();

  //------ Desenha a base preta do sofá ---------
  glColor3f(0.09, 0.09, 0.09); // Cor escura para a base
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.32, 0.015, -0.3,
                                                    4.1, 0.15, 1.71);

  // Define os cantos da base para cálculo da normal
  GLfloat baseA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat baseB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat baseC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat baseD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcula a normal para iluminação
  FunctionAux::calculateFlatNormal(baseA, baseB, baseC, baseD, normal);

  // Desenha a base
  glPushMatrix();
  glTranslatef(-0.32, 0.015, -0.3); // Translada para a posição
  glScalef(4.1, 0.15, 1.71);        // Escala para as dimensões
  glNormal3f(normal[0], normal[1],
             normal[2]); // Define a normal para iluminação
  glutSolidCube(0.1);    // Desenha a base
  glPopMatrix();

  //------- Desenha as costas do sofá -----------
  glColor3f(0.19, 0.19, 0.19); // Cor cinza escura para as costas
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.32, 0.1, -0.36, 4.1,
                                                    1.3, 0.61);

  // Define os cantos das costas para cálculo da normal
  GLfloat backA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat backB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat backC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat backD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcula a normal para iluminação
  FunctionAux::calculateFlatNormal(backA, backB, backC, backD, normal);

  // Desenha as costas
  glPushMatrix();
  glTranslatef(-0.32, 0.1, -0.36); // Translada para a posição
  glScalef(4.1, 1.3, 0.61);        // Escala para as dimensões
  glNormal3f(normal[0], normal[1],
             normal[2]); // Define a normal para iluminação
  glutSolidCube(0.1);    // Desenha as costas
  glPopMatrix();

  //--------- Desenha o assento do sofá ----------
  glColor3f(0.0, 0.0, 0.0); // Cor preta para o assento
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.41, 0.092, -0.25,
                                                    1.7, 0.15, 1.0);

  // Define os cantos do assento para cálculo da normal
  GLfloat seatA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat seatB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat seatC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat seatD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcula a normal para iluminação
  FunctionAux::calculateFlatNormal(seatA, seatB, seatC, seatD, normal);

  // Desenha o assento
  glPushMatrix();
  glTranslatef(-0.41, 0.092, -0.25); // Translada para a posição
  glScalef(1.7, 0.15, 1.0);          // Escala para as dimensões
  glNormal3f(normal[0], normal[1],
             normal[2]); // Define a normal para iluminação
  glutSolidCube(0.1);    // Desenha o assento
  glPopMatrix();

  // Desenha uma parte adicional do assento
  glColor3f(0.0, 0.0, 0.0); // Cor preta para o assento adicional
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.21, 0.092, -0.25,
                                                    1.7, 0.15, 1.0);

  // Define os cantos do assento adicional para cálculo da normal
  GLfloat seatA1[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat seatB1[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat seatC1[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat seatD1[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcula a normal para iluminação
  FunctionAux::calculateFlatNormal(seatA1, seatB1, seatC1, seatD1, normal);

  // Desenha o assento adicional
  glPushMatrix();
  glTranslatef(-0.21, 0.092, -0.25); // Translada para a posição
  glScalef(1.7, 0.15, 1.0);          // Escala para as dimensões
  glNormal3f(normal[0], normal[1],
             normal[2]); // Define a normal para iluminação
  glutSolidCube(0.1);    // Desenha o assento adicional
  glPopMatrix();

  //------ Desenha o apoio lateral do sofá --------
  glColor3f(0.91, 0.91, 0.89); // Cor cinza claro para o apoio lateral
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, -0.55, 0.065, -0.3, 1,
                                                    1.4, 1.1);

  // Define os cantos do apoio lateral para cálculo da normal
  GLfloat sideA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat sideB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat sideC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat sideD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcula a normal para iluminação
  FunctionAux::calculateFlatNormal(sideA, sideB, sideC, sideD, normal);

  // Desenha o apoio lateral
  glPushMatrix();
  glTranslatef(-0.55, 0.065, -0.3); // Translada para a posição
  glScalef(1, 1.4, 1.1);            // Escala para as dimensões
  glNormal3f(normal[0], normal[1],
             normal[2]); // Define a normal para iluminação
  glutSolidCube(0.1);    // Desenha o apoio lateral
  glPopMatrix();
}

void drawRoom1() {

  glEnable(GL_LIGHT2); // Habilita a fonte de luz 2
  float light2[4][4] = {
      {0.1f, 0.1f, 0.1f, 1.f},    // Luz ambiente
      {0.08f, 0.08f, 0.08f, 1.f}, // Luz difusa
      {0.01f, 0.01f, 0.01f, 1.f}, // Luz especular
      {-0.2, 0.5, 0.0, 1.f}       // Posição da luz
  };
  // Define as propriedades da luz
  glLightfv(GL_LIGHT2, GL_AMBIENT, &light2[0][0]);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, &light2[1][0]);
  glLightfv(GL_LIGHT2, GL_SPECULAR, &light2[2][0]);
  glLightfv(GL_LIGHT2, GL_POSITION, &light2[3][0]);

  GLfloat shininess[] = {128.0f}; // Brilho do material
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  GLfloat normal[3];

  //-------------- Piso -----------------
  glColor3f(0.85, 0.85, 0.85);                   // Cor do piso
  GLfloat matSpecular[] = {0.85f, 0.85f, 0.85f}; // Especular do piso
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  glBegin(GL_POLYGON);          // Inicia o polígono do piso
  GLfloat v0[] = {1, 0.0, -1};  // Vértice 0
  GLfloat v1[] = {1, 0.0, 1};   // Vértice 1
  GLfloat v3[] = {-1, 0.0, -1}; // Vértice 3
  FunctionAux::calculateFlatNormal(v0, v1, v3, normal); // Calcula a normal
  glNormal3f(normal[0], normal[1], normal[2]);          // Define a normal
  glVertex3f(1, 0.0, -1);                               // Vértice 0
  glVertex3f(1, 0.0, 1);                                // Vértice 1
  glVertex3f(-1, 0.0, 1);                               // Vértice 2
  glVertex3f(-1, 0.0, -1);                              // Vértice 3
  glEnd(); // Finaliza o polígono do piso

  lines(); // Desenha linhas adicionais

  //-------- desenha a parede de trás do quarto ----------------
  glColor3f(0.69, 0.58, 0.56);                           // cor
  GLfloat matSpecularWallBack[] = {0.69f, 0.58f, 0.56f}; // iluminação
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularWallBack);
  glBegin(GL_POLYGON);          // Inicia o polígono da parede de trás
  GLfloat v4[] = {1, 0.5, -1};  // Vértice 4
  GLfloat v5[] = {1, 0.0, -1};  // Vértice 5
  GLfloat v6[] = {-1, 0.5, -1}; // Vértice 6
  FunctionAux::calculateFlatNormal(v4, v5, v6, normal); // Calcula a normal
  glNormal3f(normal[0], normal[1], normal[2]);          // Define a normal
  glVertex3f(1, 0.5, -1);
  glVertex3f(1, 0.0, -1);
  glVertex3f(-1, 0.0, -1);
  glVertex3f(-1, 0.5, -1);
  glEnd(); // Finaliza a parede de trás

  //---------- desenha a parede da direita do quarto -------------
  glColor3f(0.69, 0.58, 0.56);                            // Cor da parede
  GLfloat matSpecularWallRight[] = {0.69f, 0.58f, 0.56f}; // Especular da parede
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularWallRight);
  glBegin(GL_POLYGON);         // Inicia o polígono da parede direita
  GLfloat v7[] = {1, 0.5, -1}; // Vértice 8
  GLfloat v8[] = {1, 0.0, -1}; // Vértice 9
  GLfloat v9[] = {1, 0.5, 1};  // Vértice 10
  FunctionAux::calculateFlatNormal(v7, v8, v9, normal); // Calcula a normal
  glNormal3f(normal[0], normal[1], normal[2]);          // Define a normal
  glVertex3f(1, 0.5, -1);                               // Vértice 8
  glVertex3f(1, 0.0, -1);                               // Vértice 9
  glVertex3f(1, 0.0, 1);                                // Vértice 11
  glVertex3f(1, 0.5, 1);                                // Vértice 12
  glEnd(); // Finaliza o polígono da parede direita

  //---------- Parede (Esquerda) --------------
  glColor3f(1.0, 0.0, 0.0);                         // Cor da parede
  GLfloat matSpecularWallLeft[] = {1.0f, 0.f, 0.f}; // Especular da parede
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularWallLeft);
  glBegin(GL_POLYGON);           // Inicia o polígono da parede esquerda
  GLfloat v10[] = {-1, 0.5, -1}; // Vértice 13
  GLfloat v11[] = {1, 0.0, -1};  // Vértice 14
  GLfloat v12[] = {-1, 0.5, 1};  // Vértice 15
  FunctionAux::calculateFlatNormal(v10, v11, v12, normal); // Calcula a normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Define a normal
  glVertex3f(-1, 0.5, -1);                                 // Vértice 13
  glVertex3f(-1, 0.0, -1);                                 // Vértice 14
  glVertex3f(-1, 0.0, 1);                                  // Vértice 15
  glVertex3f(-1, 0.5, 1);                                  // Vértice 16
  glEnd(); // Finaliza o polígono da parede esquerda

  //---------- Roof ---------------------
  glColor3f(0.80, 0.60, 0.58);                    // Cor do telhado
  GLfloat matSpecularRoof[] = {0.80, 0.60, 0.58}; // Especular do telhado
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularRoof);
  glBegin(GL_POLYGON);           // Iniciar o polígono do telhado
  GLfloat v13[] = {-1, 0.5, -1}; // Vértice 17
  GLfloat v14[] = {-1, 0.5, 1};  // Vértice 18
  GLfloat v15[] = {1, 0.5, -1};  // Vértice 19
  FunctionAux::calculateFlatNormal(v13, v14, v15, normal); // Calcular normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Definir normal
  glVertex3f(-1, 0.5, -1);                                 // Vértice 17
  glVertex3f(-1, 0.5, 1);                                  // Vértice 18
  glVertex3f(1, 0.5, 1);                                   // Vértice 20
  glVertex3f(1, 0.5, -1);                                  // Vértice 21
  glEnd(); // Finalizar o polígono do telhado
  //--------wall(back)grey1----------------
  // Definir a cor e o material para a parede de trás
  glColor3f(0.69, 0.58, 0.56);
  GLfloat matSpecularWallBackG[] = {0.69, 0.58, 0.56};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecularWallBackG);

  // Desenhar o primeiro polígono da parede
  glBegin(GL_POLYGON);
  GLfloat v16[] = {1, 0.5, 1};                             // Vértice 1
  GLfloat v17[] = {1, 0.27, 1};                            // Vértice 2
  GLfloat v18[] = {-1, 0.5, 1};                            // Vértice 3
  FunctionAux::calculateFlatNormal(v16, v17, v18, normal); // Calcular normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Definir normal
  glVertex3f(1, 0.5, 1);                                   // Definir vértices
  glVertex3f(1, 0.27, 1);
  glVertex3f(-1, 0.27, 1);
  glVertex3f(-1, 0.5, 1);
  glEnd();

  // Desenhar o segundo polígono da parede
  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  GLfloat v19[] = {0.2, 0.0, 1};                           // Vértice 1
  GLfloat v20[] = {0.2, 0.27, 1};                          // Vértice 2
  GLfloat v21[] = {-1, 0.0, 1};                            // Vértice 3
  FunctionAux::calculateFlatNormal(v19, v20, v21, normal); // Calcular normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Definir normal
  glVertex3f(0.2, 0.0, 1);                                 // Definir vértices
  glVertex3f(0.2, 0.27, 1);
  glVertex3f(-1, 0.27, 1);
  glVertex3f(-1, 0.0, 1);
  glEnd();

  // Desenhar o terceiro polígono da parede
  glColor3f(0.69, 0.58, 0.56);
  glBegin(GL_POLYGON);
  GLfloat v22[] = {0.4, 0.0, 1};                           // Vértice 1
  GLfloat v23[] = {0.4, 0.27, 1};                          // Vértice 2
  GLfloat v24[] = {1, 0.0, 1};                             // Vértice 3
  FunctionAux::calculateFlatNormal(v22, v23, v24, normal); // Calcular normal
  glNormal3f(normal[0], normal[1], normal[2]);             // Definir normal
  glVertex3f(0.4, 0.0, 1);                                 // Definir vértices
  glVertex3f(0.4, 0.27, 1);
  glVertex3f(1, 0.27, 1);
  glVertex3f(1, 0.0, 1);
  glEnd();

  //----------------porta principal-------------
  // Define a cor e o material para a porta principal
  glColor3f(0.01, 0.012, 0.012);
  GLfloat matSpeculardoorMain[] = {0.01, 0.012, 0.012};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpeculardoorMain);
  glPushMatrix(); // Salva o estado atual da transformação

  // Calcula e transforma os vértices para a porta
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, 0.15, 0.135, 1.055, 1.5, 2.7,
                                             0.1);
  GLfloat verticeA2[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB2[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC2[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD2[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticeA2, verticeB2, verticeC2, verticeD2,
                                   normal);    // Calcula a normal
  glTranslatef(0.15, 0.135, 1.055);            // Posiciona a porta
  glRotatef(45, 0, 1, 0);                      // Rotaciona a porta
  glScalef(1.5, 2.7, 0.1);                     // Escala a porta
  glNormal3f(normal[0], normal[1], normal[2]); // Define a normal
  glutSolidCube(0.1); // Desenha a porta como um cubo sólido
  glPopMatrix();      // Restaura o estado anterior da transformação

  // Define a cor e o material para a segunda porta
  glColor3f(0.901, 0.9012, 0.9012);
  GLfloat matSpeculardoorMain1[] = {0.901, 0.9012, 0.9012};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpeculardoorMain1);
  glPushMatrix(); // Salva o estado atual da transformação

  // Calcula e transforma os vértices para a segunda porta
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, 0.15, 0.135, 1.055,
                                                    1.2, 2.2, 0.11);
  GLfloat verticeA1[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB1[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC1[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD1[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticeA1, verticeB1, verticeC1, verticeD1,
                                   normal);    // Calcula a normal
  glTranslatef(0.15, 0.135, 1.055);            // Posiciona a segunda porta
  glRotatef(45, 0, 1, 0);                      // Rotaciona a segunda porta
  glScalef(1.2, 2.2, 0.11);                    // Escala a segunda porta
  glNormal3f(normal[0], normal[1], normal[2]); // Define a normal
  glutSolidCube(0.1); // Desenha a segunda porta como um cubo sólido
  glPopMatrix();      // Restaura o estado anterior da transformação

  //---moldura da porta da frente (formas poligonais)---

  glColor3f(0.38, 0.27, 0.19); // Define uma cor marrom para a moldura da porta
  GLfloat matSpeculardoorBorder[] = {
      0.38, 0.27,
      0.19}; // Propriedades do material especular para a moldura da porta
  glMaterialfv(GL_FRONT, GL_SPECULAR,
               matSpeculardoorBorder); // Aplica as propriedades do material

  // Parte superior da moldura
  glBegin(GL_POLYGON);
  GLfloat v25[] = {0.4, 0.285, 1.0101}; // Vértice superior direito
  GLfloat v26[] = {0.4, 0.27, 1.0101};  // Vértice inferior direito
  GLfloat v27[] = {0.2, 0.285, 1.0101}; // Vértice superior esquerdo
  FunctionAux::calculateFlatNormal(
      v25, v26, v27,
      normal); // Calcula a normal para sombreamento
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.4, 0.285, 1.0101); // Define os vértices para o polígono
  glVertex3f(0.4, 0.27, 1.0101);
  glVertex3f(0.2, 0.27, 1.0101);
  glVertex3f(0.2, 0.285, 1.0101);
  glEnd();

  // Lado vertical esquerdo da moldura
  glColor3f(0.38, 0.27, 0.19); // Reaplica a cor da moldura
  glBegin(GL_POLYGON);
  GLfloat v28[] = {0.395, 0.0, 1.0101};   // Vértice inferior esquerdo
  GLfloat v29[] = {0.395, 0.285, 1.0101}; // Vértice superior esquerdo
  GLfloat v30[] = {0.41, 0.0, 1.0101};    // Vértice inferior direito
  FunctionAux::calculateFlatNormal(
      v28, v29, v30,
      normal); // Calcula a normal para sombreamento
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.395, 0.0, 1.0101); // Define os vértices para o polígono
  glVertex3f(0.395, 0.285, 1.0101);
  glVertex3f(0.41, 0.285, 1.0101);
  glVertex3f(0.41, 0.0, 1.0101);
  glEnd();

  // Lado vertical direito da moldura
  glColor3f(0.38, 0.27, 0.19); // Reaplica a cor da moldura
  glBegin(GL_POLYGON);
  GLfloat v31[] = {0.2, 0.0, 1.0101};     // Vértice inferior esquerdo
  GLfloat v32[] = {0.395, 0.285, 1.0101}; // Vértice superior direito
  GLfloat v33[] = {0.185, 0.0, 1.0101};   // Vértice inferior direito
  FunctionAux::calculateFlatNormal(
      v31, v32, v33,
      normal); // Calcula a normal para sombreamento
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.2, 0.0, 1.0101); // Define os vértices para o polígono
  glVertex3f(0.2, 0.285, 1.0101);
  glVertex3f(0.185, 0.285, 1.0101);
  glVertex3f(0.185, 0.0, 1.0101);
  glEnd();
  //---moldura da porta traseira (espelhando a moldura frontal)---

  // Parte superior traseira da moldura
  glColor3f(0.38, 0.27, 0.19); // Reaplicar cor da moldura
  glBegin(GL_POLYGON);
  GLfloat v34[] = {0.4, 0.285, 0.999}; // Vértice superior direito
  GLfloat v35[] = {0.4, 0.27, 0.999};  // Vértice inferior direito
  GLfloat v36[] = {0.2, 0.285, 0.999}; // Vértice superior esquerdo
  FunctionAux::calculateFlatNormal(v34, v35, v36,
                                   normal); // Calcular normal para sombreamento
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.4, 0.285, 0.999); // Definir vértices para o polígono
  glVertex3f(0.4, 0.27, 0.999);
  glVertex3f(0.2, 0.27, 0.999);
  glVertex3f(0.2, 0.285, 0.999);
  glEnd();

  // Lado vertical esquerdo traseiro da moldura
  glColor3f(0.38, 0.27, 0.19); // Reaplicar cor da moldura
  glBegin(GL_POLYGON);
  GLfloat v37[] = {0.395, 0.0, 0.999};   // Vértice inferior esquerdo
  GLfloat v38[] = {0.395, 0.285, 0.999}; // Vértice superior esquerdo
  GLfloat v39[] = {0.41, 0.0, 0.999};    // Vértice inferior direito
  FunctionAux::calculateFlatNormal(v37, v38, v39,
                                   normal); // Calcular normal para sombreamento
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.395, 0.0, 0.999); // Definir vértices para o polígono
  glVertex3f(0.395, 0.285, 0.999);
  glVertex3f(0.41, 0.285, 0.999);
  glVertex3f(0.41, 0.0, 0.999);
  glEnd();

  // Lado vertical direito traseiro da moldura
  glColor3f(0.38, 0.27, 0.19); // Reaplicar cor da moldura
  glBegin(GL_POLYGON);
  GLfloat v40[] = {0.2, 0.0, 0.999};   // Vértice inferior esquerdo
  GLfloat v41[] = {0.2, 0.285, 0.999}; // Vértice superior esquerdo
  GLfloat v42[] = {0.185, 0.0, 0.999}; // Vértice inferior direito
  FunctionAux::calculateFlatNormal(v40, v41, v42,
                                   normal); // Calcular normal para sombreamento
  glNormal3f(normal[0], normal[1], normal[2]);
  glVertex3f(0.2, 0.0, 0.999); // Definir vértices para o polígono
  glVertex3f(0.2, 0.285, 0.999);
  glVertex3f(0.185, 0.285, 0.999);
  glVertex3f(0.185, 0.0, 0.999);
  glEnd();

  //-------------muro da TV------
  // Calcular vértices para o muro da TV, vetor normal é calculado para
  // sombreamento plano
  vertices = FunctionAux::calculateCubeFaceVertices(0.1, 0.74, 0.25, 0.5, 5.1,
                                                    5, 9.99);
  GLfloat verticeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};
  FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD,
                                   normal);

  // Definir cor e propriedades do material para o muro da TV
  glColor3f(0.53, 0.12, 0.12);
  GLfloat matSpeculardoortvWall[] = {0.53, 0.12, 0.12};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpeculardoortvWall);

  //---------porta------------
  // Calcular vértices para a porta, vetor normal é calculado para sombreamento
  // plano
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

  //---------lâmpada do teto------------
  // Desenhar uma lâmpada de teto em forma de toro
  glColor3f(1.0, 1.0, 1.0);
  glPushMatrix();
  glTranslatef(-0.2, 0.5, 0.0);
  glRotatef(90, 1, 0, 0);
  glutSolidTorus(0.03, 0.41, 100, 100);
  glPopMatrix();

  // Chamar funções para renderizar outros objetos (paredes, caixa,
  // guarda-roupa, sofá)
  redwall();
  greywall();
  wardrobe();
  sofa();

  // Despejar para garantir que todos os comandos OpenGL sejam executados
  glFlush();
}
