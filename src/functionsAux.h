#ifndef AUX_H
#define AUX_H

#include <GL/glut.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

/* Classe com funções auxiliares para cálculo de centro e normais de polígonos
 */
class FunctionAux {
public:
  /* Ordena vértices em ordem decrescente no eixo z */
  static bool compareByZ(const std::array<GLfloat, 3> &a,
                         const std::array<GLfloat, 3> &b) {
    return a[2] > b[2]; // Ordena pelos valores decrescentes de z
  }

  /* Calcula o vetor normal dado 3 vértices */
  static void calculateNormal(const GLfloat v0[3], const GLfloat v1[3],
                              const GLfloat v2[3], GLfloat normal[3]) {
    GLfloat diff1[3], diff2[3];

    // Calcula as diferenças dos vetores v1-v0 e v2-v0
    diff1[0] = v1[0] - v0[0];
    diff1[1] = v1[1] - v0[1];
    diff1[2] = v1[2] - v0[2];

    diff2[0] = v2[0] - v0[0];
    diff2[1] = v2[1] - v0[1];
    diff2[2] = v2[2] - v0[2];

    // Produto vetorial de diff1 e diff2
    normal[0] = diff1[1] * diff2[2] - diff1[2] * diff2[1];
    normal[1] = diff1[2] * diff2[0] - diff1[0] * diff2[2];
    normal[2] = diff1[0] * diff2[1] - diff1[1] * diff2[0];

    // Normaliza o vetor normal
    GLfloat div = sqrt(normal[0] * normal[0] + normal[1] * normal[1] +
                       normal[2] * normal[2]);
    for (int i = 0; i < 3; i++) {
      normal[i] /= div;
    }
  }

  /* Calcula a normal plana para uma face com 4 vértices */
  static void calculateFlatNormal(const GLfloat v0[3], const GLfloat v1[3],
                                  const GLfloat v2[3], const GLfloat v3[3],
                                  GLfloat normal[3]) {
    GLfloat center[3] = {(v0[0] + v1[0] + v2[0] + v3[0]) / 4,
                         (v0[1] + v1[1] + v2[1] + v3[1]) / 4,
                         (v0[2] + v1[2] + v2[2] + v3[2]) / 4};

    // Calcula os vetores v0-centro e v1-centro
    GLfloat diff1[3] = {v0[0] - center[0], v0[1] - center[1],
                        v0[2] - center[2]};
    GLfloat diff2[3] = {v1[0] - center[0], v1[1] - center[1],
                        v1[2] - center[2]};

    // Produto vetorial e normalização
    normal[0] = diff1[1] * diff2[2] - diff1[2] * diff2[1];
    normal[1] = diff1[2] * diff2[0] - diff1[0] * diff2[2];
    normal[2] = diff1[0] * diff2[1] - diff1[1] * diff2[0];

    GLfloat div = sqrt(normal[0] * normal[0] + normal[1] * normal[1] +
                       normal[2] * normal[2]);
    for (int i = 0; i < 3; i++) {
      normal[i] /= div;
    }
  }

  /* Calcula a normal plana para uma face com 3 vértices */
  static void calculateFlatNormal(const GLfloat v0[3], const GLfloat v1[3],
                                  const GLfloat v2[3], GLfloat normal[3]) {
    GLfloat center[3] = {(v0[0] + v1[0] + v2[0]) / 3,
                         (v0[1] + v1[1] + v2[1]) / 3,
                         (v0[2] + v1[2] + v2[2]) / 3};

    // Calcula os vetores v0-centro e v1-centro
    GLfloat diff1[3] = {v0[0] - center[0], v0[1] - center[1],
                        v0[2] - center[2]};
    GLfloat diff2[3] = {v1[0] - center[0], v1[1] - center[1],
                        v1[2] - center[2]};

    // Produto vetorial e normalização
    normal[0] = diff1[1] * diff2[2] - diff1[2] * diff2[1];
    normal[1] = diff1[2] * diff2[0] - diff1[0] * diff2[2];
    normal[2] = diff1[0] * diff2[1] - diff1[1] * diff2[0];

    GLfloat div = sqrt(normal[0] * normal[0] + normal[1] * normal[1] +
                       normal[2] * normal[2]);
    for (int i = 0; i < 3; i++) {
      normal[i] /= div;
    }
  }

  /* Calcula os vértices da face frontal de um cubo */
  static std::vector<std::array<GLfloat, 3>>
  calculateCubeFaceVertices(float size, float x, float y, float z, float scaleX,
                            float scaleY, float scaleZ) {

    float halfSize = size / 2.0f; // Metade do tamanho do cubo

    // Define os vértices do cubo
    std::vector<std::array<GLfloat, 3>> vertices = {
        {{-halfSize, -halfSize, -halfSize}}, {{halfSize, -halfSize, -halfSize}},
        {{halfSize, halfSize, -halfSize}},   {{-halfSize, halfSize, -halfSize}},
        {{-halfSize, -halfSize, halfSize}},  {{halfSize, -halfSize, halfSize}},
        {{halfSize, halfSize, halfSize}},    {{-halfSize, halfSize, halfSize}}};

    // Aplica escalonamento e translação
    for (auto &vertex : vertices) {
      vertex[0] = vertex[0] * scaleX + x;
      vertex[1] = vertex[1] * scaleY + y;
      vertex[2] = vertex[2] * scaleZ + z;
    }

    // Ordena os vértices por valores decrescentes de z
    std::sort(vertices.begin(), vertices.end(), FunctionAux::compareByZ);

    // Retorna os 4 vértices da face frontal
    std::vector<std::array<GLfloat, 3>> face(vertices.begin(),
                                             vertices.begin() + 4);
    return face;
  }
};

#endif
