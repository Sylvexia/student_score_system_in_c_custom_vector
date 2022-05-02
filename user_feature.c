#include "user_feature.h"

void insert_student_data()
{
    char *student_id;
    printf("Insert student id:\n");
    scanf("%s", &student_id);
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

void user_interface()
{
    int exit = 0;
    Student student[100];

    while (!exit)
    {
        enum FEATURES feature;

        print_manual();
        scanf("%d", &feature);

        switch (feature)
        {
        case INSERT_SINGLE_STUDENT:
            insert_student_data();
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
