#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum subject
{
    ENGLISH = 1,
    MATH = 2,
    SCIENCE = 3
} Subject;

typedef struct student_data
{
    char id[11];
    double english_score;
    double math_score;
    double science_score;
    double total_score;
    double average_score;
} Student;

typedef struct student_vector //dynamic array implementation
{
    Student *student;
    unsigned int size;
    unsigned int capacity;
} StudentVec;

void student_vec_initialize(StudentVec *student_vec);
void student_vec_grow(StudentVec *student_vec); // resize the vector, double the capacity if the vector is full
void student_vec_add(StudentVec *student_vec, Student student);
void student_vec_add_rand_data(StudentVec *student_vec, int size);
void student_vec_delete(StudentVec *student_vec, char *id);
Student student_vec_search_by_id(StudentVec *student_vec, char *id);
void student_vec_load_from_csv(StudentVec *student_vec, char *file_name);
void student_vec_save_to_csv(StudentVec *student_vec, char *file_name);
void student_vec_destroy(StudentVec *student_vec);
void student_vec_log(StudentVec *student_vec);
void student_vec_log_evaluate(StudentVec *student_vec, Student student);
void student_vec_log_top_ten_score_by_subject(StudentVec *student_vec, int subject);
void student_vec_log_top_ten_score_by_total_score(StudentVec *student_vec);
void student_vec_insertion_sort_by_id(StudentVec *student_vec);
void student_vec_merge_sort_by_id(StudentVec *student_vec, int start, int end);
void student_vec_tim_sort_by_id(StudentVec *student_vec);

Student student_set_data(char *id, double english, double math, double science);
Student student_rand_data();