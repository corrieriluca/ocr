#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neuralxor.h"
#include "math_tools.h"
#include "print.h"
#include "init.h"

int main(int argc, char **argv)
{
	if (argc == 1)
	{
	printf("%s",argv[1]);
	pretty_print_xor(25, "NEURAL XOR");
	pretty_print_xor(50, "NEURAL XOR");
	pretty_print_xor(100, "NEURAL XOR");

	//Seed for the random
	srand(time(NULL));

	//Choosing the number of input neurons
	int nb_input_neurons = 2;

	//Choosing the number of neurons in the hidden layer
	int nb_hidden_layer_neurons = 20;

	//Choosing the number of output neurons
	int nb_output_neurons = 1;

	//Choosing the number of epoch
	int nb_epoch = 1000000;


	//Init all the weights, biais and activation point
	//-------------------------------------------------------------------------
	int size_a0[] = {nb_input_neurons,1};
	double a0[size_a0[0] * size_a0[1]];

	int size_a1[] = {nb_hidden_layer_neurons,1};
	double a1[size_a1[0] * size_a1[1]];

	int size_a2[] = {nb_output_neurons,1};
	double a2[size_a2[0] * size_a1[1]];

	int size_w0[] = {nb_hidden_layer_neurons,nb_input_neurons};
	double weight0[size_w0[0] * size_w0[1]];
	init_matrix_random(weight0, size_w0);

	int size_w1[] = {nb_output_neurons,nb_hidden_layer_neurons};
	double weight1[size_w1[0] * size_w1[1]];
	init_matrix_random(weight1, size_w1);

	int size_b0[] = {nb_hidden_layer_neurons,1};
	double b0[size_b0[0] * size_b0[1]];
	init_matrix_random(b0, size_b0);

	int size_b1[] = {nb_output_neurons,1};
	double b1[size_b1[0] * size_b1[1]];
	init_matrix_random(b1, size_b1);


	//Test neural Xor with the random value for the weight and biais
	//-------------------------------------------------------------------------
	printf("\nOutputs with random weights and biais...\n");
	print_feed_forward(weight0, weight1, a0, a1, a2, b0, b1, size_w0, size_w1,
			size_a0, size_a1, size_a2, size_b0, size_b1);


	printf("\n\nBeginning learning process...\n");

	//Init matrix for epoch
	int s_d_b1[] = {nb_output_neurons, 1};
	double d_b1[s_d_b1[0] * s_d_b1[1]];

	int s_d_w1[] = {nb_output_neurons, nb_hidden_layer_neurons};
	double d_w1[s_d_w1[0] * s_d_w1[1]];

	int s_d_b0[] = {nb_hidden_layer_neurons, 1};
	double d_b0[s_d_b0[0] * s_d_b0[1]];

	int s_d_w0[] = {nb_hidden_layer_neurons, nb_input_neurons};
	double d_w0[s_d_w0[0] * s_d_w0[1]];

	for (int k = 0; k < nb_epoch; k++)
	{
		//Reset the matrix to 0
		init_matrix_with_0(d_b1, s_d_b1);

		init_matrix_with_0(d_w1, s_d_w1);

		init_matrix_with_0(d_b0, s_d_b0);

		init_matrix_with_0(d_w0, s_d_w0);

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


	//Print the output of the neural Xor after training
	printf("\n\nAfter learning process...\n");
	print_feed_forward(weight0, weight1, a0, a1, a2, b0, b1, size_w0, size_w1, 
			size_a0, size_a1, size_a2, size_b0, size_b1);
	}
}
