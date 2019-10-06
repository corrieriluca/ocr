#include <stdio.h>
#include "neuralxor.h"
#include "math_tools.h"


int main()
{
	//for a XOR with a hidden layer of 3 neurons
	double input[] = {0,1};
	double weight1[2*3];
	double weight2[3*1];
	init_matrix_random(weight1, 2, 3);
	init_matrix_random(weight2, 2, 3);




	//multiply_matrix(mat1,mat2,output,2,2,2,2);
	//init_matrix_random(input, 2, 2);
	
	return 0;
}

double feedforward(double *input, double *weight1)
{
	double outputf[] = {0,0,0};

	multiply_matrix(input, weight1, outputf, 1, 1, 2, 3);
	//sigmoid(outputf);

	return *outputf;
}



void printf_array(double *a)
{
	size_t n = sizeof(a)/sizeof(a[0]);

	for (size_t i = 0; i < n; ++i)
	{
			 printf("%lf\n", a[i]);
	}
}




