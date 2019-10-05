#include <stdio.h>
#include "backpropagation.h"

double sigmoid(double val)
{
    return 1.0/(1.0 + exp(-val));
}
