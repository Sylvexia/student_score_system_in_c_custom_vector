cmake_minimum_required(VERSION 3.0.0)
project(student_score_array C)
add_library(
    database_lib
    database.c
    database.h
)

add_library(
    user_feature_lib
    user_feature.c
    user_feature.h
)

add_executable(student_score_array main.c)

target_link_libraries(user_feature_lib database_lib)

target_link_libraries(student_score_array user_feature_lib)