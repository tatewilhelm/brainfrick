#include "arguments.h"
#include <string.h>

struct arguments_t lexicalize_args(int argc, char* argv[])
{
    struct arguments_t arguments;

    arguments.error = UNSET_ERROR;
    arguments.cell_size = 8; // Default

    for (int i = 1; i < argc; i++)
    {
        
        char *argument = argv[i];

        // Check if not a argument
        if (argument[0] != '-')
        {
            if( access( argument, R_OK ) == 0 ) {
                // File exists
                arguments.filepath = argument;
            } else {
                // File doesnt exist
                arguments.error = FILE_DOESNT_EXIST;
            }

            
            
        } else if (strcmp(argument, "--transpile") || strcmp("-t", argument)) {
            if (arguments.mode != UNSET_MODE)
            {
                arguments.error = INCOMPATIBLE_ARG;
                return arguments;
            }
            
            i++;
            
            // Prevent Segmentation fault
            if (i == argc)
            {
                arguments.error = INCOMPLETE_ARG;
                return arguments;
            }

            char *suffix = argv[i];

            // Detemine Language
            if (strcmp("python", suffix))
            {
                arguments.mode = PYTHON_TRANSPILE;
            } else if (strcmp("c", suffix)) {
                arguments.mode = C_TRANSPILE;
            } else {
                arguments.error = INCOMPLETE_ARG;
                return arguments;
            }

        } else if (strcmp(argument, "--interpret") || strcmp("-i", argument)) {

            if (arguments.mode != UNSET_MODE)
            {
                arguments.error = INCOMPATIBLE_ARG;
                return arguments;
            }

            arguments.mode = INTERPRETED;

        } else if (strcmp(argument, "--8bit") || strcmp("-1", argument)) {

            arguments.cell_size = 8;

        } else if (strcmp(argument, "--16bit") || strcmp("-2", argument)) {

            arguments.cell_size = 16;

        } else if (strcmp(argument, "--32bit") || strcmp("-4", argument)) {

            arguments.cell_size = 32;
        } else if (strcmp(argument, "--compile") || strcmp("-c", argument)) {

            if (arguments.mode != UNSET_MODE)
            {
                arguments.error = INCOMPATIBLE_ARG;
                return arguments;
            }

            arguments.mode = COMPILED;

        }
    }

    arguments.error = NO_ERROR;
    return arguments;
}