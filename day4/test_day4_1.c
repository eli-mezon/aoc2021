#include <unity.h>
#include <string.h>
#include <stdbool.h>
#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

#define BOARDSIZE (25)
typedef uint64_t Borad_t[BOARDSIZE];

uint64_t calc_board_sum(Borad_t aBoard)
{
    uint64_t sum = 0;
    for (uint16_t idx = 0; idx < BOARDSIZE; idx++)
    {
        sum += aBoard[idx];
    }
    return sum;
}

uint64_t calc_row_sum(Borad_t aBoard, uint16_t row_index)
{
    uint64_t sum = 0;
    for (uint16_t idx = 0; idx < 5; idx++)
    {
        sum += aBoard[row_index*5 + idx];
    }
    return sum;
}

uint64_t calc_colomn_sum(Borad_t aBoard, uint16_t colonm_index)
{
	uint64_t sum = 0;
    for (uint16_t idx = 0; idx < 5; idx++)
    {
        sum += aBoard[colonm_index + 5*idx];
    }
    return sum;
}

bool process_number(Borad_t aBoard, uint16_t number)
{
    int16_t idx = 0;
    for (idx = 0; idx < BOARDSIZE; idx++)
    {
        if (number == aBoard[idx])
        {
            aBoard[idx] = 0;
            break;
        }
    }
    int16_t row = idx / 5;
    int16_t column = idx % 5;

    int64_t row_sum = calc_row_sum(aBoard, row);
    int64_t colomn_sum = calc_colomn_sum(aBoard, column);

    return ((0 == row_sum) || (0 == colomn_sum));
}

int64_t sonar_sweep_day4_1(uint16_t * randseq, int64_t randseqsize,
    Borad_t *boards, int64_t boardamount)
{
    printf("%ld:%ld\n", randseqsize, boardamount);
    printf("%d\n", randseq[randseqsize-1]);
    printf("%ld\n", boards[boardamount-1][BOARDSIZE-1]);

    for (int64_t jdx = 0; jdx < randseqsize; jdx++)
    {
        for (int64_t idx = 0; idx < boardamount; idx ++)
        {
            if (process_number(boards[idx], randseq[jdx]))
            {
                uint64_t winboardsum = calc_board_sum(boards[idx]);
                return winboardsum * randseq[jdx];
            }
        }
    }

    return 0;
}

void test_sonar_sweep_day4_example(void)
{
    uint16_t randseq[] = {
        7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1
    };

    Borad_t boards[] =
    {
#       include "example_day4.inc"
    };

    TEST_ASSERT_EQUAL(1924, sonar_sweep_day4_1(randseq, ARRAY_SIZE(randseq), boards, ARRAY_SIZE(boards)));
}

#if 0
void test_sonar_sweep_day4(void)
{
    uint16_t randseq = {
        13,47,64,52,60,69,80,85,57,1,2,6,30,81,86,40,27,26,97,77,70,92,43,94,8,78,3,88,93,17,55,49,32,59,51,28,33,41,83,67,11,91,53,36,96,7,34,79,98,72,39,56,31,75,82,62,99,66,29,58,9,50,54,12,45,68,4,46,38,21,24,18,44,48,16,61,19,0,90,35,65,37,73,20,22,89,42,23,15,87,74,10,71,25,14,76,84,5,63,95
    };
    uint16_t test_set[] =
    {
#       include "task_day4.inc"
    };

    TEST_ASSERT_EQUAL(198, sonar_sweep_day4_1(test_set, ARRAY_SIZE(test_set)));
}
#endif
