#ifndef AUX_H
#define AUX_H

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <cmath>
#include <array>
#include <algorithm>
#include <iostream>

/* Classe com funções auxiliares para cálculos de centro e normal de poligonos */
class FunctionAux{
    public: 
        
        /* Ordena vértices em ordem decrescente de z*/
        static bool compareByZ(const std::array<GLfloat, 3>& a, const std::array<GLfloat, 3>& b) {
            return a[2] > b[2];  // Ordena em ordem decrescente de z
        }
        
        /* Realiza o cálculo de uma normal dado apenas 3 vértices */
        static void calculateNormal(const GLfloat v0[3], const GLfloat v1[3], const GLfloat v2[3], GLfloat normal [3]){
            GLfloat diff1 [3];
            GLfloat diff2 [3];
            
            /* Calcula dois vetores que são a diferena de V1 - V0 e V3 - V0 */
            diff1[0] = v1[0] - v0[0];
            diff1[1] = v1[1] - v0[1]; 
            diff1[2] = v1[2] - v0[2];

            diff2[0] = v2[0] - v0[0];
            diff2[1] = v2[1] - v0[1];
            diff2[2] = v2[2] - v0[2];
            
            /* produto vetorial entre diff1xdiff2 */
            normal[0] = (diff1[1] * diff2[2]) - (diff1[2] * diff2[1]);
            normal[1] = (diff1[2] * diff2[0]) - (diff1[0] * diff2[2]);
            normal[2] = (diff1[0] * diff2[1]) - (diff1[1] * diff2[0]);
            
            /* Operação de normalização do vetor */
            GLfloat div = sqrt((float)normal[0] * (float)normal[0] + (float)normal[1] * (float)normal[1] + (float)normal[2] * (float)normal[2]);

            
            for(int i = 0; i < 3; i++){
                normal[i] = normal[i]/div;
            }
        }
        
        /* Realiza o cálculo da normal flat para vetores com 4 vértices*/
        static void calculateFlatNormal(const GLfloat v0[3], const GLfloat v1[3], const GLfloat v2[3], const GLfloat v3[3],GLfloat normal[3]){
            GLfloat center[3];
            center[0] = v0[0] + v1[0] + v2[0]  + v3[0]/ 4;
            center[1] = v0[1] + v1[1] + v2[1]  + v3[1]/ 4;
            center[2] = v0[2] + v1[2] + v2[2]  + v3[2]/ 4;

            GLfloat diff1 [3];
            GLfloat diff2 [3];
            
            /* Calcula dois vetores que são a diferena de V1 - V0 e V3 - V0 */
            diff1[0] = v0[0] - center[0];
            diff1[1] = v0[1] - center[1]; 
            diff1[2] = v0[2] - center[2];

            diff2[0] = v1[0] - center[0];
            diff2[1] = v1[1] - center[1];
            diff2[2] = v1[2] - center[2];
            /* produto vetorial entre diff1xdiff2 */
            normal[0] = (diff1[1] * diff2[2]) - (diff1[2] * diff2[1]);
            normal[1] = (diff1[2] * diff2[0]) - (diff1[0] * diff2[2]);
            normal[2] = (diff1[0] * diff2[1]) - (diff1[1] * diff2[0]);
            
            /* Operação de normalização do vetor */
            GLfloat div = sqrt((float)normal[0] * (float)normal[0] + (float)normal[1] * (float)normal[1] + (float)normal[2] * (float)normal[2]);

            for(int i = 0; i < 3; i++){
                normal[i] = normal[i]/div;
            }
        }

        /* Realiza o cálculo da normal flat para vetores com 3 vértices*/
        static void calculateFlatNormal(const GLfloat v0[3], const GLfloat v1[3], const GLfloat v2[3],GLfloat normal[3]){
            GLfloat center[3];
            center[0] = v0[0] + v1[0] + v2[0] / 3;
            center[1] = v0[1] + v1[1] + v2[1]/ 3;
            center[2] = v0[2] + v1[2] + v2[2]/ 3;

            GLfloat diff1 [3];
            GLfloat diff2 [3];
            
            /* Calcula dois vetores que são a diferena de V1 - V0 e V3 - V0 */
            diff1[0] = v0[0] - center[0];
            diff1[1] = v0[1] - center[1]; 
            diff1[2] = v0[2] - center[2];

            diff2[0] = v1[0] - center[0];
            diff2[1] = v1[1] - center[1];
            diff2[2] = v1[2] - center[2];
            /* produto vetorial entre diff1xdiff2 */
            normal[0] = (diff1[1] * diff2[2]) - (diff1[2] * diff2[1]);
            normal[1] = (diff1[2] * diff2[0]) - (diff1[0] * diff2[2]);
            normal[2] = (diff1[0] * diff2[1]) - (diff1[1] * diff2[0]);
            
            GLfloat div = sqrt((float)normal[0] * (float)normal[0] + (float)normal[1] * (float)normal[1] + (float)normal[2] * (float)normal[2]);

            for(int i = 0; i < 3; i++){
                normal[i] = normal[i]/div;
            }
        }
        
        /* Função responsável por cálcular os vértices da face frontal de um cubo*/
        static std::vector<std::array<GLfloat, 3>> calculateCubeFaceVertices(
            float size, float x, float y, float z, float scaleX, float scaleY, float scaleZ) {
            
            float halfSize = size / 2.0f; // Tamanho do lado dividido por 2
            
            // Vértices do cubo, divide o cubo em vértices, supondo que é criado a partir do seu meio
            std::vector<std::array<GLfloat, 3>> vertices = {
                {{-halfSize, -halfSize, -halfSize}},
                {{halfSize, -halfSize, -halfSize}},
                {{halfSize,  halfSize, -halfSize}},
                {{-halfSize,  halfSize, -halfSize}},
                {{-halfSize, -halfSize,  halfSize}},
                {{halfSize, -halfSize,  halfSize}},
                {{halfSize,  halfSize,  halfSize}},
                {{-halfSize,  halfSize,  halfSize}}
            };

            // Aplicar as transformações de escala e translação
            for (auto& vertex : vertices) {
                vertex[0] = vertex[0] * scaleX + x; // Escala e translação no eixo X
                vertex[1] = vertex[1] * scaleY + y; // Escala e translação no eixo Y
                vertex[2] = vertex[2] * scaleZ + z; // Escala e translação no eixo Z
            }

            // Ordenar os vértices em ordem decrescente de z
            std::sort(vertices.begin(), vertices.end(), FunctionAux::compareByZ);

            // Selecionar os 4 vértices com maiores valores de z (frente do cubo)
            std::vector<std::array<GLfloat, 3>> face;
            for (int i = 0; i < 4; ++i) {
                face.push_back(vertices[i]);
            }

            return face;
        }
        
};


#endif




