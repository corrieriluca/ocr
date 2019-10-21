#include <stdio.h>
#include "neuralxor.h"


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
	for (double i = 0; i < 2; i++)
   {
      for (double j = 0; j < 2; j++)
      {
         a0[0] = i;
         a0[1] = j;
         feedforward(weight0, weight1, a0, a1, a2, b0, b1,
               size_w0, size_w1, size_a0, size_a1, size_a2, size_b0, size_b1);
         printf("Inputs: %lf %lf -> %lf\n", a0[0], a0[1], a2[0]);
      }
   }
}
