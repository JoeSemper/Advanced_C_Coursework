#include <stdio.h>
#include "arg_parser.h"
#include "calculations.h"

int main(int argc, char **argv)
{
    struct parameters params = {.need_help = false, .eps1 = 0.001, .eps2 = 1000};

    read_arguments(argc, argv, &params);

    // printf("%f\n", params.eps1);
    // printf("%d\n", params.eps2);

    print_all_intersection_points(params.eps1);

    print_area(params.eps1, params.eps2);

    return 0;
}