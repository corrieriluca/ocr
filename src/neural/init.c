#include <stdio.h>
#include "backpropagation.h"

void fill_array_random(double** layer, size_t i, size_t j)
{
    for (size_t index1 = 0; i < i; ++index1)
        for (size_t index2 = 0; j < j; ++index2)
        {
            layer[index1][index2] = (double)  rand() / RAND_MAX * pow(-1, rand() % 2);
        }
}
