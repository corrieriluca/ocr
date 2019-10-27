#include <stdlib.h>


//Init a matrix with values from -2 to 2                                        
void init_matrix_random(double *matrix, int *size)                              
{                                                                               
   for (int i = 0; i < size[0] * size[1]; i++)                                  
   {                                                                            
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

