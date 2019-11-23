#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h> //For atoi
#include <err.h>
#include "neural.h"
#include "math_tools.h"
#include "print.h"
#include "init.h"
#include "matrix_save.h"

int main(int argc, char **argv)
{
	printf("%s\n",argv[0]);
	pretty_print_xor(40, "NEURAL");

	//Seed for the random
	srand(time(NULL));

	//Choosing the number of input neurons
	int nb_input_neurons = 28*28;

	//Choosing the number of output neurons
	int nb_output_neurons = 67;

	//Choosing the number of neurons in the hidden layer
	int nb_hidden_layer_neurons;

	//Choosing the number of epoch
	int nb_epoch;

	if (argc == 3)
	{
		sscanf(argv[1], "%d", &nb_hidden_layer_neurons);
		sscanf(argv[2], "%d", &nb_epoch);
	}
	else
	{
		nb_hidden_layer_neurons = 350;
		nb_epoch = 3112;
	}

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

	int size_w1[] = {nb_output_neurons,nb_hidden_layer_neurons};
	double weight1[size_w1[0] * size_w1[1]];

	int size_b0[] = {nb_hidden_layer_neurons,1};
	double b0[size_b0[0] * size_b0[1]];

	int size_b1[] = {nb_output_neurons,1};
	double b1[size_b1[0] * size_b1[1]];

	init_matrix_random(weight0, size_w0);
	init_matrix_random(weight1, size_w1);
	init_matrix_with_0(b0, size_b0);
	init_matrix_with_0(b1, size_b1);
	//init_matrix_random(b0, size_b0);
	//init_matrix_random(b1, size_b1);


	//###########################################################
	print_feed_forward(weight0, weight1, a0, a1, a2, b0, b1, size_w0,
			size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);


	//TODO : Test the neural with randow init

	//#########################################################################


	//TODO : Verify that mat_to_file work
	mat_to_file(size_w0, size_w1, size_b0, size_b1,
			weight0, weight1, b0, b1, "test.ocr");

	printf("\nBeginning learning process...\n");

	//Init matrix for epoch
	int s_d_b1[] = {nb_output_neurons, 1};
	double d_b1[s_d_b1[0] * s_d_b1[1]];

	int s_d_w1[] = {nb_output_neurons, nb_hidden_layer_neurons};
	double d_w1[s_d_w1[0] * s_d_w1[1]];

	int s_d_b0[] = {nb_hidden_layer_neurons, 1};
	double d_b0[s_d_b0[0] * s_d_b0[1]];

	int s_d_w0[] = {nb_hidden_layer_neurons, nb_input_neurons};
	double d_w0[s_d_w0[0] * s_d_w0[1]];


	//Path to database
	char path_matrix[] = "../learning/matrix_database.ocr";
	char path_char[] = "../learning/character_database.ocr";

	//Expected char for a given matrix
	char good_char;

	FILE *matrix_db;
	matrix_db = fopen(path_matrix, "r");

	FILE *char_db;
	char_db = fopen(path_char, "r");

	if (matrix_db == NULL || char_db == NULL)
	{
		errx(1, "Could not acces database");
	}

	int a = 0;
	printf("Breakpoint : %d\n", a);
	a++;
	for (int k = 0; k < nb_epoch; k++)
	{
		//printf("\nBegin epoch %d/%d\n", k+1, nb_epoch);


		//Reset the matrix to 0
		init_matrix_with_0(d_b1, s_d_b1);
		init_matrix_with_0(d_w1, s_d_w1);
		init_matrix_with_0(d_b0, s_d_b0);
		init_matrix_with_0(d_w0, s_d_w0);

		//Start the learning phase
		//----------------------------------------------------------------------
		for (int i = 0; i < 1; i++)
		{
			init_a0(a0, size_a0, &good_char, matrix_db, char_db);


			feedforward(weight0, weight1, a0, a1, a2, b0, b1, size_w0,
					size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);

	printf("Breakpoint : %d\n", a);
	a++;
			backpropagation(weight1, a0, a1, a2, size_w0, size_w1, size_a0,
					size_a1, size_a2, size_b0, size_b1, d_b1, d_w1, d_b0, d_w0,
					s_d_b1, s_d_w1, s_d_b0, s_d_w0, &good_char);
	printf("Breakpoint : %d\n", a);
	a++;
		}

		//End of epoch
		add_matrix(b1, d_b1, size_b1, s_d_b1);
		add_matrix(weight1, d_w1, size_w1, s_d_w1);
		add_matrix(b0, d_b0, size_b0, s_d_b0);
		add_matrix(weight0, d_w0, size_w0, s_d_w0);
	}

	fclose(matrix_db);
	fclose(char_db);

	mat_to_file(size_w0, size_w1, size_b0, size_b1,
			weight0, weight1, b0, b1, "test2.ocr");


	//Print the output of the neural Xor after training
	printf("\n\nAfter learning process...\n");
	//TODO : Check it the network work
	//

	print_feed_forward(weight0, weight1, a0, a1, a2, b0, b1, size_w0,
			size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);

	print_matrix_double(a2, size_a2);
}
