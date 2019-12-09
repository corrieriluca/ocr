#ifndef SAVE_AND_LOAD_H
#define SAVE_AND_LOAD_H

void matload(FILE *f, double mat[], int size[]);

void savemat(FILE *f, double mat[], int size[]);

int file_to_mat(double w0[], double w1[], double b0[], double b1[],
		int size_w0[], int size_w1[], int size_b0[], int size_b1[],
		char filename[]);

int mat_to_file(double w0[], double w1[], double b0[], double b1[],
		int size_w0[], int size_w1[], int size_b0[], int size_b1[],
		char filename[]);

#endif
