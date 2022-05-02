#pragma once

#include <stdio.h>
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

void insert_student_data();
void load_from_csv();
void log_student_data_by_id();
void search_by_id();
void search_top_ten_score_by_subject();
void search_top_ten_score_by_total_score();
void add_delete_student_data();

void print_manual();
void user_interface();
