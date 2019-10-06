#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

void init_matrix_random(double *input, size_t i, size_t j);
void multiply_matrix(double mat1[], double mat2[],double output[],                            
      size_t larg_mat1, size_t larg_mat2, size_t haut_mat1, size_t haut_mat2); 
double sigmoid(double val);
double sigmoid_prime(double z);
#endif

