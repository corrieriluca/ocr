#include <stdio.h>
#include <err.h>

void matload(FILE *f, double mat[], int size[])
{
		for(int i = 0; i < size[0]; i++)
		{
			for(int j = 0; j < size[1]; j++)
			{
				if(fscanf(f, "%lf ", &mat[ i * size[1] + j]) == 0)
				{
					errx(1, "fscanf failed");
				}
			}
		}
}


void savemat(FILE *f, double mat[], int size[])
{
	for (int i = 0; i < size[0]; i++)
	{
		for(int j = 0; j < size[1]; j++)
		{
			if(j == size[1] - 1)
			{
				fprintf(f, "%f\n", mat[i * size[1] + j]);
			}
			else
			{
				fprintf(f, "%f ", mat[i * size[1] + j]);
			}
		}
	}
}


int file_to_mat(double w0[], double w1[], double b0[], double b1[], 
		int size_w0[], int size_w1[], int size_b0[], int size_b1[],
		char filename[])
{
	FILE * f; //f = flux used to write our file
	f = fopen(filename, "r");

	if (f != NULL)
	{
		matload(f, w0, size_w0);
		matload(f, w1, size_w1);
		matload(f, b0, size_b0);
		matload(f, b1, size_b1);

		fclose(f);
	}
	else
	{
		errx(1, "File creation failed.");
	}

	return 0;
}

int mat_to_file(double w0[], double w1[], double b0[], double b1[], 
		int size_w0[], int size_w1[], int size_b0[], int size_b1[],
		char filename[])
{
	FILE * f; //f = flux used to write our file

	f = fopen(filename, "w+");

	if (f != NULL)
	{
		savemat(f, w0, size_w0);
		savemat(f, w1, size_w1);
		savemat(f, b0, size_b0);
		savemat(f, b1, size_b1);

		fclose(f);
	}
	else
	{
		errx(1, "File creation failed.");
	}

	return 0;
}
/*
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
	
		return 1;
	}
}
*/
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

