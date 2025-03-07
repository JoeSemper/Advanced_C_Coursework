#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "calculations.h"

#define N_ROOTS 5  // Количество точек пересечения графиков
#define N_POINTS 5 // Количество точек для вычисления интеграла

typedef float (*function)(float);

struct point
{
    float xl;
    float xr;
};

// Диапазоны для нахождения точек пересечения функций
struct point root_intervals[N_ROOTS] = {{-6, -5.5}, {-0.5, -0.1}, {0.5, 1}, {3, 3.5}, {3.5, 4}};

// Диапазоны для нахождения точек пересечения для вычисления интегралов
struct point integral_intervals[N_POINTS] = {{-6, -5.5}, {-5.5, -4.5}, {-0.5, -0.1}, {2.5, 3.5}, {3.5, 4}};

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

float rootFindDiv2(float xl, float xr, float eps, function f, bool print_steps)
{
    int stepcount = 0; // число шагов
    float xm;
    while (fabs(xr - xl) > eps)
    { // вещественный модуль разницы
        stepcount++;
        xm = (xl + xr) / 2; // середина отрезка
        if (f(xr) == 0)
        { // нашли решение на правой границе
            if (print_steps)
                printf("Find root for %d steps\n", stepcount);
            return xr;
        }
        if (f(xl) == 0)
        { // нашли решение на левой границе
            if (print_steps)
                printf("Find root for %d steps\n", stepcount);
            return xl;
        }
        if (signF(xl, f) != signF(xm, f)) // если знак отличается
            xr = xm;
        else
            xl = xm;
    }
    if (print_steps)
        printf("Find root for %d steps\n", stepcount); // статистика
    return (xl + xr) / 2;
}

// Функции поиска точек пересечения исходных функций

float root_f1(float xl, float xr, float eps, bool print_steps)
{
    return rootFindDiv2(xl, xr, eps, f1, print_steps);
}

float root_f2(float xl, float xr, float eps, bool print_steps)
{
    return rootFindDiv2(xl, xr, eps, f2, print_steps);
}

float root_f1_f3(float xl, float xr, float eps, bool print_steps)
{
    return rootFindDiv2(xl, xr, eps, f1_f3, print_steps);
}

float root_f2_f3(float xl, float xr, float eps, bool print_steps)
{
    return rootFindDiv2(xl, xr, eps, f2_f3, print_steps);
}

float root_f1_f2(float xl, float xr, float eps, bool print_steps)
{
    return rootFindDiv2(xl, xr, eps, f1_f2, print_steps);
}

// Нахождение всех точек пересечения функций
void find_all_intersection_points(float eps, float points[], bool print_steps)
{
    points[0] = root_f1_f3(root_intervals[0].xl, root_intervals[0].xr, eps, print_steps);
    points[1] = root_f2_f3(root_intervals[1].xl, root_intervals[1].xr, eps, print_steps);
    points[2] = root_f1_f3(root_intervals[2].xl, root_intervals[2].xr, eps, print_steps);
    points[3] = root_f2_f3(root_intervals[3].xl, root_intervals[3].xr, eps, print_steps);
    points[4] = root_f1_f2(root_intervals[4].xl, root_intervals[4].xr, eps, print_steps);
}

// Печать всех точек пересечения
void print_all_intersection_points(float eps, bool print_steps)
{
    float points[N_ROOTS];

    find_all_intersection_points(eps, points, print_steps);

    printf("Intersection points: ");

    for (int i = 0; i < N_ROOTS; i++)
    {
        printf("%f", points[i]);

        if (i == N_ROOTS - 1)
        {
            printf("\n");
        }
        else
        {
            printf(", ");
        }
    }
    printf("\n");
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
    return fabs(sum);
}

// Нахождение интервалов точек для вычисления интегралов
void find_integral_intervals(float eps, float points[])
{
    points[0] = root_f1_f3(integral_intervals[0].xl, integral_intervals[0].xr, eps, false);
    points[1] = root_f1(integral_intervals[1].xl, integral_intervals[1].xr, eps, false);
    points[2] = root_f1_f3(integral_intervals[2].xl, integral_intervals[2].xr, eps, false);
    points[3] = root_f2(integral_intervals[3].xl, integral_intervals[3].xr, eps, false);
    points[4] = root_f1_f2(integral_intervals[4].xl, integral_intervals[4].xr, eps, false);
}

float calculate_integral(float eps1, size_t eps2)
{
    float points[N_POINTS];

    find_integral_intervals(eps1, points);

    float a_b = calcIntegralTrap(points[0], points[1], eps2, f3) - calcIntegralTrap(points[0], points[1], eps2, f1);
    float b_c = calcIntegralTrap(points[1], points[2], eps2, f3) + calcIntegralTrap(points[1], points[2], eps2, f1);
    float c_d = calcIntegralTrap(points[2], points[3], eps2, f2) + calcIntegralTrap(points[2], points[3], eps2, f1);
    float d_e = calcIntegralTrap(points[4], points[5], eps2, f1) - calcIntegralTrap(points[4], points[5], eps2, f2);

    return a_b + b_c + c_d + d_e;
}

float print_area(float eps1, size_t eps2)
{
    float integral = calculate_integral(eps1, eps2);

    printf("Area of the figure = %f\n", integral);
    printf("\n");
}
