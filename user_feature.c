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

char *user_insert_student_id()
{
    char *student_id = malloc(sizeof(char) * (10 + 1));

    printf("Insert student id:\n");
    scanf("%s", student_id);

    return student_id;
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

void user_interface()
{
    int exit = 0;
    StudentVec student_vec;
    student_vec_initialize(&student_vec);  //segmentation fault

    while (!exit)
    {
        enum FEATURES feature = 0;
        int feature_id = (int)feature;

        print_manual();
        scanf("%d", &feature_id);

        switch (feature_id)
        {
        case INSERT_SINGLE_STUDENT:
            insert_student_data(&student_vec);
            break;
        case LOAD_CSV:
            load_from_csv();
            break;
        case LOG_SORTED_BY_ID:
            log_student_data_by_id();
            break;
        case SEARCH_BY_ID:
            search_by_id();
            break;
        case SEARCH_TOP_TEN_SPCIFIC_SUBJECT:
            search_top_ten_score_by_subject();
            break;
        case SEARCH_TOP_TEN_TOTAL_SCORE:
            search_top_ten_score_by_total_score();
            break;
        case ADD_DELETE_STUDENT:
            add_delete_student_data();
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

void insert_student_data(StudentVec *student_vec)
{
    char *student_id = NULL;
    double english, math, science = 0;
    Student new_student;

    student_id = user_insert_student_id();
    user_insert_student_score(&english, &math, &science);
    new_student.english_score = english;
    new_student.math_score = math;
    new_student.science_score = science;
    strcpy(new_student.id, student_id);

    student_vec_insert(student_vec, new_student);
    free(student_id);
    //student_vec_log(student_vec);
}

void load_from_csv()
{
    char *file_name;
    printf("Insert file name:\n");
    scanf("%s", &file_name);
}

void log_student_data_by_id()
{
    printf("Student data by id:\n");
}

void search_by_id()
{
    char *student_id;
    printf("Insert student id:\n");
}

void search_top_ten_score_by_subject()
{
    printf("Insert subject:\n");
}

void search_top_ten_score_by_total_score()
{
    printf("Top 10 total score:\n");
}

void add_delete_student_data()
{
    printf("press 1 to add student, ");
    printf("press 2 to delete student\n");
}
