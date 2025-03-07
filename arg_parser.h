#include <stdio.h>
#include <stdbool.h>

#define ARG_STRING "hsae:n:" // Шаблон для командной строки

// Обозначение аргументов командной строки
enum PARAMS_LIST
{
    help = 'h',
    steps = 's',
    abscissas = 'a',
    eps1 = 'e',
    eps2 = 'n'
};

// Набор возможных аргументов командной строки
struct parameters
{
    bool need_help;
    bool steps;
    bool abscissas;
    float eps1;
    size_t eps2;
};

// Функция для разбора аргументов командной строки
void read_arguments(int argc, char **argv, struct parameters *params);