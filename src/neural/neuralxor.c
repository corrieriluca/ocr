#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neuralxor.h"
#include "math_tools.h"

void print_matrix_double(double matrix[], int size[])
{
	int width = size[1];
	int height = size[0];

	printf("*");
	for (int i = 0; i < width; i++)
	{
	  printf("-");
	}
	printf("*\n");

	for (int j = 0; j < height; j++)
	{
	  printf("|");
	  for (int k = 0; k < width; k++)
	  {
		  printf("%f ", matrix[k + j * width]);
	  }
	  printf("|\n");
	}

	printf("*");
	for (int l = 0; l < width; l++)
	{
	  printf("-");
	}
	printf("*\n");
}


void feedforward(double *weight0, double *weight1, double *a0, double *a1,
		double *a2, double *b0, double *b1, int *size_w0, int *size_w1,
		int *size_a0, int *size_a1, int *size_a2, int *size_b0, int *size_b1)
{
	multiply_matrix(weight0, a0, a1, size_w0, size_a0);
	add_matrix(a1, b0, size_a1, size_b0);
	apply_sigmoid_to_matrix(a1, size_a1);

	//------------------------------------------------

	multiply_matrix(weight1, a1, a2, size_w1, size_a1);
	add_matrix(a2, b1, size_a2, size_b1);
	apply_sigmoid_to_matrix(a2, size_a2);
}


void backpropagation(double *weight1, double *a0, double *a1,
		double *a2, int *size_w0, int *size_w1, int *size_a0,
		int *size_a1, int size_a2[], int *size_b0, int *size_b1,
		double *d_b1, double *d_w1, double *d_b0, double *d_w0,
		int *s_d_b1, int *s_d_w1, int *s_d_b0, int *s_d_w0)
{
	double wanted_output[1];
	//TODO : Need a way to convert a0[0] ^ a0[1]
	if ((a0[0] == 0.0 && a0[1] == 0.0) || (a0[0] == 1.0 && a0[1] == 1.0))
	{
		wanted_output[0] = 0.0;
	}
	else
	{
		wanted_output[0] = 1.0;
	}
	int size_wanted_output[] = {1,1};


	double error[1];
	int size_error[] = {1,1};

	subtract_matrix(a2, wanted_output, error, size_a2, size_wanted_output);

	// ------------------------------------------------------------------------

	double sigmoid_prime_output[1];
	int size_spo[] = {1,1};

	apply_sigmoid_prime_to_matrix(a2, sigmoid_prime_output, size_a2, size_spo);

	double D[1];
	int size_D[] = {1,1};

	hadamard_product(error, sigmoid_prime_output, D, size_error, size_spo);

	//-------------------------------------------------------------------------
	//Output to hidden layer
	//-------------------------------------------------------------------------

	double nu = -0.1;

	double tmp1[size_D[0] * size_D[1]];
	int s_tmp1[] = {size_D[0], size_D[1]};

	double a1_t[size_a1[0] * size_a1[1]];
	int size_a1_t[] = {size_a1[1], size_a1[0]};

	double delta_b1[size_b1[0] * size_b1[1]];
	int size_delta_b1[] = {size_b1[0], size_b1[1]};

	double delta_w1[size_w1[0] * size_w1[1]];
	int size_delta_w1[] = {size_w1[0], size_w1[1]};

	//Transpose the matrix of a1
	transpose_matrix(a1, a1_t, size_a1, size_a1_t);

	//Calculate -nu * D
	multiply_matrix_by_constant(D, nu, tmp1, size_D, s_tmp1);

	//Update Delta B1
	add_matrix(delta_b1, tmp1, size_delta_b1, s_tmp1);

	//Update Delta W1
	multiply_matrix(tmp1, a1_t, delta_w1, s_tmp1, size_a1_t);


	//-------------------------------------------------------------------------
	//Update D
	//-------------------------------------------------------------------------

	double D2[size_a1[0] * size_a1[1]];
	int size_D2[] = {size_a1[0], size_a1[1]};

	double tmp2[size_w1[1] * size_w1[0]];
	int s_tmp2[] = {size_w1[1], size_w1[0]};

	double sigmoid_prime_output2[size_a1[0] * size_a1[1]];
	int size_spo2[] = {size_a1[0], size_a1[1]};

	double w1_t[size_w1[0] * size_w1[1]];
	int s_w1_t[] = {size_w1[1], size_w1[0]};

	transpose_matrix(weight1, w1_t, size_w1, s_w1_t);

	multiply_matrix(w1_t, D, tmp2, s_w1_t, size_D);

	apply_sigmoid_prime_to_matrix(a1, sigmoid_prime_output2, size_a1, size_spo2);

	hadamard_product(tmp2, sigmoid_prime_output2, D2, s_tmp2, size_spo2);

	//-------------------------------------------------------------------------
	//Hidden layer to input
	//-------------------------------------------------------------------------

	double tmp3[size_D2[0] * size_D2[1]];
	int s_tmp3[] = {size_D2[0], size_D2[1]};

	double a0_t[size_a0[0] * size_a0[1]];
	int size_a0_t[] = {size_a0[1], size_a0[0]};

	double delta_b0[size_b0[0] * size_b0[1]];
	int size_delta_b0[] = {size_b0[0], size_b0[1]};

	double delta_w0[size_w0[0] * size_w0[1]];
	int size_delta_w0[] = {size_w0[0], size_w0[1]};

	//Transpose the matrix of a0
	transpose_matrix(a0, a0_t, size_a0, size_a0_t);

	//Calculate -nu * D2
	multiply_matrix_by_constant(D2, nu, tmp3, size_D2, s_tmp3);

	//Update Delta B0
	add_matrix(delta_b0, tmp3, size_delta_b0, s_tmp3);

	//Update Delta W0
	multiply_matrix(tmp3, a0_t, delta_w0, s_tmp3, size_a0_t);

	//-------------------------------------------------------------------------
	//End of backpropagation
	//-------------------------------------------------------------------------

	add_matrix(d_b1, delta_b1, s_d_b1, size_delta_b1);
	add_matrix(d_w1, delta_w1, s_d_w1, size_delta_w1);
	add_matrix(d_b0, delta_b0, s_d_b0, size_delta_b0);
	add_matrix(d_w0, delta_w0, s_d_w0, size_delta_w0);
}



int main()
{
	//For a XOR with a hidden layer of 20 neurons
	printf("#########################################\n");
	printf("###            NEURAL XOR             ###\n");
	printf("#########################################\n");

	srand(time(NULL));

	//Init all the weights, biais and activation point
	int size_a0[] = {2,1};
	double a0[size_a0[0] * size_a0[1]];

	int size_a1[] = {20,1};
	double a1[size_a1[0] * size_a1[1]];

	int size_a2[] = {1,1};
	double a2[size_a2[0] * size_a1[1]];

	//-------------------------------------------------------------------------
	int i;

	int size_w0[] = {20,2};
	double weight0[size_w0[0] * size_w0[1]];
	for (i = 0; i < size_w0[0] * size_w0[1]; i++)
	{
		weight0[i] =(((double) rand()) / (double) RAND_MAX) * (2 + 2) - 2;
	}

	int size_w1[] = {1,20};
	double weight1[size_w1[0] * size_w1[1]];
	for (i = 0; i < size_w1[0] * size_w1[1]; i++)
	{
		weight1[i] = (((double) rand()) / (double) RAND_MAX) * (2 + 2) - 2;
	}

	//-------------------------------------------------------------------------
	int size_b0[] = {20,1};
	double b0[size_b0[0] * size_b0[1]];
	for (i = 0; i < size_b0[0] * size_b0[1]; i++)
	{
		b0[i] = (((double) rand()) / (double) RAND_MAX) * (2 + 2) - 2;
	}

	int size_b1[] = {1,1};
	double b1[size_b1[0] * size_b1[1]];
	for (i = 0; i < size_b1[0] * size_b1[1]; i++)
	{
		b1[i] = (((double) rand()) / (double) RAND_MAX) * (2 + 2) - 2;
	}


	//Test neural Xor with the random value for the weight and biais
	//-------------------------------------------------------------------------
	printf("\nOutputs with random weights and biais...\n");
	for (double i = 0; i < 2; i++)
	{
		for (double j = 0; j < 2; j++)
		{
			a0[0] = i;
			a0[1] = j;
			feedforward(weight0, weight1, a0, a1, a2, b0, b1,
					size_w0, size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);
			printf("Inputs: %lf %lf -> %lf\n", a0[0], a0[1], a2[0]);
		}
	}


	printf("\n\nBeginning learning process...\n");

	for (size_t k = 0; k < 1000000; k++)
	{
		//Init matrix for epoch
		//----------------------------------------------------------------------
		int s_d_b1[] = {1,1};
		double d_b1[s_d_b1[0] * s_d_b1[1]];
		for (i = 0; i < s_d_b1[0] * s_d_b1[1]; i++)
		{
			d_b1[i] = 0;
		}

		int s_d_w1[] = {1,20};
		double d_w1[s_d_w1[0] * s_d_w1[1]];
		for (i = 0; i < s_d_w1[0] * s_d_w1[1]; i++)
		{
			d_w1[i] = 0;
		}

		int s_d_b0[] = {20,1};
		double d_b0[s_d_b0[0] * s_d_b0[1]];
		for (i = 0; i < s_d_b0[0] * s_d_b0[1]; i++)
		{
			d_b0[i] = 0;
		}

		int s_d_w0[] = {20,2};
		double d_w0[s_d_w0[0] * s_d_w0[1]];
		for (i = 0; i < s_d_w0[0] * s_d_w0[1]; i++)
		{
			d_w0[i] = 0;
		}

		//Start the learning phase
		//----------------------------------------------------------------------
		for (double i = 0; i < 2; i++)
		{
			for (double j = 0; j < 2; j++)
			{
				a0[0] = i;
				a0[1] = j;

				feedforward(weight0, weight1, a0, a1, a2, b0, b1, size_w0,
						size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);

				backpropagation(weight1, a0, a1, a2, size_w0, size_w1, size_a0,
						size_a1, size_a2, size_b0, size_b1, d_b1, d_w1, d_b0, d_w0,
						s_d_b1, s_d_w1, s_d_b0, s_d_w0);
			}
		}

		//End of epoch
		add_matrix(b1, d_b1, size_b1, s_d_b1);
		add_matrix(weight1, d_w1, size_w1, s_d_w1);
		add_matrix(b0, d_b0, size_b0, s_d_b0);
		add_matrix(weight0, d_w0, size_w0, s_d_w0);
	}


	printf("\n\nAfter learning process...\n");
	//Print the output of the neural Xor after training
	for (double i = 0; i < 2; i++)
	{
		for (double j = 0; j < 2; j++)
		{
			a0[0] = i;
			a0[1] = j;
			feedforward(weight0, weight1, a0, a1, a2, b0, b1,
					size_w0, size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);
			printf("Inputs: %lf %lf -> %lf\n", a0[0], a0[1], a2[0]);
		}
	}
}
