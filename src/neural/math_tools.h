#ifndef MATH_TOOLS_H
#define MATH_TOOLS_H

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

void apply_softmax_to_matrix(double mat[], int size[]);

void init_a0(double *a0, int *size_a0, char *good_char, FILE *matrix_db,        
        FILE *char_db);                                                         
                                                                                
int index_max_matrix(double mat[], int size[]);

double cost_function(double mat1[], double mat2[], int size1[], int size2[]);

char find_index_letter(double *output_a2, int *size);                           
                                                                                
int wanted_letter(char *letter);

#endif
