#include "arguments.h"

struct arguments_t lexicalize_args(int argc, char* argv[])
{
    struct arguments_t arguments;
    bool file_set = false;

    arguments.error = UNSET_ERROR;
    arguments.cell_size = 8; // Default

    for (int i = 1; i < argc; i++)
    {
        
        char *argument = argv[i];

        // Check if not a argument
        if (argument[0] != '-')
        {

            if(fopen(argument, "r")) {
                // File exists and 
                arguments.filepath = argument;
                file_set = true;
            } else {
                // File doesnt exist
                arguments.error = FILE_DOESNT_EXIST;
            }

            
            
        } else if (strcmp(argument, "--transpile") == 0 || strcmp("-t", argument) == 0) {
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
            if (strcmp("python", suffix) == 0)
            {
                arguments.mode = PYTHON_TRANSPILE;
            } else if (strcmp("c", suffix) == 0) {
                arguments.mode = C_TRANSPILE;
            } else {
                arguments.error = INCOMPLETE_ARG;
                return arguments;
            }

        } else if ((strcmp(argument, "--interpret") == 0) || (strcmp("-i", argument) == 0)) {

            if (arguments.mode != UNSET_MODE)
            {
                arguments.error = INCOMPATIBLE_ARG;
                return arguments;
            }

            arguments.mode = INTERPRETED;

        } else if ((strcmp(argument, "--8bit") == 0) || (strcmp("-1", argument) == 0)) {

            arguments.cell_size = 8;

        } else if ((strcmp(argument, "--16bit") == 0) || (strcmp("-2", argument) == 0)) {

            arguments.cell_size = 16;

        } else if ((strcmp(argument, "--32bit") == 0) || (strcmp("-4", argument) == 0)) {

            arguments.cell_size = 32;
        } else if ((strcmp(argument, "--compile") == 0) || (strcmp("-c", argument) == 0)) {

            if (arguments.mode != UNSET_MODE)
            {
                arguments.error = INCOMPATIBLE_ARG;
                return arguments;
            }

            arguments.mode = COMPILED;

        }
    }

    // Check if file was set
    if (!file_set)
    {
        arguments.error = NO_FILE;
        return arguments;
    }
    
    arguments.error = NO_ERROR;
    return arguments;
}