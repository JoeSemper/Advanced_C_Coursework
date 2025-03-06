#include <stdio.h>
#include <stdbool.h>

#define ARG_STRING "he:n:" // Шаблон для командной строки

enum PARAMS_LIST
{
    help = 'h',
    eps1 = 'e',
    eps2 = 'n'
};

struct parameters
{
    bool need_help;
    float eps1;
    size_t eps2;
};

void read_arguments(int argc, char **argv, struct parameters *params);