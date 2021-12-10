#include <unity.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

#define MAX(a,b) (a)>=(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) (a < 0 )?-a:a

#define MAX_DAY 2000


#define TEST_SIZE (1000)

int64_t absmy(int64_t x)
{
    return ( x<0 ) ? -x : x;
}

int64_t cost_for_move(int64_t step)
{
	int64_t sum =0;
	for(int64_t idx = 0; idx <= step; idx ++)
	{
	    sum += idx;
	}
	return sum;
}
int64_t calc_cost_move(int64_t * data, int64_t size)
{
	int64_t sum = 0;
    for (int64_t idx = 0; idx < size; idx++)
    {
        sum += cost_for_move(data[idx]);
    }
    return sum;
}

int64_t make_move(int64_t * data, int64_t size, int64_t step)
{
    int64_t move[TEST_SIZE] = { 0 };
    for (int64_t idx = 0; idx < size; idx++)
    {
        move[idx] = absmy(data[idx] - step);
//        printf("%ld, %ld\n", move[idx], idx);
    }

    return calc_cost_move(move, size);
}

int64_t sonar_sweep_day6_1(int64_t * data, int64_t size)
{
    printf("%ld, %ld\n", data[0], data[size-1]);
    printf("%ld\n", size);

    int64_t min = INT64_MAX;
//    int64_t min_index = 0;

    for (int64_t idx = 0; idx < TEST_SIZE; idx++)
    {
        int64_t cost = make_move(data, size, idx);
        if (cost <= min)
        {
            min = cost;
//            min_index = idx;
//            printf("\n{%ld, %ld}\n", min, min_index);
        }
    }

    return min;
}

void test_sonar_sweep_day6_example(void)
{
    int64_t test_set[] =
    {
#       include "task_day7.inc"
    };

    TEST_ASSERT_EQUAL(0, sonar_sweep_day6_1(test_set, ARRAY_SIZE(test_set)));
}

#if 0
void test_sonar_sweep_day6(void)
{
    Line_t test_set[] =
    {
#       include "task_day6.inc"
    };

    TEST_ASSERT_EQUAL(0, sonar_sweep_day6_1(test_set, ARRAY_SIZE(test_set)));
}
#endif
