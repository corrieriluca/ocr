#ifndef NEURAL_H
#define NEURAL_H

void feedforward(double *weight0, double *weight1, double *a0, double *a1,
		double *a2, double *b0, double *b1, int *size_w0, int *size_w1,
      int *size_a0, int *size_a1, int *size_a2, int *size_b0, int *size_b1);

void backpropagation(double *weight1, double *a0, double *a1,
		double *a2, int *size_w0, int *size_w1, int *size_a0,
      int *size_a1, int size_a2[], int *size_b0, int *size_b1,
      double *d_b1, double *d_w1, double *d_b0, double *d_w0,
      int *s_d_b1, int *s_d_w1, int *s_d_b0, int *s_d_w0, 
	  char *good_char, double *sum_cost);


#endif

