#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>


enum mode_t 
{
    UNSET_MODE, INTERPRETED, COMPILED, PYTHON_TRANSPILE, C_TRANSPILE
};

enum error_t 
{
    UNSET_ERROR, NO_ERROR, NO_FILE, INCOMPLETE_ARG, NO_ARGS, INVALID_ARG, INCOMPATIBLE_ARG, FILE_DOESNT_EXIST, HELP
};


struct arguments_t
{
    char* filepath;
    enum error_t error;
    enum mode_t mode;
    int cell_size; // 8, 16 or 32 bits
};


struct arguments_t lexicalize_args(int argc, char* argv[]);

#endif