#include <stdio.h>
#include "neuralxor.h"
#include "math_tools.h"

void printf_array(double *a)
{
	size_t n = sizeof(a)/sizeof(a[0]);

	for (size_t i = 0; i < n; ++i)
	{
			 printf("%lf\n", a[i]);
	}
}


void feedforward(double *weight0, double *weight1, double *a0, double *a1, 
		double *a2, double *b0, double *b1, int *size_w0, int *size_w1, int *size_a0, 
		int *size_a1, int *size_a2)
{

	double w0_t[size_w0[0]*size_w0[1]];
	int size_w0_t[2] = {size_w0[1], size_w0[0]};
	transpose_matrix(weight0, w0_t, size_w0, size_w0_t );

	multiply_matrix(w0_t, a0, a1, size_w0_t, size_a0);
	sum_matrix(a1, b0, size_a1[0]);
	apply_sigmoid_to_matrix(a1, size_a1[0]);

	//------------------------------------------------
	
	double w1_t[size_w1[0]*size_w1[1]];
	int size_w1_t[2] = {size_w1[1], size_w1[0]};
	transpose_matrix(weight1, w1_t, size_w1, size_w1_t );
	
	multiply_matrix(w1_t, a1, a2, size_w1_t, size_a1);
	sum_matrix(a2, b1, size_a2[0]);
	apply_sigmoid_to_matrix(a2, size_a2[0]);

	printf("With %lf and %lf the output is : %lf\n", a0[0], a0[1], a2[0]);
}

int main()
{
	//for a XOR with a hidden layer of 3 neurons
	double a0[] = {0,1};
	int size_a0[] = {2,1};

	double a1[] = {-42,-42,-42};
	int size_a1[] = {3,1};

	double a2[] = {0};
	int size_a2[] = {1,1};

	double weight0[6] = {1.5,2.0,-1.5,-1.8,0.1,0.7};
	int size_w0[] = {2,3};
	
	double weight1[3] = {0.5, -1.8, 1.2};
	int size_w1[] = {3,1};

	double b0[3] = {-2.0,1.0,-0.1};
	int size_b0[] = {3,1}; //Not use for now

	double b1[1] = {-0.1};
	int size_b1[] = {1,1}; //Not use for now
	
	feedforward(weight0, weight1, a0, a1, a2, b0, b1, 
			size_w0, size_w1, size_a0, size_a1, size_a2);
}





