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

enum interpret_mode_t
{
    // CHAR FILE reads a char from a file every cycle, slow but best for extremely large files or systems with low memory
    // READ_ONCE reads the entire file at the start, not reccomended for systems with extremely low memory but fastest
    UNSET_INTERPRET_MODE, READ_ONCE, CHAR_FILE
};


struct arguments_t
{
    char* filepath;
    char* output_filepath;
    bool specified_output_filepath;
    enum error_t error;
    enum mode_t mode;
    enum interpret_mode_t interpret_mode;
    int string_read_buffer_size;
    int cell_size; // 8, 16 or 32 bits
    bool return_ending_cell;
    bool infinite_cells;
    
};


struct arguments_t lexicalize_args(int argc, char* argv[]);

#endif