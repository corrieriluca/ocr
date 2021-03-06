#include <stdlib.h>
#include <math.h>


//Init a matrix
void init_matrix_random(double *matrix, int *size)
{
   for (int i = 0; i < size[0] * size[1]; i++)
   {

			//double d = (2 / sqrt(size[1]));
			double d = sqrt((2 / size[1]));
			matrix[i] = (((double) rand()) / (double) RAND_MAX) * (d + d) - d;

			//To change the range put that after the RAND_MAX: (max - min) - min
			//matrix[i] = (((double) rand()) / (double) RAND_MAX) * (4) - 2;

      //To change the range put that after the RAND_MAX: (max - min) - min
      matrix[i] = (((double) rand()) / (double) RAND_MAX) * (4) - 2;
   }
}

void init_matrix_with_0(double *matrix, int *size)
{
   for (int i = 0; i < size[0] * size[1]; i++)
   {
		matrix[i] = 0;
   }
}

