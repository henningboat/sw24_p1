cmake_minimum_required(VERSION 3.29)
project(p1 C)

set(CMAKE_C_STANDARD 11)

 add_executable(p1 main.c structs.h
         model_input.c
         model_input.h
         path_finding.c
         path_finding.h
         travel_time.c
         simulation_loop.c
         simulation_loop.h)

add_custom_target(copy_model_data ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/model_data"
        "${CMAKE_CURRENT_BINARY_DIR}/model_data"
)

add_dependencies(p1 copy_model_data)
#add_compile_definitions(DEBUG_PRINT)