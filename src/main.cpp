#include "kitchen.h"
#include "main_room.h"
#include "room1.h"

#include "functionsAux.h"
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MIN_X -2.5 // Coordenada X mínima
#define MAX_X 0.8  // Coordenada X máxima
#define MIN_Y 0.1  // Coordenada Y mínima
#define MAX_Y 0.5  // Coordenada Y máxima
#define MIN_Z -0.5 // Coordenada Z mínima
#define MAX_Z 5.0  // Coordenada Z máxima

// Variáveis de posição da porta
GLfloat doorPositionX = 0.0, doorPositionZ = 0.0;
int isDoorClosed = 1; // Estado da porta (fechada = 1)
float lookAtX = 0.0f, lookAtZ = -1.0f, rotationAngle = 0.0f;
static GLdouble viewerPosition[] = {0.0, 0.2, 4.2}; // Posição do espectador
static GLdouble lookAtPosition[] = {0.0, 0.2, 0.0}; // Posição do ponto de visão

// Valores de cor RGB
GLfloat colorRed = 0, colorGreen = 0, colorBlue = 0;

void *fontStyle =
    GLUT_BITMAP_HELVETICA_18; // Estilo de fonte para renderizar texto

void renderText(float x, float y, const char *text) {
  // Define a posição do texto
  glRasterPos2f(x, y);
  // Renderiza cada caractere da string
  for (unsigned int i = 0; i < strlen(text); i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
  }
}

void updateColors(int) {
  // Incrementa os valores RGB
  colorRed += 0.01;
  colorBlue += 0.001;
  colorGreen += 0.0001;

  // Reinicia se os valores excederem 1.0
  if (colorRed > 1.0)
    colorRed = 0;
  if (colorBlue > 1.0)
    colorBlue = 0;
  if (colorGreen > 1.0)
    colorGreen = 0;

  glutPostRedisplay();                 // Solicita atualização da exibição
  glutTimerFunc(100, updateColors, 0); // Chama novamente após 100ms
}

void openDoor(int v) {
  // Incrementa a posição da porta dentro dos limites
  if (doorPositionX < 0.2 && doorPositionZ < 0.2) {
    doorPositionX += 0.01;
    doorPositionZ += 0.01;
  }
  isDoorClosed = 0; // Marca a porta como aberta

  glutPostRedisplay();             // Solicita atualização da exibição
  glutTimerFunc(100, openDoor, 0); // Chama novamente após 100ms
}

void displayText() {
  if (isDoorClosed) {
    // Exibe a mensagem de prompt da porta
    renderText(-0.999, -0.500, "Pressione 'O' para abrir a porta");
    glFlush(); // Força a renderização
  }
}

void drawOuterCover() {
  // Define a cor e propriedades do material
  glColor3f(196.0f / 255.0f, 160.0f / 255.0f, 112.0f / 255.0f);
  GLfloat matSpecular[] = {1.f, 1.f, 1.f, 1.f};
  glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
  GLfloat shininess[] = {128.0f};
  glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

  GLfloat normal[3];
  glBegin(GL_POLYGON);

  // Calcula a normal para o primeiro polígono
  GLfloat v0[] = {-1, 0.0, 3};
  GLfloat v1[] = {-1, 0.5, 3};
  GLfloat v3[] = {-1, 0.0, 4};
  GLfloat vv[] = {-1, 0.5, 4};
  FunctionAux::calculateFlatNormal(v0, v1, v3, vv, normal);

  glNormal3f(normal[0], normal[1], normal[2]); // Aplica a normal
  glVertex3f(v0[0], v0[1], v0[2]);
  glVertex3f(v1[0], v1[1], v1[2]);
  glVertex3f(-1, 0.5, 4);
  glVertex3f(v3[0], v3[1], v3[2]);
  glEnd();

  glBegin(GL_POLYGON);

  // Calcula a normal para o segundo polígono
  GLfloat v4[] = {-3, 0.52, 3};
  GLfloat v5[] = {-3, 0.52, -1};
  GLfloat v6[] = {3, 0.52, 3};
  GLfloat vv1[] = {3, 0.52, -1};
  FunctionAux::calculateFlatNormal(v4, v5, v6, vv1, normal);
  glNormal3f(normal[0], normal[1], normal[2]); // Aplica a normal
  glVertex3f(-3, 0.52, 3);
  glVertex3f(-3, 0.52, -1);
  glVertex3f(3, 0.52, -1);
  glVertex3f(3, 0.52, 3);
  glEnd();

  glBegin(GL_POLYGON);

  // Calcula a normal para o terceiro polígono
  GLfloat v7[] = {-3, -0.02, 2.5};
  GLfloat v8[] = {-3, -0.02, -1};
  GLfloat v9[] = {3, -0.02, 2.5};
  GLfloat vv2[] = {3, -0.02, -1};
  FunctionAux::calculateFlatNormal(v7, v8, v9, vv2, normal);
  glNormal3f(normal[0], normal[1], normal[2]); // Aplica a normal
  glVertex3f(-3, -0.02, 2.5);
  glVertex3f(-3, -0.02, -1);
  glVertex3f(3, -0.02, -1);
  glVertex3f(3, -0.02, 2.5);
  glEnd();
}

void renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa os buffers
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Define a posição da câmera e a direção da visão
  gluLookAt(viewerPosition[0], viewerPosition[1], viewerPosition[2],
            viewerPosition[0] + lookAtX, lookAtPosition[1],
            viewerPosition[2] + lookAtZ, 0.0, 1.0, 0.0);

  // Exibe texto na cena
  glPushMatrix();
  glTranslatef(0.0, 0.2, 3.2);
  glScalef(0.5, 0.5, 0.0);
  displayText();
  glPopMatrix();

  // Chamando função que desenha as principais partes da casa: porta da frente,
  // quarto, cozinha e sala de estar, respectivamente
  drawMainDoor();
  drawRoom1();
  drawKitchen();
  drawMainRoom();

  glutSwapBuffers(); // Troca os buffers para o double buffering
}

void checkCollisions(int &orgZ) {

  std::vector<std::vector<float>> wall_boundaries = {{3.7, 3}, {1.4, 0.6}};
  std::vector<std::vector<float>> door = {{-0.85, -0.12}, {0.3, 0.1}};

  // Detecção de colisão para os limites de profundidade e de lateralidade da
  // "casa"
  if (viewerPosition[2] <= MIN_Z)
    viewerPosition[2] = MIN_Z;
  if (viewerPosition[2] >= MAX_Z)
    viewerPosition[2] = MAX_Z;
  if (viewerPosition[0] <= MIN_X)
    viewerPosition[0] = MIN_X;
  if (viewerPosition[0] >= MAX_X)
    viewerPosition[0] = MAX_X;
}

void handleKeyPress(unsigned char key, int x, int y) {
  // Movimento do usuário com W, A, S, D
  // int originalX = viewerPosition[0];
  int originalZ = viewerPosition[2];

  switch (key) {
  case 'w': // Mover para frente
    viewerPosition[0] += lookAtX * 0.1;
    viewerPosition[2] += lookAtZ * 0.1;
    break;

  case 's': // Mover para trás
    viewerPosition[0] -= lookAtX * 0.1;
    viewerPosition[2] -= lookAtZ * 0.1;
    break;

  case 'a': // Deslocar para a esquerda
    viewerPosition[0] -= cos(rotationAngle) * 0.01;
    viewerPosition[2] += sin(rotationAngle) * 0.01;
    break;

  case 'd': // Deslocar para a direita
    viewerPosition[0] += cos(rotationAngle) * 0.01;
    viewerPosition[2] -= sin(rotationAngle) * 0.01;
    break;

  case 'o': // Abrir a porta
    openDoor(0);
    break;
  }

  checkCollisions(originalZ);

  glutPostRedisplay(); // Atualiza a cena
}

void handleSpecialKeyPress(int key, int x, int y) {
  float rotationSpeed = 0.04f; // Velocidade de rotação

  switch (key) {
  case GLUT_KEY_LEFT: // Rotacionar para a esquerda
    rotationAngle -= rotationSpeed;
    break;
  case GLUT_KEY_RIGHT: // Rotacionar para a direita
    rotationAngle += rotationSpeed;
    break;
  case GLUT_KEY_UP: // Mover para cima
    viewerPosition[1] += 0.1;

    // Detecção de colisão para o limite superior de Y
    if (viewerPosition[1] >= MAX_Y) {
      viewerPosition[1] = MAX_Y;
    }
    break;
  case GLUT_KEY_DOWN: // Mover para baixo
    viewerPosition[1] -= 0.1;

    // Detecção de colisão para o limite inferior de Y
    if (viewerPosition[1] <= MIN_Y) {
      viewerPosition[1] = MIN_Y;
    }
    break;
  }

  // Atualiza a direção com base no novo ângulo de rotação
  lookAtX = sin(rotationAngle);
  lookAtZ = -cos(rotationAngle);

  glutPostRedisplay(); // Atualiza a exibição
}

void adjustViewportSize(int width, int height) {
  if (height == 0)
    height = 1; // Evitar divisão por zero
  float aspectRatio = width * 1.0 / height;

  // Define o viewport e ajusta a perspectiva
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(40.0f, aspectRatio, 0.1f, 10.0f);
  glMatrixMode(GL_MODELVIEW);

  glutPostRedisplay(); // Atualiza a exibição
}

int main(int argc, char **argv) {
  // Inicializa o GLUT e define o modo de exibição com double buffering e cores
  // RGBA
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_ALPHA);

  // Define o tamanho e a posição da janela
  glutInitWindowSize(1000, 800);
  glutInitWindowPosition(0, 0);

  // Cria a janela principal
  glutCreateWindow("Arquitetura de Casa 3D");

  // Ativa a iluminação
  glEnable(GL_LIGHTING);

  // Ativa o tratamento da cor do material
  glEnable(GL_COLOR_MATERIAL);

  // Define a cor do material para afetar tanto a frente quanto as costas dos
  // objetos
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  // Define a iluminação ambiente global
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  float globalAmb[] = {0.5f, 0.5f, 0.5f, 1.f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

  // Configura a matriz de visualização
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Registra as funções de exibição e de redimensionamento
  glutDisplayFunc(renderScene);
  glutReshapeFunc(adjustViewportSize);

  // Define a função de profundidade e manipula eventos de entrada
  glDepthFunc(GL_LEQUAL);
  glutSpecialFunc(handleSpecialKeyPress);
  glutKeyboardFunc(handleKeyPress);

  // Ativa a transparência e o teste de profundidade
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);

  // Inicializa as cores e ativa o teste de alfa
  updateColors(0);
  glAlphaFunc(GL_GREATER, 0.1);
  glEnable(GL_ALPHA_TEST);

  // Define a cor de fundo como branca
  glClearColor(1.0, 1.0, 1.0, 1.0);

  // Inicia o loop principal de eventos
  glutMainLoop();

  return 0;
}
