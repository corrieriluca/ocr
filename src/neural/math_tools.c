#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <err.h>

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
	long double sum = 0;

	for (int i = 0; i < (size[0] * size[1]); i++)
	{
		sum += exp(mat[i]);
	}

	for (int i = 0; i < (size[0] * size[1]); i++)
	{
		if (sum <= 0.0)
		{
			errx(1, "division by 0 in softmax");
		}
		mat[i] = (exp(mat[i]) / sum);
	}
}


void init_a0(double *a0, int *size_a0, char *good_char,
		FILE *matrix_db, FILE *char_db)
{
	//printf("########################################################################\n");
	char charac[3];
	fgets(charac, sizeof(charac), char_db);
	*good_char = charac[0];
	printf("'%c' ", charac[0]);

	char matrix[486]; //TODO : Find good size
	//fgets(matrix, sizeof(matrix), matrix_db);
	fgets(matrix, 486, matrix_db);

	/*printf("%s\n", matrix);

	printf("\n");
	for (int z = 0; z < (256); z++)
	{
		if ((z % 16) == 0 && (z != 0))
		{
			printf("\n");
		}

		if (matrix[z] == '0')
		{
			printf(" ");
		}
		else
		{
			if (matrix[z] == '1')
			{
			printf("O");
			}
			else
			{
				printf("*");
			}
		}
	}
	printf("\n");
*/
	int size = size_a0[0] * size_a0[1];
	for (int i = 0; i < size; i++)
	{
		if (matrix[i] == '0')
		{
			a0[i] = 0.0;
		}
		else
		{
			if (matrix[i] == '1')
			{
				a0[i] = 1.0;
			}
			else
			{
				printf("||**|*||");
			}
		}
	}

	//printf("\n");
	/*
	printf("\n");
	//Ugly but usefull to print a0
	for (int z = 0; z < (size_a0[0] * size_a0[1]); z++)
	{
		if ((z % 16) == 0 && (z != 0))
		{
			printf("\n");
		}

		printf("|%lf|",a0[z]);
	}
	printf("########################################################################\n");*/
}


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



char find_index_letter(double *output_a2, int *size)
{
	char letters[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?'0123456789";
	int index_max = 0;
	for (int i = 0; i < (size[0] * size[1]); i++)
	{
		if (output_a2[index_max] < output_a2[i])
		{
			index_max = i;
		}
	}

	return letters[index_max];
}


int wanted_letter(char *letter)
{
	char letters[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?'0123456789";

	int i = 0;
	int is_found = 0;
	//
	//TODO : Clean the 67 with actual variable nd make a propre loop
	while ((i < 67) && (!is_found))
	{
		if (*letter == letters[i])
		{
			is_found = 1;
			return i;
		}
		i++;
	}

	return i;
}
