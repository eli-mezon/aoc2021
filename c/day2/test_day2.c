#include <unity.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

typedef struct {
  int direction;
  int size;
} command_t;

int64_t sonar_sweep_day2_1(command_t * measurements, int64_t size)
{
    int64_t result = 0;

    int64_t aim = 0;
    int64_t horizontal = 0;
    int64_t depth = 0;
    for (int64_t idx = 0; idx < size; idx++)
    {
      if (measurements[idx].direction)
      {
          aim += -1*measurements[idx].direction*measurements[idx].size;
      }
      else
      {
          horizontal += measurements[idx].size;
          depth += aim*measurements[idx].size;
      }
    }
    result = horizontal *  depth;
    return result;
}

void test_sonar_sweep_day2_1_example(void)
{
    command_t example_set[] =
    {
#       include "example_day2.inc"
    };

    TEST_ASSERT_EQUAL(900, sonar_sweep_day2_1(example_set, ARRAY_SIZE(example_set)));
}

#if 1
void test_sonar_sweep_day2_1(void)
{
    command_t test_set[] =
    {
#       include "task_day2.inc"
    };

    TEST_ASSERT_EQUAL(1942068080, sonar_sweep_day2_1(test_set, ARRAY_SIZE(test_set)));
}
#endif
