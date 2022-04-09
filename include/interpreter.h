#ifndef INTERPRETER_H
#define INTERPRETER_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "arguments.h"

#define STD_CELL_SIZE 30000
int interpret(struct arguments_t arguments);

#endif