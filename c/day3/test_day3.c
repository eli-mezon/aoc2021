#include <unity.h>
#include <string.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))
#if 0
#define BITRATE (12)
int64_t sonar_sweep_day3_1(uint16_t * measurements, int64_t size)
{
    uint16_t counter[BITRATE] = {0};
    for (int64_t idx = 0; idx < size; idx++)
    {
        for (int64_t jdx = 0; jdx < BITRATE; jdx++)
        {
            counter[jdx] += (measurements[idx] >> jdx) & 0x1;
        }
    }
    uint16_t gamma = 0;
    uint16_t mask = 0;
    for (int64_t jdx = 0; jdx < BITRATE; jdx++)
    {
        printf("%d\n", counter[jdx]);
        gamma += ((counter[jdx] > size - counter[jdx] ) & 0x1) << jdx;
        mask += 1 << jdx;
    }

/*
    uint8_t gamma = ((counter[0] > size - counter[0] ) & 0x1);
    gamma += (((counter[1] > size - counter[1] ) & 0x1) << 1);
    gamma += (((counter[2] > size - counter[2] ) & 0x1) << 2);
    gamma += (((counter[3] > size - counter[3] ) & 0x1) << 3);
    gamma += (((counter[4] > size - counter[4] ) & 0x1) << 4);
*/
    uint16_t epsilon = ~gamma & mask;
    printf("\n\n\n%d\n", gamma);
    printf("%d\n\n\n\n", epsilon);

    return gamma * epsilon;
}
#else
#define BITRATE (12)
int64_t sonar_sweep_day3_2_a(uint16_t * measurements, int64_t size)
{
    uint16_t counter[BITRATE] = {0};
    uint16_t filtered[(BITRATE+1)*1000] = {0};
    uint16_t number[BITRATE+1] = {0};
    for (int64_t idx = 0; idx <size; idx++)
    {
        filtered[idx] = measurements[idx];
        number[0] += 1;
    }

    for (int64_t jdx = 0; jdx < BITRATE; jdx++)
    {
        printf("\n\n\n\nsize = %d\n", number[jdx]);
        for (int64_t idx = 0; idx < number[jdx]; idx++)
        {
            printf("%d,", filtered[jdx*1000+idx]);
            counter[jdx] += (filtered[jdx*1000+idx] >> (BITRATE - jdx - 1)) & 0x1;
        }
        printf("\ncounter = %d\n", counter[jdx]);

        uint16_t bit = (counter[jdx] >= number[jdx] - counter[jdx] ) & 0x1;
        printf("\nbit = %d\n", bit);

        for (int64_t idx = 0; idx < number[jdx]; idx++)
        {
            if (((filtered[jdx*1000+idx] >> (BITRATE - jdx - 1)) & 0x1) == bit)
            {
                filtered[(jdx+1)*1000 + (number[jdx+1])] = filtered[jdx*1000+idx];
                number[jdx+1] += 1;
                printf("%d, ", filtered[jdx*1000+idx]);
            }
        }

        if (number[jdx+1] == 1)
        {
            return filtered[(jdx+1)*1000];
        }

    }
    return 0;
}
int64_t sonar_sweep_day3_2_b(uint16_t * measurements, int64_t size)
{
    uint16_t counter[BITRATE] = {0};
    uint16_t filtered[(BITRATE+1)*1000] = {0};
    uint16_t number[BITRATE+1] = {0};
    for (int64_t idx = 0; idx <size; idx++)
    {
        filtered[idx] = measurements[idx];
        number[0] += 1;
    }

    for (int64_t jdx = 0; jdx < BITRATE; jdx++)
    {
        printf("\n\n\n\nsize = %d\n", number[jdx]);
        for (int64_t idx = 0; idx < number[jdx]; idx++)
        {
            printf("%d,", filtered[jdx*1000+idx]);
            counter[jdx] += (filtered[jdx*1000+idx] >> (BITRATE - jdx - 1)) & 0x1;
        }
        printf("\ncounter = %d\n", counter[jdx]);

        uint16_t bit = 1 - ((counter[jdx] >= number[jdx] - counter[jdx] ) & 0x1);
        printf("\nbit = %d\n", bit);

        for (int64_t idx = 0; idx < number[jdx]; idx++)
        {
            if (((filtered[jdx*1000+idx] >> (BITRATE - jdx - 1)) & 0x1) == bit)
            {
                filtered[(jdx+1)*1000 + (number[jdx+1])] = filtered[jdx*1000+idx];
                number[jdx+1] += 1;
                printf("%d, ", filtered[jdx*1000+idx]);
            }
        }

        if (number[jdx+1] == 1)
        {
            return filtered[(jdx+1)*1000];
        }

    }
    return 0;
}
#endif

void test_sonar_sweep_day3_2_example(void)
{
    uint16_t example_set[] =
    {
#       include "task_day3.inc"
    };

    TEST_ASSERT_EQUAL(230,
        sonar_sweep_day3_2_a(example_set, ARRAY_SIZE(example_set))
        * sonar_sweep_day3_2_b(example_set, ARRAY_SIZE(example_set)));
}

#if 0
void test_sonar_sweep_day3_2(void)
{
	uint16_t test_set[] =
    {
#       include "task_day3.inc"
    };

    TEST_ASSERT_EQUAL(198, sonar_sweep_day3_1(test_set, ARRAY_SIZE(test_set)));
}
#endif
