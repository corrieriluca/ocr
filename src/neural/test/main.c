#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h> //For atoi
#include <err.h>
#include "math_tools.h"
#include "print.h"
#include "save_and_load.h"

int main(int argc, char **argv)
{
	printf("%s\n",argv[0]);
	pretty_print_xor(40, "NEURAL");

	//Choosing the number of input neurons
	int nb_input_neurons = 16*16;

	//Choosing the number of output neurons
	int nb_output_neurons = 67;

	//Choosing the number of neurons in the hidden layer
	int nb_hidden_layer_neurons = 12000;

	//Choosing the number of epoch
	int nb_epoch = 4150;

	//Choosing the number of element per batch
	int batch_size = 15;

	//Total number of training data
	int nb_training_data = 62250;


	//Init all the weights, biais and activation point
	//-------------------------------------------------------------------------
	int size_a0[] = {nb_input_neurons,1};
	double a0[size_a0[0] * size_a0[1]];

	int size_a1[] = {nb_hidden_layer_neurons,1};
	double a1[size_a1[0] * size_a1[1]];

	int size_a2[] = {nb_output_neurons,1};
	double a2[size_a2[0] * size_a1[1]];

	int size_w0[] = {nb_hidden_layer_neurons,nb_input_neurons};
	double *weight0 = malloc((size_w0[0]*size_w0[1]) * sizeof(double));
	//double weight0[size_w0[0] * size_w0[1]];

	int size_w1[] = {nb_output_neurons,nb_hidden_layer_neurons};
	double *weight1 = malloc((size_w1[0]*size_w1[1]) * sizeof(double));
	//double weight1[size_w1[0] * size_w1[1]];

	int size_b0[] = {nb_hidden_layer_neurons,1};
	double b0[size_b0[0] * size_b0[1]];

	int size_b1[] = {nb_output_neurons,1};
	double b1[size_b1[0] * size_b1[1]];

	file_to_mat(weight0, weight1, b0, b1, 
			size_w0, size_w1, size_b0, size_b1, "test2.ocr");	

	print_feed_forward(weight0, weight1, a0, a1, a2, b0, b1, size_w0,
			size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);

	free(weight0);
	free(weight1);
}
