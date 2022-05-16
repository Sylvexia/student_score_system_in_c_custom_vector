#include "database.h"

void student_vec_initialize(StudentVec *student_vec)
{
    student_vec->student = NULL;
    student_vec->size = 0;
    student_vec->capacity = 0;
}

void student_vec_grow(StudentVec *student_vec)
{
    Student *new_student;
    unsigned int new_capacity;

    new_capacity = student_vec->capacity * 2 + 1;
    new_student = (Student *)malloc(sizeof(Student) * new_capacity);

    if (new_student == NULL)
    {
        printf("malloc error\n");
        exit(1);
    }

    for (unsigned int i = 0; i < student_vec->size; i++)
    {
        new_student[i] = student_vec->student[i];
    }

    free(student_vec->student);
    student_vec->student = new_student;
    student_vec->capacity = new_capacity;
}

void student_vec_add(StudentVec *student_vec, Student student)
{
    //if student.id exist in student_vec, overwrite student data
    // for (unsigned int i = 0; i < student_vec->size; i++)
    // {
    //     if (strcmp(student_vec->student[i].id, student.id) == 0)
    //     {
    //         student_vec->student[i].english_score = student.english_score;
    //         student_vec->student[i].math_score = student.math_score;
    //         student_vec->student[i].science_score = student.science_score;
    //         student_vec->student[i].total_score = student.total_score;
    //         student_vec->student[i].average_score = student.average_score;
    //         return;
    //     }
    // }

    if (student_vec->size >= student_vec->capacity)
    {
        student_vec_grow(student_vec);
    }

    student_vec->student[student_vec->size] = student;
    student_vec->size++;
}

void student_vec_add_rand_data(StudentVec *student_vec, int size)
{
    for (int i = 0; i < size; i++)
    {
        Student student = student_rand_data();
        student_vec_add(student_vec, student);
    }
}

void student_vec_delete(StudentVec *student_vec, char *id)
{
    for (unsigned int i = 0; i < student_vec->size; i++)
    {
        if (strcmp(student_vec->student[i].id, id) == 0)
        {
            for (unsigned int j = i; j < student_vec->size - 1; j++)
            {
                //student_vec->student[j] = student_vec->student[j + 1];
                strcpy(student_vec->student[j].id, student_vec->student[j + 1].id);
                student_vec->student[j].english_score = student_vec->student[j + 1].english_score;
                student_vec->student[j].math_score = student_vec->student[j + 1].math_score;
                student_vec->student[j].science_score = student_vec->student[j + 1].science_score;
                student_vec->student[j].total_score = student_vec->student[j + 1].total_score;
                student_vec->student[j].average_score = student_vec->student[j + 1].average_score;
            }

            student_vec->size--;
            break;
        }
    }
}

Student student_vec_search_by_id(StudentVec *student_vec, char *id)
{
    //maybe hashing student_id is better

    Student student;
    int found = 0;

    for (unsigned int i = 0; i < student_vec->size; i++)
    {
        if (strcmp(student_vec->student[i].id, id) == 0)
        {
            student = student_vec->student[i];
            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        student.id[0] = '\0';
        printf("student not found\n");
    }

    return student;
}

void student_vec_load_from_csv(StudentVec *student_vec, char *file_name)
{
    FILE *fp;
    char line[255];
    char *token_id, *token_english, *token_math, *token_science;
    Student new_student;

    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("file open error\n");
        exit(1);
    }

    while (fgets(line, 255, fp) != NULL)
    {
        token_id = strtok(line, ",");

        if (token_id[0] != 'K')
        {
            continue;
        }

        token_english = strtok(NULL, ",");

        token_math = strtok(NULL, ",");

        token_science = strtok(NULL, ",");

        new_student = student_set_data(token_id, atof(token_english), atof(token_math), atof(token_science));

        student_vec_add(student_vec, new_student);
    }

    fclose(fp);

    printf("loaded data:\n");
    student_vec_log(student_vec);
}

void student_vec_save_to_csv(StudentVec *student_vec, char *file_name)
{
    FILE *fp;
    char line[255];
    char *token_id;
    double token_english, token_math, token_science;

    fp = fopen(file_name, "w");

    if (fp == NULL)
    {
        printf("file open error\n");
        exit(1);
    }

    for (unsigned int i = 0; i < student_vec->size; i++)
    {
        token_id = student_vec->student[i].id;
        token_english = student_vec->student[i].english_score;
        token_math = student_vec->student[i].math_score;
        token_science = student_vec->student[i].science_score;

        sprintf(line, "%s,%lf,%lf,%lf\n", token_id, token_english, token_math, token_science);
        fputs(line, fp);
    }

    fclose(fp);
}

void student_vec_destroy(StudentVec *student_vec)
{
    free(student_vec->student);
}

void student_vec_log(StudentVec *student_vec)
{
    printf("Student id/English/Math/Science:\n");

    for (unsigned int i = 0; i < student_vec->size; i++)
    {
        printf("%s %lf %lf %lf\n", student_vec->student[i].id,
               student_vec->student[i].english_score,
               student_vec->student[i].math_score,
               student_vec->student[i].science_score);
    }

    printf("Current size: %d\n", student_vec->size);
}

void student_vec_log_evaluate(StudentVec *student_vec, Student student)
{
    int english_rank = 1;
    int math_rank = 1;
    int science_rank = 1;
    int total_score_rank = 1;

    for (unsigned int i = 0; i < student_vec->size; i++)
    {
        if (student_vec->student[i].english_score > student.english_score)
        {
            english_rank++;
        }
        if (student_vec->student[i].math_score > student.math_score)
        {
            math_rank++;
        }
        if (student_vec->student[i].science_score > student.science_score)
        {
            science_rank++;
        }
        if (student_vec->student[i].total_score > student.total_score)
        {
            total_score_rank++;
        }
    }

    student_vec_log(student_vec);
    printf("english rank: %d\n", english_rank);
    printf("math rank: %d\n", math_rank);
    printf("science rank: %d\n", science_rank);
    printf("total score rank: %d\n", total_score_rank);
    printf("\n");
}

void student_vec_log_top_ten_score_by_subject(StudentVec *student_vec, int subject)
{
    unsigned int k = 10;
    unsigned int used_index[k];

    switch (subject)
    {
    case ENGLISH:
        printf("English top 10:\n");
        break;

    case MATH:
        printf("Math top 10:\n");
        break;

    case SCIENCE:
        printf("Science top 10:\n");
        break;
    }

    for (unsigned int i = 0; i < k; i++)
    {
        double max_score = 0;
        unsigned int max_index = 0;

        for (unsigned int j = 0; j < student_vec->size; j++)
        {
            unsigned int continue_flag = 0;

            for (unsigned int l = 0; l < k; l++) //if find jth largest, skip
            {
                if (used_index[l] == j)
                {
                    continue_flag = 1;
                }
            }

            if (continue_flag == 1)
            {
                continue;
            }

            switch (subject)
            {

            case ENGLISH:
                if (max_score < student_vec->student[j].english_score)
                {
                    max_score = student_vec->student[j].english_score;
                    max_index = j;
                }
                break;

            case MATH:
                if (max_score < student_vec->student[j].math_score)
                {
                    max_score = student_vec->student[j].math_score;
                    max_index = j;
                }
                break;

            case SCIENCE:
                if (max_score < student_vec->student[j].science_score)
                {
                    max_score = student_vec->student[j].science_score;
                    max_index = j;
                }
                break;
            }
        }
        used_index[i] = max_index;

        printf("rank: %d, id: %s, score: %lf\n", i + 1, student_vec->student[max_index].id, max_score);
    }
}

void student_vec_log_top_ten_score_by_total_score(StudentVec *student_vec)
{
    unsigned int k = 10;
    unsigned int used_index[k];

    printf("Total score top 10:\n");

    for (unsigned int i = 0; i < k; i++)
    {
        double max_score = 0;
        unsigned int max_index = 0;

        for (unsigned int j = 0; j < student_vec->size; j++)
        {
            unsigned int continue_flag = 0;

            for (unsigned int l = 0; l < k; l++) //if find jth largest, skip
            {
                if (used_index[l] == j)
                {
                    continue_flag = 1;
                }
            }

            if (continue_flag == 1)
            {
                continue;
            }

            if (max_score < student_vec->student[j].total_score)
            {
                max_score = student_vec->student[j].total_score;
                max_index = j;
            }
        }
        used_index[i] = max_index;

        printf("rank: %d, id: %s, score: %lf\n", i + 1, student_vec->student[max_index].id, max_score);
    }
}

void student_vec_insertion_sort_by_id(StudentVec *student_vec)
{
    //insertion sort by id
    Student temp_student;
    int i, j; //j could be negative

    for (i = 1; i < student_vec->size; i++)
    {
        temp_student = student_vec->student[i];
        j = i - 1;

        while (j >= 0 && strcmp(temp_student.id,
                                student_vec->student[j].id) <= 0)
        {
            student_vec->student[j + 1] = student_vec->student[j];
            j--;
        }

        student_vec->student[j + 1] = temp_student;
    }
}

void student_vec_merge_sort_by_id(StudentVec *student_vec, int start, int end)
{
    //merge sort by id
    int mid;
    if (start < end)
    {
        mid = (start + end) / 2;
        student_vec_merge_sort_by_id(student_vec, start, mid);
        student_vec_merge_sort_by_id(student_vec, mid + 1, end);
        student_vec_merge_by_id(student_vec, start, mid, end);
    }
}

void student_vec_merge_by_id(StudentVec *student_vec, int start, int mid, int end)
{
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    Student *L = malloc(n1 * sizeof(Student));
    Student *R = malloc(n2 * sizeof(Student));
    //Student L[n1], R[n2];

    for (i = 0; i < n1; i++)
    {
        L[i] = student_vec->student[start + i];
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = student_vec->student[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = start;

    while (i < n1 && j < n2)
    {
        if (strcmp(L[i].id, R[j].id) <= 0)
        {
            student_vec->student[k] = L[i];
            i++;
        }
        else
        {
            student_vec->student[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        student_vec->student[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        student_vec->student[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void student_vec_tim_sort_by_id(StudentVec *student_vec)
{
    //tim sort
}

Student student_set_data(char *id, double english, double math, double science)
{
    Student student;

    if (id[0] != 'K')
    {
        printf("not a valid id\n");
        exit(1);
    }

    student.english_score = english;
    student.math_score = math;
    student.science_score = science;
    student.total_score = english + math + science;
    student.average_score = student.total_score / 3.0;
    strcpy(student.id, id);

    return student;
}

Student student_rand_data()
{
    double rand_english = (rand() % 1000000) / 1000.0;
    double rand_math = (rand() % 1000000) / 1000.0;
    double rand_science = (rand() % 1000000) / 1000.0;
    double rand_total = rand_english + rand_math + rand_science;
    double rand_average = rand_total / 3.0;

    char rand_id[10 + 1];

    rand_id[0] = 'K';

    for (int i = 1; i <= 9; i++)
    {
        rand_id[i] = rand() % 10 + '0';
    }

    rand_id[10] = '\0';

    Student student = student_set_data(rand_id, rand_english, rand_math, rand_science);
    return student;
}