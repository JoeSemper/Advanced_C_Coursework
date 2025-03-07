#include <stdio.h>
#include "arg_parser.h" // Файл с разбором аргументов командной строки
#include "calculations.h" // Файл со всеми вычисленийми

void print_help_text();

// Главная функция с основной логикой программы
int main(int argc, char **argv)
{
    struct parameters params =
    {
        .need_help = false,
        .steps = false,
        .abscissas = false,
        .eps1 = 0.001,
        .eps2 = 1000
    };

    read_arguments(argc, argv, &params);

    if (params.need_help)
        print_help_text();

    if (params.abscissas)
        print_all_intersection_points(params.eps1, params.steps);

    print_area(params.eps1, params.eps2);

    return 0;
}

// Функция печати справки
void print_help_text()
{
    printf("\n");
    printf("Command line arguments:\n");
    printf(" -h - help\n");
    printf(" -s - print number of steps for finding points\n");
    printf(" -a - print abscissas of points of intersection\n");
    printf(" -e <epsilon> - epsilon for points of intersection\n");
    printf(" -n <segments> - number of segments for integral calculation\n");
    printf("\n");
}