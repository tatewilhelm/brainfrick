cmake_minimum_required (VERSION 2.8.11)
project (brainfrick)


include_directories(include)
add_executable(brainfrick src/main.c src/arguments.c src/interpreter.c)


