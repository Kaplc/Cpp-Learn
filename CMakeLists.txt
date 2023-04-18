cmake_minimum_required(VERSION 3.17)
project(cpp_learn C)

set(CMAKE_C_STANDARD 11)

add_executable(cpp_learn
        main.c src/calculate.c header/calculate.h src/utility.c header/utility.h src  "src/translation.c")
