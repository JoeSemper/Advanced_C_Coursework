#include <stdio.h>
#include "arg_parser.h"
#include "calculations.h"

int main(int argc, char **argv)
{

    print_all_intersection_points(0.0001);

    print_area(0.0001, 10000);

    return 0;
}