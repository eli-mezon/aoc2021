#include <unity.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

#define MAX(a,b) (a)>=(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) (a < 0 )?-a:a

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

#define MAX_X (40)
#define MAX_Y (40)

int64_t paper[MAX_X*MAX_Y] = {0};

typedef struct 
{
    int64_t x;
    int64_t y;
} Dot_t;

typedef struct 
{
    char aix;
    int64_t value;
} Fold_t;

void print_paper(int64_t * buffer, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
        printf("%c", buffer[idx]? '1' : ' ');
        if (idx % MAX_X == (MAX_X -1)) printf("\n");
    }
    printf("\n");
}
void print_dots(Dot_t * buffer, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
            printf("%ld, %ld", buffer[idx].x, buffer[idx].y);
        printf("\n");
    }
    printf("\n");
}
void process_dots(Dot_t * buffer, int64_t size, int64_t * result)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
        result[buffer[idx].x * MAX_X + buffer[idx].y] = 1;
    }
    printf("\n");
}
int64_t count_dots(int64_t * buffer, int64_t size)
{
    int64_t sum = 0;
    for (int64_t idx = 0; idx < size; idx++)
    {
        if (buffer[idx] > 0) 
        {
            sum += 1;
        }
    }
    return sum;
}
int64_t fold_x(Dot_t * dot, int64_t value)
{
   dot->x = 2 * value - dot->x;
}
int64_t process_fold_x(Dot_t * buffer, int64_t size, int64_t value)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
        if (buffer[idx].x >= 0) 
        {
            if (buffer[idx].x > value)
            {
                fold_x(&buffer[idx], value);
            }
            else if (buffer[idx].x == value)
            {
                buffer[idx].x = -1;
            }

        }
    }
}
int64_t fold_y(Dot_t * dot, int64_t value)
{
   dot->y = 2 * value - dot->y;
}
int64_t process_fold_y(Dot_t * buffer, int64_t size, int64_t value)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
        if (buffer[idx].x >= 0 && buffer[idx].y >= value) 
        {
            if (buffer[idx].y > value)
            {
                fold_y(&buffer[idx], value);
            }
            else if (buffer[idx].y == value)
            {
                buffer[idx].x = -1;
            }
        }
    }
}
void print_folds(Fold_t * buffer, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
            printf("%c, %ld", buffer[idx].aix, buffer[idx].value);
        printf("\n");
    }
    printf("\n");
}


int64_t sonar_sweep_day6_1(Dot_t * data, int64_t size, Fold_t * fold, int64_t foldsize)
{
 //   print_dots(data, size);
//    print_folds(fold, foldsize);

    for (int64_t idx = 0; idx < foldsize; idx++)
    {
        if (fold[idx].aix == 'x')
        {
        process_fold_x(data, size, fold[idx].value);
        }
        else
        {
        process_fold_y(data, size, fold[idx].value);
        }
    }
    process_dots(data, size, paper);

    print_paper(paper, ARRAY_SIZE(paper));
    return count_dots(paper, ARRAY_SIZE(paper));
}

void test_sonar_sweep_day6_example(void)
{
    Dot_t test_set[] =
    {
#       include "task_day13.inc"
    };

    Fold_t fold_set[] =
    {
#if 0     
{'y',7},
{'x',5},
#else
{'x',655},
{'y',447},
{'x',327},
{'y',223},
{'x',163},
{'y',111},
{'x',81},
{'y',55},
{'x',40},
{'y',27},
{'y',13},
{'y',6},
#endif
    };

    int64_t result = sonar_sweep_day6_1(test_set, ARRAY_SIZE(test_set), fold_set, ARRAY_SIZE(fold_set));
    TEST_ASSERT_EQUAL(0, result);
}

/*
fold along y=7
fold along x=5
*/

/*
fold along x=655
fold along y=447
fold along x=327
fold along y=223
fold along x=163
fold along y=111
fold along x=81
fold along y=55
fold along x=40
fold along y=27
fold along y=13
fold along y=6
*/


/*

0,14 -> 0,0  | 2*7 - y
0,13 -> 0,1  | 2*7 - 6
*/