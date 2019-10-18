#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

void init_matrix_random(double *input, size_t i, size_t j);

void transpose_matrix(double mat1[], double mat1_t[], int size_mat1[], int size_mat1_t[]);


void multiply_matrix(double mat1[], double mat2[], double mat_out[],
		int size_mat1[], int size_mat2[]);

void sum_matrix(double mat1[], double mat2[], int size);
void sub_matrix(double mat1[], double mat2[], int size);

double sigmoid(double val);

void apply_sigmoid_to_matrix(double mat1[], int size);

double sigmoid_prime(double z);

void hadamard_product(double mat1[], mat2[], int size_mat1[], int size_mat2[]);


#endif

