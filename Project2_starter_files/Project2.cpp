/* Project2.cpp
 * Ima Student
 * EE312, Summer 2017
 * Project 2, Matrix Multiplication
 */

#include <stdio.h>
#include <stdint.h>
#include "MatrixMultiply.h"
#include <stdlib.h>

void multiplyMatrices(
        double a[],
        const uint32_t a_rows,
        const uint32_t a_cols,
        double b[],
        const uint32_t b_cols,
        double c[]){
    for(uint32_t i = 0; i < a_rows; i++){    
        for(uint32_t j = 0; j < b_cols; j++){
            c[i * b_cols + j] = 0;
            for(uint32_t k = 0; k < a_cols; k++){
                c[i * b_cols + j] += (a[i * a_cols + k] * b[k * b_cols + j]); //multipy row element in a by corresponding element in b
            }
        }
    }
}

double** multiplyMatricesPtr(
        double** a,
        const uint32_t a_rows,
        const uint32_t a_cols,
        double** b,
        const uint32_t b_cols) {
    double** c = (double **)malloc(sizeof(double *) * a_rows);
    for (uint32_t z = 0; z < a_rows; z++) {
        *(c + z) = (double *)malloc(sizeof(double) * b_cols);
    }
    for(uint32_t i = 0; i < a_rows; i++){
        for(uint32_t j = 0; j < b_cols; j++){
            c[i][j] = 0;
            for (uint32_t k = 0; k < a_cols; k++){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

// https://en.wikipedia.org/wiki/Transpose
double** transposeMatrix(
         double** a,
         const uint32_t a_rows,
         const uint32_t a_cols) {
    double** b = (double **)malloc(sizeof(double*) * a_cols);
    for(uint32_t z = 0; z < a_cols; z++){
        *(b + z) = (double *)malloc(sizeof(double) * a_rows);
    }
    for(uint32_t i = 0; i < a_cols; i++){
        for(uint32_t j = 0; j < a_rows; j++){
            b[i][j] = a[j][i];
        }
    }
    return b;
}
