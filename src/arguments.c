#include "arguments.h"

struct arguments_t lexicalize_args(int argc, char* argv[])
{
    struct arguments_t arguments;
    bool file_set = false;

    arguments.mode = UNSET_MODE;
    arguments.error = UNSET_ERROR;
    arguments.cell_size = 8; // Default
    arguments.return_ending_cell = false;
    arguments.infinite_cells = false;
    arguments.output_filepath = "";
    arguments.specified_output_filepath = false;
    arguments.interpret_mode = UNSET_INTERPRET_MODE;

    for (int i = 1; i < argc; i++)
    {
        
        char* argument = argv[i];

        // Check if not a argument
        if (argument[0] != '-')
        {

            if(fopen(argument, "r")) {
                // File exists 

                // Checking if directory
                struct stat path_stat;
                stat(argument, &path_stat);
                if (S_ISREG(path_stat.st_mode))
                {
                    // File exists and isnt a directory
                    arguments.filepath = argument;
                    file_set = true;
                } else {
                    // Path exists, yet its a directory
                    arguments.error = PATH_IS_DIRECTORY;
                    return arguments;
                }     
                
            } else {
                // File doesnt exist
                arguments.error = FILE_DOESNT_EXIST;
            }

        } else if (strcmp(argument, "--output") == 0 || strcmp("-o", argument) == 0) {
            i++;
        
            // Prevent Segmentation fault
            if (i == argc)
            {
                arguments.error = INCOMPLETE_ARG;
                return arguments;
            }

            

            arguments.specified_output_filepath = true;
            arguments.output_filepath = argv[i];
        
            
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

            char* suffix = argv[i];

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

        } else if ((strcmp(argument, "--compile") == 0) || (strcmp("-c", argument) == 0)) {

            if (arguments.mode != UNSET_MODE)
            {
                arguments.error = INCOMPATIBLE_ARG;
                return arguments;
            }

            arguments.mode = COMPILED;

        } else if (strcmp(argument, "--read-char") == 0) {

            if (arguments.interpret_mode != UNSET_INTERPRET_MODE)
            {
                arguments.error = INCOMPATIBLE_ARG;
                return arguments;
            }

            arguments.interpret_mode = CHAR_FILE;
        } else if (strcmp(argument, "--read-once") == 0) {

            if (arguments.interpret_mode != UNSET_INTERPRET_MODE)
            {
                arguments.error = INCOMPATIBLE_ARG;
                return arguments;
            }

            arguments.interpret_mode = READ_ONCE;
        // } else if (ead_(strcmp(argument, "--cli") == 0) || (strcmp("-l", argument) == 0)) {

        //     if (arguments.mode != UNSET_MODE)
        //     {
        //         arguments.error = INCOMPATIBLE_ARG;
        //         return arguments;
        //     }

        //     arguments.mode = CLI_INTERPRETED;
        
        // } else if ((strcmp(argument, "--8bit") == 0) || (strcmp("-1", argument) == 0)) {

        //     arguments.cell_size = 8;

        // } else if ((strcmp(argument, "--16bit") == 0) || (strcmp("-2", argument) == 0)) {

        //     arguments.cell_size = 16;

        // } else if ((strcmp(argument, "--32bit") == 0) || (strcmp("-4", argument) == 0)) {

        //     arguments.cell_size = 32;
        // } else if ((strcmp(argument, "--compile") == 0) || (strcmp("-c", argument) == 0)) {

        //     if (arguments.mode != UNSET_MODE)
        //     {
        //         arguments.error = INCOMPATIBLE_ARG;
        //         return arguments;
        //     }

        //     arguments.mode = COMPILED;

        } else if ((strcmp(argument, "--help") == 0) || (strcmp("-h", argument) == 0)) {

            if (arguments.mode != UNSET_MODE)
            {
                arguments.error = INCOMPATIBLE_ARG;
                return arguments;
            }

            arguments.mode = HELP;

        } else if (strcmp(argument, "--return-ending-cell") == 0) {

            arguments.return_ending_cell = true;

        } else if (strcmp(argument, "--infinite-cells") == 0) {

            arguments.infinite_cells = true;

        } else {

            arguments.error = INVALID_ARG;
            return arguments;
        
        }
    }

    // Enforce default interpretation
    if (arguments.mode == UNSET_MODE)
    {
        arguments.mode = INTERPRETED;
    }

    if (arguments.mode == INTERPRETED)
    {
        // Enforce default interpretation mode
        if (arguments.interpret_mode == UNSET_INTERPRET_MODE)
        {
            arguments.interpret_mode = CHAR_FILE;
        }
    }
    

    // Check if file was set if the mode is intepreted or another mode files are nessecary for.
    if (!file_set)
    {
        if (arguments.mode == INTERPRETED || arguments.mode == PYTHON_TRANSPILE || arguments.mode == C_TRANSPILE) 
        {
            arguments.error = NO_FILE;
            return arguments;
        }
    }

    if (!arguments.specified_output_filepath)
    {
        arguments.output_filepath = "a";
    }

    
    
    arguments.error = NO_ERROR;
    return arguments;
}