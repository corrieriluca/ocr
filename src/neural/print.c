#include <stdio.h>
#include <string.h>
#include "neural.h"
#include "math_tools.h"
#include <err.h>


void pretty_print_xor(size_t nb_char, char *str)
{
	if (nb_char < strlen(str)+6)
	{
		printf("pretty_print_xor: Can't print with these imputs");
	}

	else
	{
		size_t i;
		size_t middle = nb_char / 2 - strlen(str) / 2 - 3;

		for (i = 0; i < nb_char; i++)
		{
			printf("#");
		}

		printf("\n###");


		for (i = 0; i < nb_char - strlen(str) - 5; i++)
		{
			if (i == middle)
			{
				printf("%s",str);
			}
			else
			{
				printf(" ");
			}
		}
		printf("###\n");

		for (i = 0; i < nb_char; i++)
		{
			printf("#");
		}

		printf("\n");
	}
}


void print_matrix_double(double matrix[], int size[])
{
  int width = size[1];
  int height = size[0];

  printf("*");
  for (int i = 0; i < width; i++)
  {
    printf("-");
  }
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
  {
    printf("-");
  }
  printf("*\n");
}


void print_feed_forward(double *weight0, double *weight1, double *a0,
		double *a1, double *a2, double *b0, double *b1, int *size_w0,
		int *size_w1, int *size_a0, int *size_a1, int *size_a2,
		int *size_b0, int *size_b1)
{
	//Path to database
	char path_matrix_test[] = "../learning/matrix_database_test.ocr";
	char path_char_test[] = "../learning/character_database_test.ocr";

	FILE *matrix_db_test;
	matrix_db_test = fopen(path_matrix_test, "r");

	FILE *char_db_test;
	char_db_test = fopen(path_char_test, "r");

	if (matrix_db_test == NULL || char_db_test == NULL)
	{
		errx(1, "Could not acces database_test");
	}

	double compteur = 0.0;
	int nb_test = 60;

	for (int i = 0; i < nb_test; i++)
	{
		char charac[3];
		fgets(charac, sizeof(charac), char_db_test);
		char good_char = charac[0];

		char matrix[486]; //TODO : Find good size
		fgets(matrix, 486, matrix_db_test);

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


		/*//Ugly but usefull to print a2
		for (int z = 0; z < (size_a2[0] * size_a2[1]); z++)
		{
			if ((z % 10) == 0 && (z != 0))
			{
				printf("\n");
			}

			printf("|%lf|",a2[z]);
		}

		printf("\n");*/
	}

	double success_rate = compteur / nb_test;
	printf("Success rate = %lf\n", success_rate);

	fclose(matrix_db_test);
	fclose(char_db_test);
}

