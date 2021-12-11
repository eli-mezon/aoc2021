#include <unity.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

#define MAX(a,b) (a)>=(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) (a < 0 )?-a:a

#define DIGITS_COUNT (100)
#define TEST_SIZE (100)

int64_t get_value(char ** data, int64_t aidx, int64_t ajdx)
{
//	printf("{%ld, %ld}= %c\n", aidx, ajdx, data[aidx][ajdx]);
    return data[aidx][ajdx] - '0';
}
static int64_t count = 0;
static int64_t count_data[TEST_SIZE][DIGITS_COUNT];
static int64_t first = 0;
static int64_t second = 0;
static int64_t third = 0;

void update_max(int64_t value)
{
    if (value > first)
    {
        third = second;
        second = first;
        first = value;
    }
    else if (value > second)
    {
        third = second;
        second = value;
    }
    else if (value > third)
    {
        third = value;
    }
}
void mark_and_go(char ** data, int64_t aidx, int64_t ajdx)
{
//	printf("[%ld, %ld]\n", aidx, ajdx);
    if (aidx == -1) return;
    if (ajdx == -1) return;
    if (aidx == TEST_SIZE) return;
    if (ajdx == DIGITS_COUNT )return;
    if (1 == count_data[aidx][ajdx]) return;
    if (9 == get_value(data, aidx, ajdx)) return;

    count_data[aidx][ajdx] = 1;
    count += 1;
//	printf("{%ld, %ld}\n", aidx, ajdx);

    mark_and_go(data, aidx - 1, ajdx);
    mark_and_go(data, aidx, ajdx - 1);
    mark_and_go(data, aidx, ajdx + 1);
    mark_and_go(data, aidx + 1, ajdx);
}

void gprint_data(char ** datatoprint)
{
	for (int64_t idx = 0; idx < TEST_SIZE; idx++)
    {
        for (int64_t jdx = 0; jdx < DIGITS_COUNT; jdx++)
        {
            printf("%c, ", datatoprint[idx][jdx]);
        }
        printf("\n");
    }
}
void gprint_basin(int64_t * datatoprint)
{
	for (int64_t idx = 0; idx < TEST_SIZE; idx++)
    {
        for (int64_t jdx = 0; jdx < DIGITS_COUNT; jdx++)
        {
            printf("%ld, ", datatoprint[idx*TEST_SIZE +  jdx]);
        }
        printf("\n");
    }
}

int64_t get_basin_size(char ** data, int64_t aidx, int64_t ajdx)
{
	count = 0;
	memset(count_data, 0x0, sizeof(count_data));
	mark_and_go(data, aidx, ajdx);

	return count;
}

int64_t get_sum_if_lower(char ** data, int64_t aidx, int64_t ajdx)
{
    int64_t value = get_value(data, aidx, ajdx);
    int64_t u = (aidx == 0) ? 10 : get_value(data, aidx - 1, ajdx);
    int64_t l = (ajdx == 0) ? 10 : get_value(data, aidx, ajdx - 1);
    int64_t d = (aidx == TEST_SIZE - 1) ? 10 : get_value(data, aidx + 1, ajdx);
    int64_t r = (ajdx == DIGITS_COUNT - 1) ? 10 : get_value(data, aidx, ajdx + 1);

    if (value < u && value < l && value < d && value < r)
    {
    	int64_t sum = get_basin_size(data, aidx, ajdx);
    	printf("%ld, %ld  : %ld\n", aidx, ajdx, sum);

        return sum;
    }
    return 0;
}

int64_t sonar_sweep_day6_1(char ** data, int64_t size)
{
    printf("%s, %ld\n", data[0], strlen(data[0]));
    printf("%ld\n", size);

#if 1
    for (int64_t idx = 0; idx < size; idx++)
    {
        for (int64_t jdx = 0; jdx < DIGITS_COUNT; jdx++)
        {
            update_max(get_sum_if_lower(data, idx, jdx));
        }
    }
#endif
    return first * second * third;
}

void test_sonar_sweep_day6_example(void)
{
    char * test_set[] =
    {
#       include "task_day9.inc"
    };

    TEST_ASSERT_EQUAL(0, sonar_sweep_day6_1(test_set, ARRAY_SIZE(test_set)));
}
