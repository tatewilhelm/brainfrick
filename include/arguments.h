#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>


enum mode_t 
{
    UNSET_MODE, INTERPRETED, COMPILED, PYTHON_TRANSPILE, C_TRANSPILE, HELP
};

enum error_t 
{
    UNSET_ERROR, NO_ERROR, NO_FILE, INCOMPLETE_ARG, NO_ARGS, INVALID_ARG, INCOMPATIBLE_ARG, FILE_DOESNT_EXIST,
    PATH_IS_DIRECTORY
};


struct arguments_t
{
    char* filepath;
    char* output_filepath;
    bool specified_output_filepath;
    enum error_t error;
    enum mode_t mode;
    int cell_size; // 8, 16 or 32 bits
    bool return_ending_cell;
    bool infinite_cells;
    
};


struct arguments_t lexicalize_args(int argc, char* argv[]);

#endif