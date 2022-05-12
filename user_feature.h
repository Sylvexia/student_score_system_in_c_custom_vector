#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "database.h"

enum FEATURES
{
    INSERT_SINGLE_STUDENT=1,
    LOAD_CSV=2,
    LOG_SORTED_BY_ID=3,
    SEARCH_BY_ID=4,
    SEARCH_TOP_TEN_SPCIFIC_SUBJECT=5,
    SEARCH_TOP_TEN_TOTAL_SCORE=6,
    ADD_DELETE_STUDENT=7,
    EXIT=8
};

void print_manual();

void user_insert_studuent_id(char* student_id);
void user_insert_student_score(double* english, double* math, double* science);
void user_insert_file_name(char* file_name);
void user_interface();

void feature_insert_student_data(StudentVec *student_vec);
void feature_load_from_csv(StudentVec *student_vec);
void feature_log_student_data_by_id(StudentVec *student_vec);
void feature_search_by_id(StudentVec *student_vec);
void feature_search_top_ten_score_by_subject(StudentVec *student_vec);
void feature_search_top_ten_score_by_total_score(StudentVec *student_vec);
void feature_add_delete_student_data(StudentVec *student_vec);
