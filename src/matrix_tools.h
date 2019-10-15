#ifndef MATRIX_TOOLS_H
#define MATRIX_TOOLS_H

void print_matrix(size_t matrix[], size_t height, size_t width);
void matrix_random_fill(size_t matrix[], size_t height, size_t width);

size_t *extract_matrix(size_t sourceMatrix[], size_t width,
                       size_t startingRow, size_t startingColumn,
                       size_t resultHeight, size_t resultWidth);

#endif