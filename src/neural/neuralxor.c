#include <stdio.h>
#include "neuralxor.h"
#include "math_tools.h"

void printf_array(double *a)
{
	size_t n = sizeof(a)/sizeof(a[0]);

	for (size_t i = 0; i < n; ++i)
	{
			 printf("a[%u] = %lf\n",i, a[i]);
	}
}

void feedforward(double *weight0, double *weight1, double *a0, double *a1, 
		double *a2, double *b0, double *b1, int *size_w0, int *size_w1, int *size_a0, 
		int *size_a1, int *size_a2, int *size_b0, int *size_b1)
{

	double w0_t[size_w0[0]*size_w0[1]];
	int size_w0_t[2] = {size_w0[1], size_w0[0]};
	transpose_matrix(weight0, w0_t, size_w0, size_w0_t );

	multiply_matrix(w0_t, a0, a1, size_w0_t, size_a0);
	add_matrix(a1, b0, size_a1, size_b0);
	apply_sigmoid_to_matrix(a1, size_a1[0]);

	//------------------------------------------------
	
	double w1_t[size_w1[0]*size_w1[1]];
	int size_w1_t[2] = {size_w1[1], size_w1[0]};
	transpose_matrix(weight1, w1_t, size_w1, size_w1_t );
	
	multiply_matrix(w1_t, a1, a2, size_w1_t, size_a1);
	add_matrix(a2, b1, size_a2, size_b1);
	apply_sigmoid_to_matrix(a2, size_a2[0]);
}

void backpropagation(double *weight0, double *weight1, double *a0, double *a1, 
		double *a2, double *b0, double *b1, int *size_w0, int *size_w1, int *size_a0, 
		int *size_a1, int *size_a2, int *size_b0, int *size_b1)
{
	double wanted_output[1] = {0};  //TODO : Need a way to convert a0[0] ^ a0[1]
	int size_wanted_output[] = {1,1};

	double error[1] = {-42}; //Must put a value. Otherwise Undeclared for subtract
	int size_error[] = {1,1};

	subtract_matrix(a2, wanted_output, error, size_a2, size_wanted_output);

	// -----------------------------------------------
	
	double D[1] = {sigmoid_prime(a2[0])};
	int size_D[] = {1,1};

	hadamard_product(error, D, size_error, size_D);

}




int main()
{
	printf("#########################################\n");
	printf("###            NEURAL XOR             ###\n");
	printf("#########################################\n");

	//for a XOR with a hidden layer of 3 neurons
	double a0[2];
	int size_a0[] = {2,1};

	double a1[3];
	int size_a1[] = {3,1};

	double a2[1];
	int size_a2[] = {1,1};

	double weight0[6] = {1.5,2.0,-1.5,-1.8,0.1,0.7};
	int size_w0[] = {2,3};
	
	double weight1[3] = {0.5, -1.8, 1.2};
	int size_w1[] = {3,1};

	double b0[3] = {-2.0,1.0,-0.1};
	int size_b0[] = {3,1}; 

	double b1[1] = {-0.1};
	int size_b1[] = {1,1}; 
	

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
	for (size_t k = 0; k < 1; k++)
	{
		for (double i = 0; i < 2; i++)
		{
			for (double j = 0; j < 2; j++)
			{
				a0[0] = i;
				a0[1] = j;
				feedforward(weight0, weight1, a0, a1, a2, b0, b1, 
						size_w0, size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);


				backpropagation(weight0, weight1, a0, a1, a2, b0, b1, 
						size_w0, size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);



			}
		}
	}


	printf("\n\nAfter learning process...\n");
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
