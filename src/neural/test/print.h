#ifndef PRINT_H
#define PRINT_H

char recognize(double *weight0, double *weight1, double *a0,
		double *a1, double *a2, double *b0, double *b1, int *size_w0,
        int *size_w1, int *size_a0, int *size_a1, int *size_a2,
        int *size_b0, int *size_b1);

void print_feed_forward(double *weight0, double *weight1, double *a0,
		double *a1, double *a2, double *b0, double *b1, int *size_w0,
      int *size_w1, int *size_a0, int *size_a1, int *size_a2,
      int *size_b0, int *size_b1);

#endif

