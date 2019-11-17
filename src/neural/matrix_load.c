#include <stdio.h>
#include <err.h>

int file_to_mat(int mat1[], int mat2[], int mat3[], int mat4[],
	double mat5[], double mat6[], double mat7[], double mat8[],
							char filename[])
{
	FILE * f; //f = flux used to write our file

	f = fopen(filename, "r");

	if (f != NULL)
	{
		int m1 = mat1[1];
		for(int i = 0; i < mat1[0]; i++)
		{
			for(int j = 0; j < m1; j++)
			{
				if(fscanf(f, "%lf ", &mat5[i*m1+j]) == 0)
				{
					errx(1, "fscanf failed");
				}
			}
		}
		int m2 = mat2[1];
		for(int i = 0; i < mat2[0]; i++)
		{
			for(int j = 0; j < m2; j++)
			{
				if(fscanf(f, "%lf", &mat6[i*m2+j]) == 0)
				{
					errx(1, "fscanf failed");
				}
			}
		}
		int m3 = mat3[1];
		for(int i = 0; i < mat3[0]; i++)
		{
			for(int j = 0; j < m3; j++)
			{
				if(fscanf(f, "%lf", &mat7[i*m3+j]) == 0)
				{
					errx(1, "fscanf failed");
				}
			}
		}
		int m4 = mat4[1];
		for(int i = 0; i < mat4[1]; i++)
		{
			for(int j = 0; j < m4; j++)
			{
				if(fscanf(f, "%lf", &mat8[i*m4+j]) == 0)
				{
					errx(1, "fscanf failed");
				}
			}                                                       
                }		
		fclose(f);
	}
	else
	{
		errx(1, "File creation failed.");
	}

	return 0;
}

/*
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

int main()                                                                      
{
	int a[2] = {3,3};
	int b[2] = {2,3};
	int c[2] = {3,2};
	int d[2] = {2,2};
	double e[9] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
	double f[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
	double g[6] = {0.0,0.0,0.0,0.0,0.0,0.0};
	double h[4] = {0.0,0.0,0.0,0.0};
	int i;
	i =  file_to_mat(a, b, c, d, e, f, g, h, "_matrices2.txt");
	print_matrix_double(e, a);
	print_matrix_double(f, b);
	print_matrix_double(g, c);
	print_matrix_double(h, d);
	if(i == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}                                                                     
}
*/
