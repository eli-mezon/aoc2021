#include <unity.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

#define MAX(a,b) (a)>=(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) (a < 0 )?-a:a

#define MATRIXSIZE (10)
void flash(int64_t * buffer, int64_t poss);

void fill_ocpotus(int64_t * buffer, int64_t * input, int64_t inputsize)
{
    for (int64_t idx = 0; idx < inputsize; idx++)
    {
        int64_t value = input[idx];
        int64_t jdx = 0;
        while (value != 0)
        {
            buffer[idx*MATRIXSIZE + (MATRIXSIZE - 1 - jdx)] = value % 10;
            value = value / 10;
            jdx += 1;
        }
    }
}

void make_day(int64_t * buffer, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
        buffer[idx] += 1;
        if (buffer[idx] > 9)
        {
            flash(buffer, idx);
        }
    }
}
int64_t calc_flash(int64_t * buffer, int64_t size)
{
	int64_t sum = 0;
    for (int64_t idx = 0; idx < size; idx++)
    {
        if (buffer[idx] > 9)
        {
        	sum += 1;
        	buffer[idx] = 0;
        }
    }
    return sum;
}

void increase(int64_t * buffer, int64_t idx, int64_t jdx)
{
    if (idx < 0 || idx >= MATRIXSIZE) return;
    if (jdx < 0 || jdx >= MATRIXSIZE) return;
    buffer[idx*MATRIXSIZE + jdx] += 1;
    if (buffer[idx*MATRIXSIZE + jdx] == 10) flash(buffer, (idx*MATRIXSIZE + jdx));
}

void flash(int64_t * buffer, int64_t poss)
{
	if (buffer[poss] != 10) return;
	buffer[poss] += 1;
	int64_t idx = poss / MATRIXSIZE;
	int64_t jdx = poss % MATRIXSIZE;
	increase(buffer, idx-1, jdx-1);
	increase(buffer, idx-1, jdx);
	increase(buffer, idx-1, jdx+1);
	increase(buffer, idx, jdx-1);
	increase(buffer, idx, jdx+1);
	increase(buffer, idx+1, jdx-1);
	increase(buffer, idx+1, jdx);
	increase(buffer, idx+1, jdx+1);
}

void make_flash(int64_t * buffer, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
        if (buffer[idx] > 9)
        {
            flash(buffer, idx);
        }
    }
}

void print_ocpotus(int64_t * buffer)
{
    for (int64_t idx = 0; idx < MATRIXSIZE; idx++)
    {
        for (int64_t jdx = 0; jdx < MATRIXSIZE; jdx++)
        {
            printf("%ld, ", buffer[idx*MATRIXSIZE +jdx]);
        }
        printf("\n");
    }
    printf("\n");
}
int64_t sonar_sweep_day6_1(int64_t * data, int64_t size)
{
    int64_t octopus[MATRIXSIZE*MATRIXSIZE] = {0};
    fill_ocpotus(octopus, data, size);
    print_ocpotus(octopus);

//    int64_t sum = 0;

//    for (int64_t idx = 0; idx < 100; idx++)
    int64_t index = 0;
    while(1)
    {
    	index += 1;
        make_day(octopus, ARRAY_SIZE(octopus));
//        make_flash(octopus, ARRAY_SIZE(octopus));
        print_ocpotus(octopus);
        if(100 == calc_flash(octopus, ARRAY_SIZE(octopus))) break;
//        print_ocpotus(octopus);
    }

    return index;
}

void test_sonar_sweep_day6_example(void)
{
    int64_t test_set[] =
    {
#       include "task_day11.inc"
    };

    TEST_ASSERT_EQUAL(0, sonar_sweep_day6_1(test_set, ARRAY_SIZE(test_set)));
}
