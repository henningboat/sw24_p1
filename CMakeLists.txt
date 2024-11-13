cmake_minimum_required(VERSION 3.29)
project(p1 C)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/model_data/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/model_data/)

set(CMAKE_C_STANDARD 11)

 add_executable(p1 main.c structs.h
         model_input.c
         model_input.h)
