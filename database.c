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
}