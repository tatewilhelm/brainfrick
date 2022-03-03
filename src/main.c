#include <stdio.h>
#include "arguments.h"
#include "interpreter.h"


int main(int argc, char* argv[])
{ 
    struct arguments_t arguments;
    arguments = lexicalize_args(argc, argv);

    switch (arguments.error) {

        case NO_FILE:
            printf("tbf: A fatal error has occured. No file passed.\n");
            return 0;
        break;

        case UNSET_ERROR:
            printf("tbf: A fatal error has occured. Internal Unset Error.\n");
            return 0;
        break;

        case NO_ERROR:
            printf("tbf: No error has occured\n");
        break;

        case INCOMPLETE_ARG:
            printf("tbf: A fatal error has occured. Incomplete argument.\n");
            return 0;
        break;

        case INCOMPATIBLE_ARG:
            printf("tbf: A fatal error has occured. Incompatible arguments.\n");
            return 0;
        break;

        case FILE_DOESNT_EXIST:
            printf("tbf: A fatal error has occured. INput file does not exist.");
            return 0;
        break;
    }

    // Errors are out of the way, manage modes now.

    switch (arguments.mode)
    {
        case INTERPRETED:
            printf("Interpreted\n");
            return interpret(arguments);
            break;
        case COMPILED:
            printf("Compiled\n");
            break;

        case C_TRANSPILE:
            printf("C\n");
            break;

        case PYTHON_TRANSPILE:
            printf("Python\n");
            break;
        default:
            printf("Def\n");
            break;
    }

    switch (arguments.cell_size)
    {
        case 8:
            printf("8\n");
            break;
        case 16:
            printf("16\n");
            break;
        case 32:
            printf("32\n");
            break;
    }
    printf("%s\n", arguments.filepath);
}