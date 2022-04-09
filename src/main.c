#include <stdio.h>
#include <errno.h>
#include "arguments.h"
#include "interpreter.h"


int main(int argc, char* argv[])
{ 
    struct arguments_t arguments;
    arguments = lexicalize_args(argc, argv);


    switch (arguments.error) {

        case NO_FILE:
            printf("brainfrick: A fatal error has occured. No file passed.\n");
            return 0;
        break;

        case UNSET_ERROR:   
            printf("brainfrick: A fatal error has occured. Internal Unset Error.\n");
            return -1;
        break;

        case INCOMPLETE_ARG:
            printf("brainfrick: A fatal error has occured. Incomplete argument.\n");
            return EINVAL;
        break;

        case INVALID_ARG:
            printf("brainfrick: A fatal error has occured. Invalid argument\n");
            return EINVAL;
        break;

        case FILE_DOESNT_EXIST:
            printf("brainfrick: A fatal error has occured. Path does not exist.");
            return ENOENT;
        break;

        case PATH_IS_DIRECTORY:
            printf("brainfrick: A fatal error has occured. Path specified is a directory.\n");
            return EISDIR;
        break;
    }

    // Errors are out of the way, manage modes now.

    switch (arguments.mode)
    {
        case INTERPRETED:
            return interpret(arguments);
        case HELP:
            printf("brainfrick is a program used to interpret brainfuck programs.\n--help                Displays help menu\n--interpret           Sets brainfrick to interpret the file specified\n--returnEndingCell    Returns the ending value of the cell pointed to, instead of the standard errno.\n--infiniteCells       Unlimited amount fo cells compared to the standard 30,000\n");
            break;
    }

}