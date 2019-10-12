#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

void init_matrix_random(double *input, size_t i, size_t j);


void multiply_matrix(double mat1[], double mat2[], double mat_out[],
		int size_mat1[], int size_mat2[]);

void sum_matrix(double mat1[], double mat2[], int size);

double sigmoid(double val);

void apply_sigmoid_to_matrix(double mat1[], int size);

double sigmoid_prime(double z);



#endif

