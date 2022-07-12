cmake_minimum_required (VERSION 3.0)
project (brainfrick)

set (CMAKE_C_STANDARD 99)
include_directories(include)
add_executable(brainfrick src/main.c src/arguments.c src/interpreter.c src/python.c src/c.c src/compiler.c)

install(TARGETS brainfrick DESTINATION bin)


