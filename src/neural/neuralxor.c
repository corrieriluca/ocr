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
        printf("-");
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
        printf("-");
    printf("*\n");
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
	apply_sigmoid_to_matrix(a1, size_a1);

	//------------------------------------------------
	
	double w1_t[size_w1[0]*size_w1[1]];
	int size_w1_t[2] = {size_w1[1], size_w1[0]};
	transpose_matrix(weight1, w1_t, size_w1, size_w1_t );
	
	multiply_matrix(w1_t, a1, a2, size_w1_t, size_a1);
	add_matrix(a2, b1, size_a2, size_b1);
	apply_sigmoid_to_matrix(a2, size_a2);
}





void backpropagation(double *weight0, double *weight1, double *a0, double *a1, 
		double *a2, double *b0, double *b1, int *size_w0, int *size_w1, int *size_a0, 
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

	// -----------------------------------------------

	double sigmoid_prime_output[1];
	int size_spo[] = {1,1};

	apply_sigmoid_prime_to_matrix(a2, sigmoid_prime_output, size_a2, size_spo);

	double D[1]; 
	int size_D[] = {1,1};

	hadamard_product(error, sigmoid_prime_output, D, size_error, size_spo);

	//Beginning boucle
	//------------------------------------------------------------------

	double nu = -0.1;

	double delta_b1[1];
	int size_delta_b1[] = {1,1};


	double delta_w1[1];
	int size_delta_w1[] = {1,1};

	multiply_matrix_by_constant(D, nu, delta_b1, size_D, size_delta_b1);

	//--------------------------------------------------------

	double a1_t[3];
	int size_a1_t[] = {size_a1[1], size_a1[0]};

	transpose_matrix(a1, a1_t, size_a1, size_a1_t);

	multiply_matrix_by_constant(D, nu, delta_w1, size_D, size_delta_w1);

	multiply_matrix(delta_w1, a1_t, a1_t, size_delta_w1, size_a1_t);

	double a1_tt[3];
	int size_a1_tt[] = {size_a1_t[1], size_a1_t[0]};



	//--------------------------------------------------------
	//Update D :
	//--------------------------------------------------------

	double D2[3];
	int size_D2[] = {3,1};

	double tmp[3];
	int size_tmp[] = {size_w1[0], size_w1[1]};

	multiply_matrix(weight1, D, tmp, size_w1, size_D);

	//
	double sigmoid_prime_output2[3];
	int size_spo2[] = {3,1};

	apply_sigmoid_prime_to_matrix(a1, sigmoid_prime_output2, size_a1, size_spo2);

	hadamard_product(tmp, sigmoid_prime_output2, D2, size_tmp, size_spo2);

	//HIDDEN LAYER TO INPUT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	double delta_w0[6];
	int size_delta_w0[] = {2,3};

	double delta_b0[3];
	int size_delta_b0[] = {3,1};

	multiply_matrix_by_constant(D2, nu, delta_b0, size_D2, size_delta_b0);

	//--------------------------------------------------------

	double a0_t[2];
	int size_a0_t[] = {size_a0[1], size_a0[0]};

	transpose_matrix(a0, a0_t, size_a0, size_a0_t);
	
	double tmp3[3];
	int size_tmp3[] = {3,1};

	multiply_matrix_by_constant(D2, nu, tmp3, size_D2, size_tmp3);

	multiply_matrix(tmp3, a0_t, delta_w0, size_tmp3, size_a0_t);

	double a0_tt[3];
	int size_a0_tt[] = {size_a0_t[1], size_a0_t[0]};

//----------------------------------------------------------------------------

	add_matrix(d_b1, delta_b1, s_d_b1, size_delta_b1);
	add_matrix(d_w1, a1_tt, s_d_w1, size_a1_tt);
	add_matrix(d_b0, delta_b0, s_d_b0, size_delta_b0);
	add_matrix(d_w0, a0_tt, s_d_w0, size_a0_tt);
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

	//55double weight0[6] = {1.5,2.0,-1.5,-1.8,0.1,0.7};
	srand(time(NULL));
	double weight0[6];
	for (size_t i = 0; i < 6; i++)
	{
		weight0[i] =((((double) rand()) / (double) RAND_MAX) * (2 + 2) - 2) / 1;
	}
	int size_w0[] = {2,3};
	print_matrix_double(weight0, size_w0);
	
	//double weight1[3] = {0.5, -1.8, 1.2};
	double weight1[3];
	for (size_t i = 0; i < 3; i++)
	{
		weight1[i] = ((((double) rand()) / (double) RAND_MAX) * (2 + 2) - 2) / 1;
	}
	int size_w1[] = {3,1};
	print_matrix_double(weight1, size_w1);

	//double b0[3] = {-2.0,1.0,-0.1};
	double b0[3];
	for (size_t i = 0; i < 3; i++)
	{
		b0[i] = (((double) rand()) / (double) RAND_MAX) * (2 + 2) - 2;
	}
	int size_b0[] = {3,1}; 

	double b1[1];
	b1[0] = (((double) rand()) / (double) RAND_MAX) * (2 + 2) - 2;
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

	print_matrix_double(weight0, size_w0);

	printf("\n\nBeginning learning process...\n");


	for (size_t k = 0; k < 1000; k++)
	{
		double d_b1[1] = {0};
		int s_d_b1[] = {1,1};
		double d_w1[3] = {0,0,0};
		int s_d_w1[] = {3,1};
		double d_b0[3] = {0,0,0};
		int s_d_b0[] = {3,1};
		double d_w0[6] = {0,0,0,0,0,0};
		int s_d_w0[] = {2,3};

		for (double i = 0; i < 2; i++)
		{
			for (double j = 0; j < 2; j++)
			{
				a0[0] = i;
				a0[1] = j;

				//a0[0] = (((double)rand()) / (double)RAND_MAX) < 0.5;
				//a0[1] = (((double)rand()) / (double)RAND_MAX) < 0.5;
				//printf("%lf %lf\n\n", a0[0], a0[1]);
				
				feedforward(weight0, weight1, a0, a1, a2, b0, b1, 
						size_w0, size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);


				backpropagation(weight0, weight1, a0, a1, a2, b0, b1, 
						size_w0, size_w1, size_a0, size_a1, size_a2, size_b0, size_b1,
						d_b1, d_w1, d_b0, d_w0, s_d_b1, s_d_w1, s_d_b0, s_d_w0);

				//print_matrix_double(weight1, size_w0);
			}
		}

		add_matrix(b1, d_b1, size_b1, s_d_b1);
		add_matrix(weight1, d_w1, size_w1, s_d_w1);
		add_matrix(b0, d_b0, size_b0, s_d_b0);
		add_matrix(weight0, d_w0, size_w0, s_d_w0);
		print_matrix_double(d_w0, s_d_w0);
	}

	print_matrix_double(weight0, size_w0);

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
