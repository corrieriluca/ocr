#include <stdio.h>
#include "backpropagation.h"

double sigmoid(double z)
{
	return (double)(1.0 / (1.0 + exp(-z)));
}

double sigmoid_prime(double z)
{
	return z * (1 - z);
}


//Hadamard product
// Equation for the error in the output layer
//
