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


void multiply_matrix(double mat1[], double mat2[],double output[],                            
      size_t larg_mat1, size_t larg_mat2, size_t haut_mat1, size_t haut_mat2)   
{                                                                               
   size_t i,j,k;                                                                
                                                                                
   for(i = 0; i <  haut_mat1; ++i)                                              
   {                                                                            
      for(j = 0; j < larg_mat1; ++j)                                            
      { 
         double sum = 0;                                                        

         for (k = 0; k < larg_mat2; ++k)                                        
         {                                                                      
            sum = sum + mat1[i * larg_mat1 + k] * mat2[k * larg_mat2 + j];      
         }                                                                      
                                                                                
         output[i * larg_mat2 + j] = sum;                                       
      }                                                                         
   }                                                                            
}


double sigmoid(double z)
{
	return (double)(1.0 / (1.0 + exp(-z)));
}


double sigmoid_prime(double z)
{
	return z * (1 - z);
}

