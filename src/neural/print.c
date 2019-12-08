#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <err.h>
#include "neural.h"
#include "math_tools.h"


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
	char letters[] =                                                    
	   "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?'0123456789";

	srand(time(NULL));

	double compteur = 0.0;
	int nb_test = 100;

	for (int i = 0; i < nb_test; i++)
	{
		int index_rand = rand() % 67;                                       
																			
		char path_matrix[80];                                               
		snprintf(path_matrix, 80, "../learning/database/%d.txt", index_rand);
																			
		char good_char = letters[index_rand];                               
		printf("'%c' ", good_char);                                         
																			
		FILE *matrix_db;
		char matrix[(size_a0[0]*size_a0[1]*2+2)];
		matrix_db = fopen(path_matrix, "r");
		if (matrix_db == NULL)
		{
			printf("%s\n", path_matrix);
			printf("%d\n", index_rand);
			errx(1, "Could not acces database");
		}

		fgets(matrix, (size_a0[0]*size_a0[1]*2+2), matrix_db);
		int size = size_a0[0] * size_a0[1];
		for (int i = 0; i < size; i++)
		{
			if (matrix[i] == '0')
			{
				a0[i] = 0.0;
			}
			else
			{
				if (matrix[i] == '1')
				{
					a0[i] = 1.0;
				}
				else
				{
					printf("||**|*||");
				}
			}
		}

		feedforward(weight0, weight1, a0, a1, a2, b0, b1, size_w0, size_w1, size_a0,
			size_a1, size_a2, size_b0, size_b1);


		char return_char = '*';

		return_char = find_index_letter(a2, size_a2);
		int return_char_index = wanted_letter(good_char);

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
		fclose(matrix_db);
	}

	double success_rate = compteur / nb_test;
	printf("Success rate = %lf\n", success_rate);

}

