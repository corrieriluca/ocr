#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void init_matrix_random(double *input, size_t i, size_t j)
{
        srand(time(NULL));
        for(size_t index = 0; index < i * j; ++index)
        {
          input[index] = (double)rand()/(double)RAND_MAX;
        }
}


void transpose_matrix(double mat1[], double mat1_t[], int size_mat1[], int size_mat1_t[])
{
	for (int i = 0; i < size_mat1[1]; i++)
	{
		for (int j = 0; j < size_mat1[0]; j++)
		{
			mat1_t[j + i * size_mat1[0]] = mat1[i + j * size_mat1[1]];
		}
	}
}


void multiply_matrix(double mat1[], double mat2[], double mat_out[], 
		int size_mat1[], int size_mat2[])   
{                                                                               
	if (size_mat1[1] != size_mat2[0])
	{
		printf("multiply_matrix : Can't multiply matrix with these dimension\n");
	}

	else
	{
		size_t i,j,k;                                                                
		double sum;

		for(i = 0; i <  size_mat1[0]; ++i)                                              
		{                                                                            
			for(j = 0; j < size_mat2[1]; ++j)                                            
			{ 
				sum = 0;                                                        

				for (k = 0; k < size_mat1[1]; k++)                                        
				{                                                                      
					sum = sum + mat1[i * size_mat1[1] + k] * mat2[k * size_mat2[1] + j];      
				}             
				mat_out[i * size_mat2[1] + j] = sum;              
			}                              
		}                                                                            
	}
}

void sum_matrix(double mat1[], double mat2[], int size)
{
	for (int index = 0; index < size; index++)
	{
		mat1[index] += mat2[index];
	}
}

void sub_matrix(double mat1[], double mat2[], int size)
{
	for (int index = 0; index < size; index++)
	{
		mat1[index] -= mat2[index];
	}
}

double sigmoid(double z)
{
	return (double)(1.0 / (1.0 + exp(-z)));
}
void apply_sigmoid_to_matrix(double mat1[], int size)
{
	for (int index = 0; index < size; index++)
	{
		mat1[index] = sigmoid(mat1[index]);
	}
}

double sigmoid_prime(double z)
{
	return z * (1 - z);
}

void hadamard_product(double mat1[], mat2[], int size_mat1[], int size_mat2[])
{
	if (size_mat1[0] != size_mat2[0] && size_mat1[1] != size_mat2[1])
	{
		printf("Hadamard_product : Please provide matrix of the same size");
	}

	else
	{
		int size = size_mat1[0] * size_mat1[1];
		for (int index = 0; index < size ; i++)
		{
			mat1[i] *= mat2[i];
		}
	}
}

