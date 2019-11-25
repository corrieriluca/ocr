#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int index_max_matrix(double mat[], int size[])
{
	int index_max = 0;
	for (int i = 0; i < (size[0] * size[1]); i++)
	{
		if (mat[index_max] < mat[i])
		{
			index_max = i;
		}
	}

	return index_max;
}

double cost_function(double mat1[], double mat2[],
		int size1[], int size2[])
{
	double sum = 0.0;

	if ((size1[0] != size2[0]) || (size1[1] != size2[1]))
	{
		printf("cost_function: ");
		printf("Can't compute cost function  with those dimension\n");
	}
	else
	{
		for (int i = 0; i < (size1[0] * size1[1]); i++)
		{
			sum += pow((mat1[i] - mat2[i]), 2);
		}
	}

	return sum;
}





void transpose_matrix(double mat1[], double mat1_t[],
		int size_mat1[], int size_mat1_t[])
{
	if ((size_mat1[0] != size_mat1_t[1]) || (size_mat1[1] != size_mat1_t[0]))
	{
		printf("transpose_matrix: ");
		printf("Can't transpose matrix with those dimension\n");
	}
	else
	{
		for (int i = 0; i < size_mat1[1]; i++)
		{
			for (int j = 0; j < size_mat1[0]; j++)
			{
				mat1_t[j + i * size_mat1[0]] = mat1[i + j * size_mat1[1]];
			}
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
		int i,j,k;
		double sum;

		for(i = 0; i <  size_mat1[0]; ++i)
		{
			for(j = 0; j < size_mat2[1]; ++j)
			{
				sum = 0;

				for (k = 0; k < size_mat1[1]; k++)
				{
					sum += mat1[i * size_mat1[1] + k] * mat2[k * size_mat2[1] + j];
				}
				mat_out[i * size_mat2[1] + j] = sum;
			}
		}
	}
}


void add_matrix(double mat1[], double mat2[], int size_mat1[], int size_mat2[])
{
	if (size_mat1[0] != size_mat2[0] && size_mat1[1] != size_mat2[1])
	{
		printf("add_matrix : Please provide matrix of the same size\n");
	}
	else
	{
		int size = size_mat1[0] * size_mat1[1];

		for (int index = 0; index < size; index++)
		{
			mat1[index] += mat2[index];
		}
	}
}


void subtract_matrix(double mat1[], double mat2[], double mat_out[],
		int size_mat1[], int size_mat2[])
{
	if (size_mat1[0] != size_mat2[0] && size_mat1[1] != size_mat2[1])
	{
		printf("subtract_matrix : Please provide matrix of the same size\n");
	}

	else
	{
		int size = size_mat1[0] * size_mat1[1];

		for (int index = 0; index < size; index++)
		{
			mat_out[index] = mat1[index] - mat2[index];
		}
	}
}


double sigmoid(double z)
{
	return (double)(1.0 / (1.0 + exp(-z)));
}


void apply_sigmoid_to_matrix(double mat[], int size[])
{
	for (int index = 0; index < size[0] * size[1]; index++)
	{
		mat[index] = sigmoid(mat[index]);
	}
}


double sigmoid_prime(double z)
{
	return z * (1 - z);
}


void apply_sigmoid_prime_to_matrix(double mat1[], double mat_out[],
		int size_mat1[], int size_mat_out[])
{
	if (size_mat1[0] != size_mat_out[0] || size_mat1[1] != size_mat_out[1])
	{
		printf("apply_signoid_prime_to_matrix: ");
		printf("Please provide matrix of the same size\n");
	}
	else
	{
		int size = size_mat1[0] * size_mat1[1];

		for (int index = 0; index < size; index++)
		{
			mat_out[index] = sigmoid_prime(mat1[index]);
		}
	}
}


void hadamard_product(double mat1[],double mat2[], double mat_out[],
		int size_mat1[], int size_mat2[])
{
	if (size_mat1[0] != size_mat2[0] || size_mat1[1] != size_mat2[1])
	{
		printf("Hadamard_product : Please provide matrix of the same size\n");
	}
	else
	{
		int size = size_mat1[0] * size_mat1[1];

		for (int index = 0; index < size ; index++)
		{
			mat_out[index] = mat1[index] * mat2[index];
		}
	}
}


void multiply_matrix_by_constant(double mat1[], double c, double mat_out[],
		int size_mat1[], int size_mat_out[])
{
	if (size_mat1[0] != size_mat_out[0] || size_mat1[1] != size_mat_out[1])
	{
		printf("multiply_matrix_by_constant: ");
		printf("Please provide matrix of the same size\n");
	}
	else
	{
		int size = size_mat1[0] * size_mat1[1];

		for (int index = 0; index < size ; index++)
		{
			mat_out[index] = mat1[index] * c;
		}
	}
}

void apply_softmax_to_matrix(double mat[], int size[])
{
	double sum = 0;

	for (int i = 0; i < (size[0] * size[1]); i++)
	{
		sum += exp(mat[i]);
	}

	for (int i = 0; i < (size[0] * size[1]); i++)
	{
		mat[i] = (exp(mat[i]) / sum);
	}
}
