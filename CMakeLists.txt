cmake_minimum_required (VERSION 2.8.11)
project (tbf)


include_directories(include)

add_executable(tbf src/main.c src/arguments.c src/interpreter.c)    

