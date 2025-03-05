#include <stdio.h>
#include <math.h>
#include "calculations.h"

typedef float (*function)(float);

// Исходные функции

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
    return 3 / x;
}

// Пересечение исходных функций

float f1_f3(float x)
{
    return 0.6 * x + 3 - 3 / x;
}

float f2_f3(float x)
{
    return (x - 2) * (x - 2) * (x - 2) - 1 - 3 / x;
}

float f1_f2(float x)
{
    return (x - 2) * (x - 2) * (x - 2) - 1 - 0.6 * x - 3;
}

// Общая функция поиска точек пересечения

int signF(float x, function f)
{
    return f(x) == 0 ? 0 : (f(x) < 0 ? -1 : +1);
}

float rootFindDiv2(float xl, float xr, float eps, function f)
{
    int stepcount = 0; // число шагов
    float xm;
    while (fabs(xr - xl) > eps)
    { // вещественный модуль разницы
        stepcount++;
        xm = (xl + xr) / 2; // середина отрезка
        if (f(xr) == 0)
        { // нашли решение на правой границе
            printf("Find root for %d steps\n", stepcount);
            return xr;
        }
        if (f(xl) == 0)
        { // нашли решение на левой границе
            printf("Find root for %d steps\n", stepcount);
            return xl;
        }
        if (signF(xl, f) != signF(xm, f)) // если знак отличается
            xr = xm;
        else
            xl = xm;
    }
    printf("Find root for %d steps\n", stepcount); // статистика
    return (xl + xr) / 2;
}

// Функции поиска точек пересечения исходных функций

float intersection_f1_f3(float xl, float xr, float eps)
{
    return rootFindDiv2(xl, xr, eps, f1_f2);
}

float intersection_f2_f3(float xl, float xr, float eps)
{
    return rootFindDiv2(xl, xr, eps, f2_f3);
}

float intersection_f1_f2(float xl, float xr, float eps)
{
    return rootFindDiv2(xl, xr, eps, f1_f2);
}

// Нахождение всех точек пересечения
void find_All_intersection_points(float eps, float points[], int nPoints)
{

}

// Печать всех точек пересечения
void print_All_intersection_points(float eps)
{

}

// Функция вычисления интеграла
float calcIntegralTrap(float xl, float xr, size_t n, function f)
{
    float sum = 0;
    float h = (xr - xl) / n;
    for (float x = xl + h; x < xr - h; x += h)
    {
        sum += 0.5 * h * (f(x) + f(x + h));
    }
    return sum;
}

float integral_f1(float xl, float xr)
{
    return calcIntegralTrap(xl, xr, 10000, f2);
}
