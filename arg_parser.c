#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "arg_parser.h"

// Функция для разбора аргументов командной строки
void read_arguments(int argc, char **argv, struct parameters *params)
{
    int arg;

    while ((arg = getopt(argc, argv, ARG_STRING)) != -1)
    {
        switch (arg)
        {
        case help:
            params->need_help = true;
            break;

        case steps:
            params->steps = true;
            break;

        case abscissas:
            params->abscissas = true;
            break;

        case eps1:
            params->eps1 = strtod(optarg, NULL);
            break;

        case eps2:
            params->eps2 = strtod(optarg, NULL);
            break;

        default:
            break;
        }
    }
}