#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void init_matrix_random(double *input, size_t i, size_t j)
{
        srand(time(NULL));
        for(size_t index = 0; index < i * j; ++index)
        {
          input[index] = (double)rand()/(double)RAND_MAX;
        }
}


void multiply_matrix(double mat1[], double mat2[], double mat_out[], 
		int size_mat1[], int size_mat2[])   
{                                                                               
   size_t i,j,k;                                                                
	double sum;

	printf("START THE FIRST MULTIPLICATION ######################################\n\n\n");
   for(i = 0; i <  size_mat1[1]; ++i)                                              
   {                                                                            
      for(j = 0; j < size_mat2[0]; ++j)                                            
      { 
         sum = 0;                                                        

         for (k = 0; k < size_mat1[0]; k++)                                        
         {                                                                      
            sum = sum + mat1[i * size_mat1[0] + k] * mat2[k * size_mat2[0] + j];      

				printf("val weight = %lf and val input = %lf \n", mat1[i*size_mat1[0]+k], mat2[k*size_mat2[0]+j]);
				printf("%lf\n", sum);
         }             
			printf("\n");
         mat_out[i * size_mat2[0] + j] = sum;                                       
      }                              
   }                                                                            
	printf("END OF FIRST MULTIPLICATION ######################################\n");
}

void sum_matrix(double mat1[], double mat2[], int size)
{
	for (int index = 0; index < size; index++)
	{
		mat1[index] += mat2[index];
	}
}

double sigmoid(double z)
{
	return (double)(1.0 / (1.0 + exp(-z)));
}
void apply_sigmoid_to_matrix(double mat1[], int size)
{
	for (int index = 0; index < size; index++)
	{
		mat1[index] = sigmoid(mat1[index]);
	}
}



double sigmoid_prime(double z)
{
	return z * (1 - z);
}

