#include <stdio.h>
#include <string.h>
#include <err.h>
#include "neural.h"
#include "math_tools.h"

char recognize(double *weight0, double *weight1, double *a0,
		double *a1, double *a2, double *b0, double *b1, int *size_w0,
		int *size_w1, int *size_a0, int *size_a1, int *size_a2,
		int *size_b0, int *size_b1)
{
	/*
	int size = size_a0[0] * size_a0[1];
	for (int i = 0; i < size; i++)
	{
		if (matchar[i] == 0.0)
		{
			a0[i] = 0.0;
		}
		else
		{
			a0[i] = 1.0;
		}
	}*/

	feedforward(weight0, weight1, a0, a1, a2, b0, b1, size_w0, size_w1, size_a0,
		size_a1, size_a2, size_b0, size_b1);


	char return_char = '*';
	return_char = find_index_letter(a2, size_a2);

	return return_char;
}


void print_feed_forward(double *weight0, double *weight1, double *a0,
		double *a1, double *a2, double *b0, double *b1, int *size_w0,
		int *size_w1, int *size_a0, int *size_a1, int *size_a2,
		int *size_b0, int *size_b1)
{
	//Path to database
	char path_matrix_test[] = "../../learning/matrix_database_test.ocr";
	char path_char_test[] = "../../learning/character_database_test.ocr";

	FILE *matrix_db_test;
	matrix_db_test = fopen(path_matrix_test, "r");

	FILE *char_db_test;
	char_db_test = fopen(path_char_test, "r");

	if (matrix_db_test == NULL || char_db_test == NULL)
	{
		errx(1, "Could not acces database_test");
	}

	double compteur = 0.0;
	int nb_test = 400;

	for (int i = 0; i < nb_test; i++)
	{
		char charac[3];
		fgets(charac, sizeof(charac), char_db_test);
		char good_char = charac[0];

		char matrix[(size_a0[0]*size_a0[1]*2+2)];
		fgets(matrix, (size_a0[0]*size_a0[1]*2+2), matrix_db_test);

		int size = size_a0[0] * size_a0[1];
		for (int i = 0; i < size; i++)
		{
			if (matrix[i] == '0')
			{
				a0[i] = 0.0;
			}
			else
			{
				a0[i] = 1.0;
			}
		}

		feedforward(weight0, weight1, a0, a1, a2, b0, b1, size_w0, size_w1, size_a0,
			size_a1, size_a2, size_b0, size_b1);


		char return_char = '*';

		return_char = find_index_letter(a2, size_a2);
		int return_char_index = wanted_letter(&good_char);

		if (return_char_index == index_max_matrix(a2, size_a2))
		{
			compteur++;
			printf("\033[1;34m");
		}
		else
		{
			printf("\033[1;31m");
		}

		printf("Given letter : %c (index = %02d) || ", good_char, return_char_index);
		printf("output letter : %c (index = %02d)\033[0m\n", return_char, index_max_matrix(a2,size_a2));
	}

	double success_rate = compteur / nb_test;
	printf("Success rate = %lf\n", success_rate);

	fclose(matrix_db_test);
	fclose(char_db_test);
}

