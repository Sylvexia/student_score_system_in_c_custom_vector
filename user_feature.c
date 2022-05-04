#include "user_feature.h"

void print_manual()
{
    printf("input the number according to the feature:\n");
    printf("1. insert single student data, if exist, overwrite\n");
    printf("2. load from csv\n");
    printf("3. logging the student data, sorted by id\n");
    printf("4. search by specific studnt id, list all subject score, total score, average, rank from all subjects, rank by total score\n");
    printf("5. search top 10 score by specific subject");
    printf("6. search top 10 score by total score\n");
    printf("7. add, delete student data\n");
    printf("8. exit\n");
    printf("input the number: ");
}

void user_insert_student_id(char *student_id)
{
    printf("Insert student id:\n");
    scanf("%s", student_id);

    return;
}

void user_insert_student_score(double *english, double *math, double *science)
{
    printf("Insert student score:\n");

    printf("english: ");
    scanf("%lf", english);
    printf("math: ");
    scanf("%lf", math);
    printf("science: ");
    scanf("%lf", science);

    return;
}

void user_insert_file_name(char *file_name)
{
    printf("Insert file name:\n");
    scanf("%s", file_name);

    return;
}

void user_interface()
{
    int exit = 0;
    StudentVec student_vec;
    student_vec_initialize(&student_vec);

    while (!exit)
    {
        enum FEATURES feature = 0;
        int feature_id = (int)feature;

        print_manual();
        scanf("%d", &feature_id);

        switch (feature_id)
        {
        case INSERT_SINGLE_STUDENT:
            feature_insert_student_data(&student_vec);
            break;
        case LOAD_CSV:
            feature_load_from_csv(&student_vec);
            break;
        case LOG_SORTED_BY_ID:
            feature_log_student_data_by_id(&student_vec);
            break;
        case SEARCH_BY_ID:
            feature_search_by_id();
            break;
        case SEARCH_TOP_TEN_SPCIFIC_SUBJECT:
            feature_search_top_ten_score_by_subject();
            break;
        case SEARCH_TOP_TEN_TOTAL_SCORE:
            feature_search_top_ten_score_by_total_score();
            break;
        case ADD_DELETE_STUDENT:
            feature_add_delete_student_data();
            break;
        case EXIT:
            exit = 1;
            break;
        default:
            printf("input error\n");
            break;
        }
    }
}

void feature_insert_student_data(StudentVec *student_vec)
{
    char student_id[10 + 1];
    double english, math, science = 0;
    Student new_student;

    user_insert_student_id(student_id);
    user_insert_student_score(&english, &math, &science);

    new_student.english_score = english;
    new_student.math_score = math;
    new_student.science_score = science;
    strcpy(new_student.id, student_id);

    student_vec_insert(student_vec, new_student);
    student_vec_log(student_vec);
}

void feature_load_from_csv(StudentVec *student_vec)
{
    char file_name[255];
    user_insert_file_name(&file_name);

    student_vec_load_from_csv(student_vec, file_name);
}

void feature_log_student_data_by_id(StudentVec *student_vec)
{
    //student_vec_merge_sort_by_id(student_vec);
    student_vec_insertion_sort_by_id(student_vec);
    student_vec_log(student_vec);
}

void feature_search_by_id()
{
    char student_id[10 + 1];
    user_insert_student_id(student_id);
}

void feature_search_top_ten_score_by_subject()
{
    printf("Insert subject:\n");
}

void feature_search_top_ten_score_by_total_score()
{
    printf("Top 10 total score:\n");
}

void feature_add_delete_student_data()
{
    printf("press 1 to add student, ");
    printf("press 2 to delete student\n");
}
