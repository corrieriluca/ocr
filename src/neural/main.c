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
	if (argc == 1)
	{
		printf("%s\n",argv[0]);
		pretty_print_xor(40, "NEURAL");

		//Seed for the random
		srand(time(NULL));

		//Choosing the number of input neurons
		int nb_input_neurons = 28*28;

		//Choosing the number of neurons in the hidden layer
		int nb_hidden_layer_neurons = 200;

		//Choosing the number of output neurons
		int nb_output_neurons = 67;

		//Choosing the number of epoch
		int nb_epoch = 1000;

		char path_matrix[] = "../learning/matrix_database.ocr";
		char path_char[] = "../learning/character_database.ocr";


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
		init_matrix_random(b0, size_b0);
		init_matrix_random(b1, size_b1);

		
		/*//Test neural with the random value for the weight and biais
		//-------------------------------------------------------------------------
		printf("\nOutputs with random weights and biais...\n");
		print_feed_forward(weight0, weight1, a0, a1, a2, b0, b1, size_w0, size_w1,
				size_a0, size_a1, size_a2, size_b0, size_b1);
*/
		mat_to_file(size_w0, size_w1, size_b0, size_b1,
				weight0, weight1, b0, b1, "test.ocr");

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


		char good_char;

		FILE *matrix_db;
		matrix_db = fopen(path_matrix, "r");
		
		FILE *char_db;
		char_db = fopen(path_char, "r");

		if (matrix_db == NULL || char_db == NULL)
		{
			errx(1, "Could not acces database");
		}


		for (int k = 0; k < nb_epoch; k++)
		{
			printf("epoch %d/%d\n", k, nb_epoch);


			//Reset the matrix to 0
			init_matrix_with_0(d_b1, s_d_b1);
			init_matrix_with_0(d_w1, s_d_w1);
			init_matrix_with_0(d_b0, s_d_b0);
			init_matrix_with_0(d_w0, s_d_w0);

			//Start the learning phase
			//----------------------------------------------------------------------
			for (int i = 0; i < 20; i++)
			{
				init_a0(a0, size_a0, &good_char, matrix_db, char_db);


				feedforward(weight0, weight1, a0, a1, a2, b0, b1, size_w0,
						size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);

				backpropagation(weight1, a0, a1, a2, size_w0, size_w1, size_a0,
						size_a1, size_a2, size_b0, size_b1, d_b1, d_w1, d_b0, d_w0,
						s_d_b1, s_d_w1, s_d_b0, s_d_w0, &good_char);
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
		/*print_feed_forward(weight0, weight1, a0, a1, a2, b0, b1, size_w0, size_w1, 
				size_a0, size_a1, size_a2, size_b0, size_b1);*/
	}



	/*
	if (argc == 4)
	{
		//Seed for the random
		srand(time(NULL));

		//Choosing the number of input neurons
		int nb_input_neurons = 2;

		//Choosing the number of neurons in the hidden layer
		int nb_hidden_layer_neurons = atoi(argv[1]);


		//Choosing the number of output neurons
		int nb_output_neurons = 1;

		//Choosing the number of epoch
		int nb_epoch = atoi(argv[2]);


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

		int nb_error = 0;
		int nb_test = atoi(argv[3]);

		for(int y = 0; y < nb_test; y++)
		{
			init_matrix_random(weight0, size_w0);
			init_matrix_random(weight1, size_w1);
			init_matrix_random(b0, size_b0);
			init_matrix_random(b1, size_b1);

			//Test neural Xor with the random value for the weight and biais
			//-------------------------------------------------------------------------
			//printf("Test %d on %d\n", y, nb_test);

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
				mini_batch(d_b1, d_w1, d_b0, d_w0, s_d_b1, s_d_w1, s_d_b0, s_d_w0,
						weight0, weight1, a0, a1, a2, b0, b1, size_w0, size_w1,
						size_a0, size_a1, size_a2, size_b0, size_b1);

				//End of epoch
				add_matrix(b1, d_b1, size_b1, s_d_b1);
				add_matrix(weight1, d_w1, size_w1, s_d_w1);
				add_matrix(b0, d_b0, size_b0, s_d_b0);
				add_matrix(weight0, d_w0, size_w0, s_d_w0);
			}
			nb_error += is_working(weight0, weight1, a0, a1, a2, b0, b1, size_w0,
					size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);
		}


		printf("With %d neurons, %d epoch, on %d test => Number of error = %d/%d\n",
				nb_hidden_layer_neurons, nb_epoch, nb_test, nb_error,nb_test*4);
	}
	*/
	
	/*if (argc != 1 && argc !=4)
	{
		printf("\nmain: Usage: nb_neurons_hidden_layer nb_epoch nb_test\n");
	}*/

}




/*void mini_batch(double d_b1[], double d_w1[], double d_b0[], double d_w0[],
		int s_d_b1[], int s_d_w1[], int s_d_b0[], int s_d_w0[],
		double weight0[], double weight1[], double a0[], double a1[], double a2[],
		double b0[], double b1[], int size_w0[], int size_w1[], 
		int size_a0[], int size_a1[], int size_a2[], int size_b0[], int size_b1[])
{
	//Reset the matrix to 0
	init_matrix_with_0(d_b1, s_d_b1);
	init_matrix_with_0(d_w1, s_d_w1);
	init_matrix_with_0(d_b0, s_d_b0);
	init_matrix_with_0(d_w0, s_d_w0);

	//Start epoch
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
}*/

/*int is_working(double *weight0, double *weight1, double *a0, double *a1,
		double *a2, double *b0, double *b1, int *size_w0, int *size_w1,
      int *size_a0, int *size_a1, int *size_a2, int *size_b0, int *size_b1)
{
	int is_working_output = 0;

	for (double i = 0; i < 2; i++)
	{
		for (double j = 0; j < 2; j++)
		{
			a0[0] = i;
			a0[1] = j;

			feedforward(weight0, weight1, a0, a1, a2, b0, b1, size_w0,
					size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);
			
			int input1;
			int input2;
			int output;

			input1 = a0[0];
			input2 = a0[1];
			if (a2[0] >= 0.5)
			{
				output = 1;
			}
			else
			{
				output = 0;
			}

			if (output != (input1 ^ input2))
			{
				is_working_output++;
			}
		}
	}

	return is_working_output;
}*/

