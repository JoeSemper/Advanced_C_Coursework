#include <stdio.h>
#include "calculations.h"

typedef float (*function)(float);

float f1(float x)
{
    return 0.6 * x + 3;
}

float f2(float x)
{
    return (x - 2) * (x - 2) * (x - 2) - 1;
}

float f3(float x)
{
    return x / 3;
}

float df1(float x)
{
    return 3 / 5;
}

float df2(float x)
{
    return 3 * (x - 2) * (x - 2);
}

float df3(float x)
{
    return -(3 / (x * x));
}


