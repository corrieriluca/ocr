#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

int index_max_matrix(double mat[], int size[]);

void transpose_matrix(double mat1[], double mat1_t[],
		int size_mat1[], int size_mat1_t[]);

void multiply_matrix(double mat1[], double mat2[], double mat_out[],
		int size_mat1[], int size_mat2[]);

void add_matrix(double mat1[], double mat2[],
		int size_mat1[], int size_mat2[]);

void subtract_matrix(double mat1[], double mat2[], double mat_out[],
		int size_mat1[], int size_mat2[]);

double sigmoid(double val);

void apply_sigmoid_to_matrix(double mat1[], int size[]);

double sigmoid_prime(double z);

void apply_sigmoid_prime_to_matrix(double mat1[], double mat_out[],
		int size_mat1[], int size_mat_out[]);

void hadamard_product(double mat1[], double mat2[], double mat_out[],
		int size_mat1[], int size_mat2[]);

void multiply_matrix_by_constant(double mat1[], double c, double mat_out[],
		int size_mat1[], int size_mat_out[]);

#endif

