#include "compiler.h"
#include "constants.h"

int compile(struct arguments_t arguments)
{
    struct arguments_t transpile_arguments = arguments;
    transpile_arguments.output_filepath = "temp.c";
    transpile_arguments.specified_output_filepath = true;
    int transpile_error = transpile_c(transpile_arguments);

    if (transpile_error != 0)
    {
        return transpile_error;
    }

    if (!arguments.specified_output_filepath)
    {
        arguments.output_filepath = "a.out";
    }
    char compile_command[MAXIMUM_COMPILER_COMMAND_LENGTH] = "";
    strcat(compile_command, C_COMPILER);
    strcat(compile_command, " ");
    strcat(compile_command, transpile_arguments.output_filepath);
    strcat(compile_command, " ");
    strcat(compile_command, C_COMPILER_OUTPUT_FILE_FLAG);
    strcat(compile_command, " ");
    strcat(compile_command, arguments.output_filepath);
    strcat(compile_command, " ");
    strcat(compile_command, C_COMPILER_FLAGS);
    strcat(compile_command, " ");
    strcat(compile_command, SILENCE_COMPILER_OUTPUT);
    system(compile_command);

    remove("temp.c");

    return 0;
}