cmake_minimum_required(VERSION 3.16)
project(minicalc C)

set(CMAKE_C_STANDARD 11)

add_executable(minicalc main.c arq.c arq.h lexer.c lexer.h parser.c parser.h var.c var.h)
add_executable(lexertest lexertest.c arq.c arq.h lexer.c lexer.h)

target_link_libraries(minicalc m)
