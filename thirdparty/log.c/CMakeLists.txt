cmake_minimum_required(VERSION 3.22.1)
project(log.c LANGUAGES C)

add_library(${PROJECT_NAME} ./src/log.c ./src/log.c)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
target_include_directories(${PROJECT_NAME} PUBLIC src/)
target_compile_options(${PROJECT_NAME} PUBLIC "-DLOG_USE_COLOR")

