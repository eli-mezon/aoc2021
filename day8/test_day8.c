#include <unity.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

#define MAX(a,b) (a)>=(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) (a < 0 )?-a:a

#define MAX_DAY 2000


#define TEST_SIZE (1000)

#define DIGITS_COUNT (10)
#define NUMBET_COUNT (4)
#define SEGMENT_COUNT (7)

typedef struct {
    char * digits[DIGITS_COUNT];
    char * number[NUMBET_COUNT];
} Code_t;

void decode_digits(Code_t data, char * code)
{
    int64_t  decode[SEGMENT_COUNT] = {0};
    int64_t  decode_uniq[SEGMENT_COUNT] = {0};
    for (int64_t idx = 0; idx < DIGITS_COUNT; idx++)
    {
        printf("%s\n", data.digits[idx]);
        size_t len = strlen(data.digits[idx]);
        for (size_t jdx = 0; jdx < len; jdx++)
        {
            printf("%c:", data.digits[idx][jdx]);
            uint8_t index = (uint8_t)data.digits[idx][jdx] - (uint8_t)'a';
            decode[index] += 1;

            if (len == 2 || len == 3 || len == 4 || len == 8)
            {
            decode_uniq[index] += 1;
            }
        }
        printf("\n");
    }

    for (int64_t idx = 0; idx < SEGMENT_COUNT; idx++)
    {
    switch (decode[idx])
    {
    case 4:
    	code[idx] = 5;
    	break;
    case 6:
    	code[idx] = 2;
    	break;
    case 7:
    	code[idx] = (decode_uniq[idx] == 0) ? 7 : 4;
    	break;
    case 8:
    	code[idx] = (decode_uniq[idx] == 1) ? 1 : 3;
    	break;
    case 9:
    	code[idx] = 6;
    	break;
    }
    }
    for (int64_t idx = 0; idx < SEGMENT_COUNT; idx++)
    {
/*
        printf("{%ld, ", decode[idx]);
        printf("%ld, ", decode_uniq[idx]);
*/
        printf("%d,", code[idx]);
    }
    printf("\n");

}

int64_t decode_word(char * word)
{
	int64_t sum = 0;
	bool has_2 = 0;
    for (int64_t idx = 0; idx < 8; idx++)
    {
        sum += word[idx];
        if (word[idx]==2) has_2 = 1;
    }

    switch(sum) {
    case 24: return 0;
    case 9: return 1;
    case 20 : return (has_2) ? 5 : 2;
    case 21 : return  3;
    case 15 : return  4;
    case 25 : return  6;
    case 10 : return  7;
    case 28 : return  8;
    case 23 : return  9;
    }
    return 0;
}

int64_t decode_number(char * data, char * code)
{
    char word[8] = {0};

    for (size_t idx = 0; idx < strlen(data); idx++)
    {
        word[idx] = code[data[idx] - 'a'];
    }

    printf("%s\n", word);
    return decode_word(word);
}

int64_t decode_numbers(Code_t data, char * code)
{
	int64_t sum = 0;
    for (int64_t idx = 0; idx < NUMBET_COUNT; idx++)
    {
        sum = sum * 10 + decode_number(data.number[idx], code);
    }
    return sum;
}

int64_t sonar_sweep_day6_1(Code_t * data, int64_t size)
{
    printf("%s, %s\n", data->digits[0], data->number[NUMBET_COUNT-1]);
    printf("%ld\n", size);

    int64_t sum = 0;
    char code[SEGMENT_COUNT] = {0};


    for (int64_t idx = 0; idx < size; idx++)
    {
        memset(code, 0, sizeof(code));
        decode_digits(data[idx], code);
        sum += decode_numbers(data[idx], code);
    }

    return sum;
}

void test_sonar_sweep_day6_example(void)
{
	Code_t test_set[] =
    {
#       include "task_day8.inc"
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

#if 0
 abcdefg

0: abc.efg
1: ..c..f.
2: a.cde.g
3: a.cd.fg
4: .bcd.f.
5: ab.d.fg
6: ab.defg
7: a.c..f.
8: abcdefg
9: abcd.fg

1: ..c..f.
4: .bcd.f.
7: a.c..f.
8: abcdefg
   2242141

0: abc.efg
2: a.cde.g
3: a.cd.fg
5: ab.d.fg
6: ab.defg
9: abcd.fg

   1234567
   8687497

   acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab |
   cdfeb fcadb cdfeb cdbaf


   0: 123.567 = 24
   1: ..3..6. = 9
   2: 1.345.7 = 20
   3: 1.34.67 = 21
   4: .234.6. = 15
   5: 12.4.67 = 20
   6: 12.4567 = 25
   7: 1.3..6. = 10
   8: 1234567 = 28
   9: 1234.67 = 23

24 = 0
9 = 1
20 = 2
21 = 3
15 = 4
20 = 5
25 = 6
10 = 7
28 = 8
23 = 9

#endif
