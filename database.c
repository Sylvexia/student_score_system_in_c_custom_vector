#include "database.h"

void student_vec_initialize(StudentVec *student_vec)
{
    student_vec->student = NULL;
    student_vec->size = 0;
    student_vec->capacity = 0;
}

void student_vec_resize(StudentVec *student_vec)
{
    Student *new_student;
    unsigned int new_capacity;

    new_capacity = student_vec->capacity * 2;
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

void student_vec_insert(StudentVec *student_vec, Student student)
{
    if (student_vec->size == student_vec->capacity)
    {
        student_vec_resize(student_vec);
    }

    student_vec->student[student_vec->size] = student;
    student_vec->size++;
}

void student_vec_delete(StudentVec *student_vec, char *id)
{
    for (unsigned int i = 0; i < student_vec->size; i++)
    {
        if (strcmp(student_vec->student[i].id, id) == 0)
        {
            for (unsigned int j = i; j < student_vec->size - 1; j++)
            {
                student_vec->student[j] = student_vec->student[j + 1];
            }

            student_vec->size--;
            break;
        }
    }
}

void student_vec_load_from_csv(StudentVec *student_vec, char *file_name)
{
    FILE *fp;
    char line[255];
    char *token;
    Student new_student;

    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        printf("file open error\n");
        exit(1);
    }

    while (fgets(line, 255, fp) != NULL)
    {
        token = strtok(line, ",");

        if (token[0] != 'K')
        {
            continue;
        }

        strcpy(new_student.id, token);

        token = strtok(NULL, ",");
        new_student.english_score = atof(token);

        token = strtok(NULL, ",");
        new_student.math_score = atof(token);

        token = strtok(NULL, ",");
        new_student.science_score = atof(token);

        student_vec_insert(student_vec, new_student);
    }

    fclose(fp);

    printf("loaded data:\n");
    student_vec_log(student_vec);
}

void student_vec_destroy(StudentVec *student_vec)
{
    free(student_vec->student);
}

void student_vec_log(StudentVec *student_vec)
{
    for (unsigned int i = 0; i < student_vec->size; i++)
    {
        printf("%s %lf %lf %lf\n", student_vec->student[i].id,
               student_vec->student[i].english_score,
               student_vec->student[i].math_score,
               student_vec->student[i].science_score);
    }

    printf("Current size: %d\n", student_vec->size);
}

void student_vec_insertion_sort_by_id(StudentVec *student_vec)
{
    //insertion sort by id
    Student temp_student;
    int i, j;   //j could be negative

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