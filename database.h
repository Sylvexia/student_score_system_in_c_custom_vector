#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student_data
{
    double english_score;
    double math_score;
    double science_score;
    char id[11];
} Student;

typedef struct student_vector
{
    Student *student;
    unsigned int size;
    unsigned int capacity;
} StudentVec;

void student_vec_initialize(StudentVec *student_vec);
void student_vec_resize(StudentVec *student_vec);
void student_vec_insert(StudentVec *student_vec, Student student);
void student_vec_delete(StudentVec *student_vec, char *id);
void student_vec_destroy(StudentVec *student_vec);
void student_vec_log(StudentVec *student_vec);