#ifndef INTERPRETER_H
#define INTERPRETER_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include "arguments.h"


int interpret(struct arguments_t arguments);

#endif