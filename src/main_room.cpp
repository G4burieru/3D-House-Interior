#include "main_room.h"
#include "functionsAux.h"
#include <GL/glut.h>

void drawCubeMainRoom(float x, float y, float z, float scaleX, float scaleY,
                      float scaleZ, const float *color) {

  // Define material especular e brilho
  GLfloat matSpecular[] = {color[0], color[1], color[2]};
  GLfloat shininess[] = {1.0f};

  // Define propriedades do material para reflexão especular
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // Calcula os vértices do cubo
  std::vector<std::array<GLfloat, 3>> vertices =
      FunctionAux::calculateCubeFaceVertices(0.1, x, y, z, scaleX, scaleY,
                                             scaleZ);

  GLfloat normal[3]; // Vetor normal para iluminação
  GLfloat verticeA[3] = {vertices[0][1], vertices[0][2], vertices[0][3]};
  GLfloat verticeB[3] = {vertices[1][1], vertices[1][2], vertices[1][3]};
  GLfloat verticeC[3] = {vertices[2][1], vertices[2][2], vertices[2][3]};
  GLfloat verticeD[3] = {vertices[3][1], vertices[3][2], vertices[3][3]};

  // Calcula a normal para a face do cubo
  FunctionAux::calculateFlatNormal(verticeA, verticeB, verticeC, verticeD,
                                   normal);

  glColor3fv(color);                // Define a cor do cubo
  glPushMatrix();                   // Salva o estado atual da matriz
  glTranslatef(x, y, z);            // Move para a posição especificada
  glScalef(scaleX, scaleY, scaleZ); // Escala o cubo
  glNormal3f(normal[0], normal[1],
             normal[2]); // Define a normal para iluminação
  glutSolidCube(0.1f);   // Desenha o cubo
  glPopMatrix();         // Restaura o estado anterior da matriz
}

void drawPolygonMainRoom(GLfloat vertices[4][3], GLfloat color[3]) {

  // Define a cor do material especular e brilho
  GLfloat matSpecular[] = {color[0], color[1], color[2]};
  GLfloat shininess[] = {1.0f};
  GLfloat normal[3]; // Array para vetores normais

  // Define propriedades do material
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);

  // Calcula a normal para o polígono
  FunctionAux::calculateNormal(vertices[0], vertices[1], vertices[3], normal);

  glBegin(GL_POLYGON); // Começa a desenhar o polígono
  glNormal3f(normal[0], normal[1],
             normal[2]); // Define a normal para iluminação

  // Define os vértices do polígono
  for (int i = 0; i < 4; i++) {
    glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
  }

  glEnd(); // Termina de desenhar o polígono
}

void mainRoomTv() {
  // Define cores
  const float colorWhite[] = {0.9f, 0.9f, 0.9f};
  const float colorShadow[] = {0.0f, 0.01f, 0.0f};
  // const float colorLine[] = {0.990f, 0.99901f, 0.9909f};
  const float colorDark[] = {0.0990f, 0.099901f, 0.09909f};
  const float colorGray[] = {0.64f, 0.64f, 0.64f};

  // Suporte da TV
  drawCubeMainRoom(0.96f, 0.2f, 1.73f, 0.1f, 4.0f, 7.0f, colorWhite);

  // Sombra
  drawCubeMainRoom(0.97f, 0.2f, 1.73f, 0.001f, 4.0f, 7.0f, colorShadow);

  // TV
  drawCubeMainRoom(0.9596f, 0.2f, 1.73f, 0.1f, 1.5f, 3.0f, colorDark);

  // Alto-falante
  drawCubeMainRoom(0.9596f, 0.075f, 2.0f, 0.6f, 1.5f, 0.5f, colorDark);
  drawCubeMainRoom(0.9599f, 0.075f, 2.0f, 0.6f, 1.52f, 0.52f, colorGray);
  drawCubeMainRoom(0.9596f, 0.075f, 1.47f, 0.6f, 1.5f, 0.5f, colorDark);
  drawCubeMainRoom(0.9599f, 0.075f, 1.47f, 0.6f, 1.52f, 0.52f, colorGray);
}

void msofa() {
  // Define cores
  const float colorBase[] = {0.9f, 0.9f, 0.9f};
  const float colorLayer2[] = {0.85f, 0.85f, 0.85f};
  const float colorRest[] = {0.95f, 0.95f, 0.95f};
  const float colorPillow[] = {0.5f, 0.8f, 0.85f};
  const float colorTable[] = {0.95f, 0.95f, 0.95f};
  const float colorTableBase[] = {0.85f, 0.85f, 0.85f};
  // const float colorFloor[] = {0.05f, 0.08f, 0.085f};

  // Base
  drawCubeMainRoom(0.0f, 0.002f, 1.7f, 1.2f, 0.5f, 3.0f, colorBase);
  drawCubeMainRoom(0.0f, 0.002f, 2.1f, 1.2f, 0.5f, 3.0f, colorBase);
  drawCubeMainRoom(0.065f, 0.002f, 2.2f, 2.5f, 0.5f, 1.2f, colorBase);
  drawCubeMainRoom(0.065f, 0.002f, 1.6f, 2.5f, 0.5f, 1.2f, colorBase);

  // Camada 2
  drawCubeMainRoom(0.0f, 0.05f, 1.7f, 1.2f, 0.5f, 3.0f, colorLayer2);
  drawCubeMainRoom(0.0f, 0.05f, 2.1f, 1.2f, 0.5f, 3.0f, colorLayer2);
  drawCubeMainRoom(0.065f, 0.05f, 2.2f, 2.5f, 0.5f, 1.2f, colorLayer2);
  drawCubeMainRoom(0.065f, 0.05f, 1.6f, 2.5f, 0.5f, 1.2f, colorLayer2);

  // Descanso
  drawCubeMainRoom(-0.06f, 0.05f, 1.7f, 0.4f, 1.5f, 3.1f, colorRest);
  drawCubeMainRoom(-0.06f, 0.05f, 2.115f, 0.4f, 1.5f, 3.1f, colorRest);

  // Desenha almofadas nas posições especificadas com rotação correta
  float pillowPositions[] = {1.7f, 1.8f, 1.6f,
                             2.0f, 2.1f, 2.2f}; // Posições das almofadas

  for (int i = 0; i < 6; ++i) {
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(-0.03f, 0.115f,
                 pillowPositions[i]); // Translada para a posição da almofada
    glScalef(0.2f, 0.5f, 0.5f);       // Escala a almofada
    glRotatef(45, 1, 0, 0);           // Rotaciona a almofada
    drawCubeMainRoom(0, 0, 0, 1.0f, 1.0f, 1.0f, colorPillow);
    glPopMatrix(); // Restaura a matriz de transformação anterior
  }

  // Mesa
  drawCubeMainRoom(0.96f, 0.01f, 1.6f, 0.25f, 0.05f, 0.25f, colorTable);
  drawCubeMainRoom(0.96f, 0.01f, 1.7f, 0.25f, 0.05f, 0.25f, colorTable);
  drawCubeMainRoom(0.96f, 0.01f, 1.8f, 0.25f, 0.05f, 0.25f, colorTable);
  drawCubeMainRoom(0.96f, 0.01f, 1.9f, 0.25f, 0.05f, 0.25f, colorTable);
  drawCubeMainRoom(0.96f, 0.01f, 1.98f, 0.25f, 0.05f, 0.25f, colorTable);

  // Base da mesa
  drawCubeMainRoom(0.96f, 0.002f, 1.7f, 0.03f, 0.05f, 0.03f, colorTableBase);
  drawCubeMainRoom(0.96f, 0.002f, 1.8f, 0.03f, 0.05f, 0.03f, colorTableBase);
  drawCubeMainRoom(0.96f, 0.002f, 1.9f, 0.03f, 0.05f, 0.03f, colorTableBase);
  drawCubeMainRoom(0.96f, 0.002f, 1.98f, 0.03f, 0.05f, 0.03f, colorTableBase);
}

void mainRoomPainting() {

  // Define as cores
  const float white[] = {0.95f, 0.95f, 0.95f};       // Branco
  const float red[] = {1.0f, 0.0f, 0.0f};            // Vermelho
  const float black[] = {0.01f, 0.01f, 0.01f};       // Preto
  const float darkGray[] = {0.095f, 0.095f, 0.095f}; // Cinza escuro

  // 1ª linha
  drawCubeMainRoom(-0.47f, 0.4f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // Borda branca
  drawCubeMainRoom(-0.47f, 0.4f, 1.041f, 0.8f, 0.8f, 0.01f,
                   red); // Interior vermelho

  drawCubeMainRoom(-0.3f, 0.4f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // Borda branca
  drawCubeMainRoom(-0.3f, 0.4f, 1.041f, 0.8f, 0.8f, 0.01f,
                   black); // Interior preto

  // 2ª linha
  drawCubeMainRoom(-0.47f, 0.25f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // Borda branca
  drawCubeMainRoom(-0.47f, 0.25f, 1.041f, 0.8f, 0.8f, 0.01f,
                   black); // Interior preto

  drawCubeMainRoom(-0.3f, 0.25f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // Borda branca
  drawCubeMainRoom(-0.3f, 0.25f, 1.041f, 0.8f, 0.8f, 0.01f,
                   red); // Interior vermelho

  // 3ª linha
  drawCubeMainRoom(-0.47f, 0.1f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // Borda branca
  drawCubeMainRoom(-0.47f, 0.1f, 1.041f, 0.8f, 0.8f, 0.01f,
                   red); // Interior vermelho

  drawCubeMainRoom(-0.3f, 0.1f, 1.04f, 1.0f, 1.0f, 0.01f,
                   white); // Borda branca
  drawCubeMainRoom(-0.3f, 0.1f, 1.041f, 0.8f, 0.8f, 0.01f,
                   black); // Interior preto

  // Pintura grande
  drawCubeMainRoom(-0.7f, 0.25f, 1.04f, 2.0f, 2.0f, 0.01f,
                   white); // Camada branca
  drawCubeMainRoom(-0.7f, 0.25f, 1.041f, 1.7f, 1.7f, 0.01f,
                   darkGray); // Camada cinza escuro
  drawCubeMainRoom(-0.7f, 0.25f, 1.042f, 1.4f, 1.4f, 0.01f,
                   red); // Camada vermelha
  drawCubeMainRoom(-0.7f, 0.25f, 1.043f, 1.1f, 1.1f, 0.01f,
                   white); // Camada interna branca

  // Linhas verticais
  drawCubeMainRoom(-0.32f, 0.25f, 1.04f, 0.03f, 5.0f, 0.01f,
                   white); // Linha vertical
  drawCubeMainRoom(-0.28f, 0.25f, 1.04f, 0.03f, 5.0f, 0.01f,
                   white); // Linha vertical
  drawCubeMainRoom(-0.45f, 0.25f, 1.04f, 0.03f, 5.0f, 0.01f,
                   white); // Linha vertical
  drawCubeMainRoom(-0.49f, 0.25f, 1.04f, 0.03f, 5.0f, 0.01f,
                   white); // Linha vertical
}

void mainRoomBase() {
  // Parede ciana
  glColor3f(0.5f, 0.8f, 0.85f);
  GLfloat color[] = {0.5f, 0.8f, 0.85f};
  GLfloat rightWall[4][3] = {{0.985f, 0.5f, 1.0f},
                             {0.985f, 0.5f, 4.6f},
                             {0.985f, 0.0f, 4.6f},
                             {0.985f, 0.0f, 1.0f}};
  drawPolygonMainRoom(rightWall, color);

  // Base do chão
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

  // Seções das paredes brancas
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

  // Seção de fundo preto
  glColor3f(0.09f, 0.09f, 0.09f);
  color[0] = 0.09f;
  color[1] = 0.09f;
  color[2] = 0.09f;
  GLfloat blackBackground[4][3] = {{-0.2f, 0.0f, 1.011f},
                                   {-0.2f, 0.5f, 1.011f},
                                   {-0.9f, 0.5f, 1.011f},
                                   {-0.9f, 0.0f, 1.011f}};
  drawPolygonMainRoom(blackBackground, color);

  // Seção da entrada
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
  // Definições de cor
  const float brown[] = {0.34f, 0.25f, 0.13f};
  const float white[] = {0.9985f, 0.9985f, 0.9985f};

  // Primeiro grande cubo marrom
  drawCubeMainRoom(0.0f, 0.49f, 1.9f, 3.0f, 0.3f, 5.0f, brown);

  // Primeiro cubo branco menor
  drawCubeMainRoom(0.0f, 0.488f, 1.9f, 2.7f, 0.3f, 4.5f, white);

  // Segundo grande cubo marrom
  drawCubeMainRoom(0.35f, 0.49f, 1.9f, 3.0f, 0.3f, 5.0f, brown);

  // Segundo cubo branco menor
  drawCubeMainRoom(0.35f, 0.488f, 1.9f, 2.7f, 0.3f, 4.5f, white);
}

void drawMainRoom() {
  // Ativar iluminação
  glEnable(GL_LIGHT1);
  float light1[4][4] = {
      {0.1f, 0.1f, 0.1f, 1.f},    // Ambiente
      {0.08f, 0.08f, 0.08f, 1.f}, // Difusa
      {0.01f, 0.01f, 0.01f, 1.f}, // Especular
      {0.0f, 0.488f, 1.9f, 1.f}   // Posição
  };

  // Definir propriedades da luz
  glLightfv(GL_LIGHT1, GL_AMBIENT, &light1[0][0]);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, &light1[1][0]);
  glLightfv(GL_LIGHT1, GL_SPECULAR, &light1[2][0]);
  glLightfv(GL_LIGHT1, GL_POSITION, &light1[3][0]);

  // Desenhar componentes da sala principal
  mainRoomBase();
  mainRoomTop();
  mainRoomTv();
  mainRoomPainting();
  msofa();
}

void drawMainDoor() {
  // Desenhar painéis da porta
  glColor3f(0.095, 0.095, 0.095);
  glBegin(GL_POLYGON);
  glVertex3f(-0.7, 0.3, 3); // Ponto 1 do painel
  glVertex3f(-0.55 - doorPositionX, 0.3,
             3 + doorPositionZ); // Ponto 2 do painel
  glVertex3f(-0.55 - doorPositionX, 0.0,
             3 + doorPositionZ); // Ponto 3 do painel
  glVertex3f(-0.7, 0.0, 3);      // Ponto 4 do painel
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-0.4, 0.3, 3); // Ponto 1 do painel
  glVertex3f(-0.55 + doorPositionX, 0.3,
             3 + doorPositionZ); // Ponto 2 do painel
  glVertex3f(-0.55 + doorPositionX, 0.0,
             3 + doorPositionZ); // Ponto 3 do painel
  glVertex3f(-0.4, 0.0, 3);      // Ponto 4 do painel
  glEnd();

  // Desenhar borda da porta
  glColor3f(0.23, 0.20, 0.23);
  glBegin(GL_POLYGON);
  glVertex3f(-0.401, 0.3, 3.01); // Ponto 1 da borda
  glVertex3f(-0.38, 0.3, 3.01);  // Ponto 2 da borda
  glVertex3f(-0.38, 0.0, 3.01);  // Ponto 3 da borda
  glVertex3f(-0.401, 0.0, 3.01); // Ponto 4 da borda
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-0.699, 0.3, 3.01); // Ponto 1 da borda
  glVertex3f(-0.72, 0.3, 3.01);  // Ponto 2 da borda
  glVertex3f(-0.72, 0.0, 3.01);  // Ponto 3 da borda
  glVertex3f(-0.699, 0.0, 3.01); // Ponto 4 da borda
  glEnd();

  glBegin(GL_POLYGON);
  glVertex3f(-0.38, 0.299, 3.01); // Ponto 1 da borda
  glVertex3f(-0.72, 0.299, 3.01); // Ponto 2 da borda
  glVertex3f(-0.72, 0.32, 3.01);  // Ponto 3 da borda
  glVertex3f(-0.38, 0.32, 3.01);  // Ponto 4 da borda
  glEnd();

  if (isDoorClosed) {
    // Desenhar design da porta
    glColor3f(0.35, 0.34, 0.35);
    glBegin(GL_POLYGON);
    glVertex3f(-0.65, 0.2, 3.01); // Design parte superior
    glVertex3f(-0.6, 0.2, 3.01);  // Design parte superior
    glVertex3f(-0.6, 0.1, 3.01);  // Design parte inferior
    glVertex3f(-0.65, 0.1, 3.01); // Design parte inferior
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.45, 0.2, 3.01); // Design parte superior
    glVertex3f(-0.5, 0.2, 3.01);  // Design parte superior
    glVertex3f(-0.5, 0.1, 3.01);  // Design parte inferior
    glVertex3f(-0.45, 0.1, 3.01); // Design parte inferior
    glEnd();

    // Desenhar linhas da porta
    glColor3f(0.9095, 0.9095, 0.9095);
    glBegin(GL_POLYGON);
    glVertex3f(-0.45, 0.099, 3.01); // Linha inferior
    glVertex3f(-0.55, 0.099, 3.01); // Linha inferior
    glVertex3f(-0.55, 0.1, 3.01);   // Linha inferior
    glVertex3f(-0.45, 0.1, 3.01);   // Linha inferior
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.45, 0.3, 3.02);   // Linha superior
    glVertex3f(-0.449, 0.3, 3.02);  // Linha superior
    glVertex3f(-0.449, 0.05, 3.02); // Linha superior
    glVertex3f(-0.45, 0.05, 3.02);  // Linha superior
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.65, 0.2, 3.02);   // Linha do design
    glVertex3f(-0.55, 0.2, 3.02);   // Linha do design
    glVertex3f(-0.55, 0.201, 3.02); // Linha do design
    glVertex3f(-0.65, 0.201, 3.02); // Linha do design
    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-0.65, 0.0, 3.02);   // Linha da base
    glVertex3f(-0.651, 0.0, 3.02);  // Linha da base
    glVertex3f(-0.651, 0.25, 3.02); // Linha da base
    glVertex3f(-0.65, 0.25, 3.02);  // Linha da base
    glEnd();
  }
}
