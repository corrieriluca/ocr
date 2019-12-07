#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neural.h"
#include "math_tools.h"
#include "print.h"
#include "save_and_load.h"

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
	apply_softmax_to_matrix(a2, size_a2);
}


