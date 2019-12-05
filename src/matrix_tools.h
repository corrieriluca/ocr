#ifndef MATRIX_TOOLS_H
#define MATRIX_TOOLS_H

void print_matrix(size_t matrix[], size_t height, size_t width);
void print_matrix_double(double matrix[], size_t height, size_t width);
void matrix_random_fill(size_t matrix[], size_t height, size_t width);

size_t *extract_matrix(size_t sourceMatrix[], size_t width,
                       size_t startingRow, size_t startingColumn,
                       size_t resultHeight, size_t resultWidth);

void remove_blank(size_t sourceMatrix[], size_t height, size_t width,
                    size_t res[]);

size_t *crop_matrix(size_t sourceMatrix[], size_t blankRes[], size_t width);

void matrix_in_square(size_t matrix[], size_t square[], size_t height,
                      size_t width, size_t squareSize);

double *resize_matrix(size_t matrix[], size_t height, size_t width);

#endif