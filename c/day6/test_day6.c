#include <unity.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

#define MAX(a,b) (a)>=(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) ((a) < 0 )?(-a):(a)

#define TEST_SIZE (1000)

#define MAX_DAY 8

static int64_t population[MAX_DAY + 1] = {0};

void print_population()
{
    for (int64_t idx = 0; idx <= MAX_DAY; idx++)
    {
        printf("%ld, ", population[idx]);
    }
    printf("\n");
}

void one_more_day()
{
    int64_t ready = population[0];
    for (int64_t idx = 1; idx <= MAX_DAY; idx++)
    {
        population[idx - 1] = population[idx];
    }

    population[6] += ready;
    population[MAX_DAY] = ready;
}

int64_t sum_population()
{
	int64_t sum = 0;
    for (int64_t idx = 0; idx <= MAX_DAY; idx++)
    {
        sum += population[idx];
    }
    return sum;
}

void fill_population(int64_t * data, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
       population[data[idx]] += 1;
       printf("%ld,%ld\n", data[idx], population[data[idx]]);
    }


}

int64_t sonar_sweep_day6_1(int64_t * data, int64_t size)
{
    printf("%ld, %ld\n", data[0], data[size-1]);
    printf("%ld\n", size);

    fill_population(data, size);
    print_population();

    for(int64_t idx = 0; idx < 256; idx++)
    {
       one_more_day();
//       print_population();
    }

    return sum_population();
}

void test_sonar_sweep_day6_example(void)
{
    int64_t test_set[] =
    {
#       include "example_day6.inc"
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
