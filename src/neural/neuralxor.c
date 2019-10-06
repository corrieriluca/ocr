#include <stdio.h>
#include "neuralxor.h"
#include "math_tools.h"


int main()
{
        double mat1[] = {1,2,3,4};
        double mat2[] = {5,6,7,8};
   double output[2*2];
        multiply_matrix(mat1,mat2,output,2,2,2,2);

        double input[2*2];
        init_matrix_random(input, 2, 2);



        for (size_t i = 0; i < 2*2; ++i)
        {
                printf("%lf\n", output[i]);
        }

        for (size_t b = 0; b < 2*2; ++b)
        {
                printf("%lf\n", input[b]);
        }
        return 0;
}



