#include "user_feature.h"

void print_manual()
{
    printf("input the number according to the feature:\n");
    printf("1. insert single student data, if exist, overwrite\n");
    printf("2. load from csv\n");
    printf("3. logging the student data, sorted by id\n");
    printf("4. search by specific student id, list all subject score, total score, average, rank from all subjects, rank by total score\n");
    printf("5. search top 10 score by specific subject\n");
    printf("6. search top 10 score by total score\n");
    printf("7. add, delete student data\n");
    printf("8. exit\n");
    printf("other number may be features for debug UwU\n");
    printf("input the number: \n");
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

        printf("allocated size: %lfMB\n", student_vec.capacity * sizeof(Student) / 1048576.0);

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
        case SEARCH_BY_ID_EVALUATE:
            feature_search_by_id_evaluate(&student_vec);
            break;
        case SEARCH_TOP_TEN_SPECIFIC_SUBJECT:
            feature_search_top_ten_score_by_subject(&student_vec);
            break;
        case SEARCH_TOP_TEN_TOTAL_SCORE:
            feature_search_top_ten_score_by_total_score(&student_vec);
            break;
        case ADD_DELETE_STUDENT:
            feature_add_delete_student_data(&student_vec);
            break;
        case EXIT:
            exit = 1;
            student_vec_destroy(&student_vec);
            break;

            /// debug features
        case INSERT_RAND_DATA:
            feature_add_rand_data(&student_vec);
            break;
        case SAVE_CSV:
            feature_save_csv(&student_vec);
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

    user_insert_student_id(student_id);
    user_insert_student_score(&english, &math, &science);

    // start time
    clock_t start = clock();

    Student new_student = student_set_data(student_id, english, math, science);

    Student search_student = student_vec_search_by_id(student_vec, student_id);

    if (search_student.id[0] != '\0')
    {
        // print student
        printf("Overwrite student data, the origin student data was:\n");
        printf("student id: %s\n", search_student.id);
        printf("english: %lf\n", search_student.english_score);
        printf("math: %lf\n", search_student.math_score);
        printf("science: %lf\n", search_student.science_score);
    }
    else
    {
        printf("So, insert new student id: %s", new_student.id);
    }

    student_vec_add(student_vec, new_student);
    student_vec_tim_sort_by_id(student_vec);
    student_vec_delete_duplicate_id(student_vec);

    // end time
    clock_t end = clock();
    printf("seconds elapsed: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void feature_load_from_csv(StudentVec *student_vec)
{
    char file_name[255];
    user_insert_file_name(file_name);

    // start time
    clock_t start = clock();

    student_vec_load_from_csv(student_vec, file_name);
    student_vec_tim_sort_by_id(student_vec);
    student_vec_delete_duplicate_id(student_vec);

    // end time
    clock_t end = clock();
    printf("seconds elapsed: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void feature_log_student_data_by_id(StudentVec *student_vec)
{
    // start time
    clock_t start = clock();

    student_vec_log(student_vec);

    // end time
    clock_t end = clock();
    printf("seconds elapsed: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void feature_search_by_id_evaluate(StudentVec *student_vec)
{
    char student_id[10 + 1];
    user_insert_student_id(student_id);

    // start time
    clock_t start = clock();

    Student student = student_vec_search_by_id(student_vec, student_id);
    student_vec_log_evaluate(student_vec, student);

    // end time
    clock_t end = clock();
    printf("seconds elapsed: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void feature_search_top_ten_score_by_subject(StudentVec *student_vec)
{
    Subject subject;
    int subject_id = 0;
    subject_id = (int)subject;
    StudentVec top_ten_student_vec[10];

    printf("Insert subject:\n");
    printf("1. english\n");
    printf("2. math\n");
    printf("3. science\n");

    scanf("%d", &subject_id);

    // start time
    clock_t start = clock();

    switch (subject_id)
    {
    case ENGLISH:
        student_vec_log_top_ten_score_by_subject(student_vec, ENGLISH);
        break;

    case MATH:
        student_vec_log_top_ten_score_by_subject(student_vec, MATH);
        break;

    case SCIENCE:
        student_vec_log_top_ten_score_by_subject(student_vec, SCIENCE);
        break;

    default:
        printf("input error\n");
        break;
    }

    // end time
    clock_t end = clock();
    printf("seconds elapsed: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);

    return;
}

void feature_search_top_ten_score_by_total_score(StudentVec *student_vec)
{
    // start time
    clock_t start = clock();

    student_vec_log_top_ten_score_by_total_score(student_vec);

    // end time
    clock_t end = clock();
    printf("seconds elapsed: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void feature_add_delete_student_data(StudentVec *student_vec)
{
    int choice = 0;
    double english, math, science;
    char student_id[10 + 1];

    printf("press 1 to add student, ");
    printf("press 2 to delete student\n");

    scanf("%d", &choice);

    if (choice == 1)
    {
        user_insert_student_id(student_id);
        user_insert_student_score(&english, &math, &science);

        // start time
        clock_t start = clock();

        Student new_student = student_set_data(student_id, english, math, science);
        student_vec_add(student_vec, new_student);
        student_vec_tim_sort_by_id(student_vec);
        student_vec_delete_duplicate_id(student_vec);

        // end time
        clock_t end = clock();
        printf("seconds elapsed: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
    else if (choice == 2)
    {
        user_insert_student_id(student_id);

        // start time
        clock_t start = clock();

        student_vec_delete(student_vec, student_id);

        // end time
        clock_t end = clock();
        printf("seconds elapsed: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    }
}

void feature_add_rand_data(StudentVec *student_vec)
{
    int num = 0;
    printf("insert number of students want to generate: ");
    scanf("%d", &num);

    // start time
    clock_t start = clock();

    student_vec_add_rand_data(student_vec, num);
    // student_vec_merge_sort_by_id(student_vec, 0, student_vec->size - 1);
    student_vec_tim_sort_by_id(student_vec);
    student_vec_delete_duplicate_id(student_vec);

    // end time
    clock_t end = clock();
    printf("seconds elapsed: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void feature_save_csv(StudentVec *student_vec)
{
    // current time as file name
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char time_str[255];
    strftime(time_str, 255, "%Y_%m_%d_%H_%M_%S", tm);

    printf("saving csv...\n");
    student_vec_save_to_csv(student_vec, time_str);
    printf("done\n");
}