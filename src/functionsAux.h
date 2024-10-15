#ifndef AUX_H
#define AUX_H

#include <GL/glut.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>

/* Class with auxiliary functions for polygon center and normal calculations */
class FunctionAux {
public:
  /* Sort vertices in descending order of z-axis */
  static bool compareByZ(const std::array<GLfloat, 3> &a,
                         const std::array<GLfloat, 3> &b) {
    return a[2] > b[2]; // Sort by descending z values
  }

  /* Calculate normal vector given 3 vertices */
  static void calculateNormal(const GLfloat v0[3], const GLfloat v1[3],
                              const GLfloat v2[3], GLfloat normal[3]) {
    GLfloat diff1[3], diff2[3];

    // Calculate vector differences v1-v0 and v2-v0
    diff1[0] = v1[0] - v0[0];
    diff1[1] = v1[1] - v0[1];
    diff1[2] = v1[2] - v0[2];

    diff2[0] = v2[0] - v0[0];
    diff2[1] = v2[1] - v0[1];
    diff2[2] = v2[2] - v0[2];

    // Cross product of diff1 and diff2
    normal[0] = diff1[1] * diff2[2] - diff1[2] * diff2[1];
    normal[1] = diff1[2] * diff2[0] - diff1[0] * diff2[2];
    normal[2] = diff1[0] * diff2[1] - diff1[1] * diff2[0];

    // Normalize the normal vector
    GLfloat div = sqrt(normal[0] * normal[0] + normal[1] * normal[1] +
                       normal[2] * normal[2]);
    for (int i = 0; i < 3; i++) {
      normal[i] /= div;
    }
  }

  /* Calculate flat normal for a face with 4 vertices */
  static void calculateFlatNormal(const GLfloat v0[3], const GLfloat v1[3],
                                  const GLfloat v2[3], const GLfloat v3[3],
                                  GLfloat normal[3]) {
    GLfloat center[3] = {(v0[0] + v1[0] + v2[0] + v3[0]) / 4,
                         (v0[1] + v1[1] + v2[1] + v3[1]) / 4,
                         (v0[2] + v1[2] + v2[2] + v3[2]) / 4};

    // Calculate vectors v0-center and v1-center
    GLfloat diff1[3] = {v0[0] - center[0], v0[1] - center[1],
                        v0[2] - center[2]};
    GLfloat diff2[3] = {v1[0] - center[0], v1[1] - center[1],
                        v1[2] - center[2]};

    // Cross product and normalization
    normal[0] = diff1[1] * diff2[2] - diff1[2] * diff2[1];
    normal[1] = diff1[2] * diff2[0] - diff1[0] * diff2[2];
    normal[2] = diff1[0] * diff2[1] - diff1[1] * diff2[0];

    GLfloat div = sqrt(normal[0] * normal[0] + normal[1] * normal[1] +
                       normal[2] * normal[2]);
    for (int i = 0; i < 3; i++) {
      normal[i] /= div;
    }
  }

  /* Calculate flat normal for a face with 3 vertices */
  static void calculateFlatNormal(const GLfloat v0[3], const GLfloat v1[3],
                                  const GLfloat v2[3], GLfloat normal[3]) {
    GLfloat center[3] = {(v0[0] + v1[0] + v2[0]) / 3,
                         (v0[1] + v1[1] + v2[1]) / 3,
                         (v0[2] + v1[2] + v2[2]) / 3};

    // Calculate vectors v0-center and v1-center
    GLfloat diff1[3] = {v0[0] - center[0], v0[1] - center[1],
                        v0[2] - center[2]};
    GLfloat diff2[3] = {v1[0] - center[0], v1[1] - center[1],
                        v1[2] - center[2]};

    // Cross product and normalization
    normal[0] = diff1[1] * diff2[2] - diff1[2] * diff2[1];
    normal[1] = diff1[2] * diff2[0] - diff1[0] * diff2[2];
    normal[2] = diff1[0] * diff2[1] - diff1[1] * diff2[0];

    GLfloat div = sqrt(normal[0] * normal[0] + normal[1] * normal[1] +
                       normal[2] * normal[2]);
    for (int i = 0; i < 3; i++) {
      normal[i] /= div;
    }
  }

  /* Calculate front face vertices of a cube */
  static std::vector<std::array<GLfloat, 3>>
  calculateCubeFaceVertices(float size, float x, float y, float z, float scaleX,
                            float scaleY, float scaleZ) {

    float halfSize = size / 2.0f; // Half of the cube size

    // Define the cube vertices
    std::vector<std::array<GLfloat, 3>> vertices = {
        {{-halfSize, -halfSize, -halfSize}}, {{halfSize, -halfSize, -halfSize}},
        {{halfSize, halfSize, -halfSize}},   {{-halfSize, halfSize, -halfSize}},
        {{-halfSize, -halfSize, halfSize}},  {{halfSize, -halfSize, halfSize}},
        {{halfSize, halfSize, halfSize}},    {{-halfSize, halfSize, halfSize}}};

    // Apply scaling and translation
    for (auto &vertex : vertices) {
      vertex[0] = vertex[0] * scaleX + x;
      vertex[1] = vertex[1] * scaleY + y;
      vertex[2] = vertex[2] * scaleZ + z;
    }

    // Sort vertices by descending z values
    std::sort(vertices.begin(), vertices.end(), FunctionAux::compareByZ);

    // Return the 4 vertices of the front face
    std::vector<std::array<GLfloat, 3>> face(vertices.begin(),
                                             vertices.begin() + 4);
    return face;
  }
};

#endif
