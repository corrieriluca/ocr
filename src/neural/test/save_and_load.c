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
		errx(1, "File loading failed.");
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
