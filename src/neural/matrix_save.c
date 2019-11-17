#include "stdio.h"
#include "err.h"

int mat_to_file(int mat1[], int mat2[], int mat3[], int mat4[], double mat5[], 
	double mat6[], double mat7[], double mat8[], char filename[])
{
	FILE * f; //f = flux used to write our file

	f = fopen(filename, "w");

	if (f != NULL)
	{
		int m1 = mat1[1];
		for(int i = 0; i < mat1[0]; i++)
		{
			for(int j = 0; j < m1; j++)
			{
				if(j == m1-1)
				{
					fprintf(f, "%f\n", mat5[i*m1+j]);
				}
				else
				{
					fprintf(f, "%f ", mat5[i*m1+j]);
				}
			}
		}
		int m2 = mat2[1];
		for(int i = 0; i < mat2[0]; i++)
		{
			for(int j = 0; j < m2; j++)
			{
				if(j == m2-1)
				{
					fprintf(f, "%f\n", mat6[i*m2+j]);
				}
				else
				{
					fprintf(f, "%f ", mat6[i*m2+j]);
				}
			}
		}
		int m3 = mat3[1];
		for(int i = 0; i < mat3[0]; i++)
		{
			for(int j = 0; j < m3; j++)
			{
				if(j == m3-1)
				{
					fprintf(f, "%f\n", mat7[i*m3+j]);
				}
				else
				{
					fprintf(f, "%f ", mat7[i*m3+j]);
				}
			}
		}

		int m4 = mat4[1];
		for(int i = 0; i < mat4[1]; i++)

		{
			for(int j = 0; j < m4; j++)
			{
				if(j == m4-1)
				{
					fprintf(f, "%f\n", mat8[i*m4+j]);
				}
				else
				{
					fprintf(f, "%f ", mat8[i*m4+j]);
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

int main()                                                                      
{
	int a[2] = {3,3};
	int b[2] = {2,3};
	int c[2] = {3,2};
	int d[2] = {2,2};
	double e[9] = {0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
	double f[6] = {0.1,0.2,0.3,0.4,0.5,0.6};
	double g[6] = {0.1,0.2,0.3,0.4,0.5,0.6};
	double h[4] = {0.1,0.2,0.3,0.4};
	int i;
	i =  mat_to_file(a, b, c, d, e, f, g, h, "_matrices2.txt");
	if(i == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}                                                                     
}
