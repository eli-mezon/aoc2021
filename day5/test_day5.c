#include <unity.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

typedef struct {
    int64_t point1[2];
    int64_t point2[2];
} Line_t;

#define FIELD_SIZE (1000)
#define MAX(a,b) (a)>=(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) ((a) < 0 )?(-a):(a)
static int64_t field[FIELD_SIZE][FIELD_SIZE] = {0};

bool line_is_of(Line_t * line)
{
    return ((line->point1[0] == line->point2[0]) || (line->point1[1] == line->point2[1]) ||
            (ABS(line->point1[0] - line->point2[0]) == ABS(line->point1[1] - line->point2[1])));
}

void print_filed(void)
{
    for (int64_t idx = 0; idx < FIELD_SIZE; idx++)
    {
        for (int64_t jdx = 0; jdx < FIELD_SIZE; jdx++)
        {
            printf("%ld, ", field[idx][jdx]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void fill_filed(Line_t * line)
{
    if (line->point1[0] == line->point2[0])
    {
        int64_t max = MAX(line->point1[1], line->point2[1]);
        int64_t min = MIN(line->point1[1], line->point2[1]);
        for (int64_t idx = min; idx <= max; idx++)
        {
            field[line->point1[0]][idx] += 1;
        }
    }
    else if (line->point1[1] == line->point2[1])
    {
        int64_t max = MAX(line->point1[0], line->point2[0]);
        int64_t min = MIN(line->point1[0], line->point2[0]);
        for (int64_t idx = min; idx <= max; idx++)
        {
            field[idx][line->point2[1]] += 1;
        }
    }
    else
    {
        int64_t max = MAX(line->point1[0],line->point2[0]);
        int64_t min = MIN(line->point1[0],line->point2[0]);
        int64_t num = max - min;
//        printf("{%ld,%ld} -> %ld\n",  max, min, num);
        int64_t aix_0_sign = ((line->point1[0] - line->point2[0]) < 0) ? 1 : -1;
        int64_t aix_1_sign = ((line->point1[1] - line->point2[1]) < 0) ? 1 : -1;
//        printf("{%ld,%ld} -> {%ld,%ld}\n", line->point1[0], line->point1[1], line->point2[0], line->point2[1]);

//        printf("{%ld,%ld,%ld}\n", num, aix_0_sign, aix_1_sign);

        for (int64_t idx = 0; idx <= num; idx++)
        {
                field[line->point1[0] + idx * aix_0_sign][line->point1[1] + idx * aix_1_sign] += 1;
        }
        printf("\n");
    }

//    print_filed();
}
int64_t sonar_sweep_day5_1(Line_t * data, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
        if (line_is_of(&data[idx]))
        {
            fill_filed(&data[idx]);
            printf("%ld:%ld\n", data[idx].point1[0], data[idx].point2[1]);
        }
    }

    int64_t sum = 0;
    for (int64_t idx = 0; idx < FIELD_SIZE; idx++)
    {
        for (int64_t jdx = 0; jdx < FIELD_SIZE; jdx++)
        {
//            printf("%ld, ", field[idx][jdx]);
			if (field[idx][jdx] >= 2)
			{
				sum += 1;
			}
        }
//        printf("\n");
    }
//    print_filed();
    return sum;
}

void test_sonar_sweep_day5_example(void)
{
    Line_t test_set[] =
    {
#       include "task_day5.inc"
    };

    TEST_ASSERT_EQUAL(0, sonar_sweep_day5_1(test_set, ARRAY_SIZE(test_set)));
}

#if 0
void test_sonar_sweep_day5(void)
{
    uint64_t test_set[] =
    {
#       include "task_day5.inc"
    };

    TEST_ASSERT_EQUAL(0, sonar_sweep_day5_1(test_set, ARRAY_SIZE(test_set)));
}
#endif
