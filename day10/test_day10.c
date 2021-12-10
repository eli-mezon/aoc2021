#include <unity.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

#define MAX(a,b) (a)>=(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) (a < 0 )?-a:a

#define TEST_SIZE (10)

int64_t get_value(char symbol)
{
    switch(symbol)
    {
    case ')': return 3;
    case ']': return 57;
    case '}': return 1197;
    case '>': return 25137;
    }
    return 0;
}

int64_t getsymbolsize(char symbol)
{
    switch(symbol)
    {
    case '(': return 1;
    case '[': return 2;
    case '{': return 3;
    case '<': return 4;
    }
    return 0;
}

bool is_open(char symbol)
{
    return (symbol == '(' || symbol == '[' || symbol == '{' || symbol == '<');
}

bool is_close(char symbol)
{
    return (symbol == ')' || symbol == ']' || symbol == '}' || symbol == '>');
}

bool is_match(char aSymbol, char bSymbol)
{
    return (aSymbol == '(' && bSymbol == ')')
    || (aSymbol == '[' && bSymbol == ']')
    || (aSymbol == '{' && bSymbol == '}')
    || (aSymbol == '<' && bSymbol == '>');
}
void printdata(char * data, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
        printf("%c", data[idx]);
    }
    printf("\n");
}
int64_t find(char * data, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
    	if (is_open(data[idx])) return idx;
    }
    return 0;
}
int64_t getsize(char * data, int64_t size)
{
	int64_t sum = 0;
    for (int64_t idx = size-1; idx >= 0; idx--)
    {
    	if (is_open(data[idx]))
    	{
            printf("%c", data[idx]);
    		sum = sum * 5 + getsymbolsize(data[idx]);
    	}
    }
    return sum;
}
int64_t go_ahead(char * data, int64_t size, int64_t index)
{
    char symbol = data[index];
    int64_t symbol_index = index;
//printf("o{%c,%ld}\n", symbol, symbol_index);

    while (index <= size) {
        index += 1;
        if ('.' == data[index]) continue;
        if (is_open(data[index]))
        {
            int64_t go_result = go_ahead(data, size, index);
            if (-1 != go_result) return go_result;
        }
        else if (is_close(data[index]))
        {
//printf("c{%c,%ld}\n", data[index], index);
            if (is_match(symbol, data[index]))
            {
                data[index] = '.';
                data[symbol_index] = '.';
//printf("m[%ld,%ld]\n", symbol_index, index);
                return -1;
            }
            else return get_value(data[index]);
        }
//printdata( data, size);
    }
    return 0;
}
void shift_left(int64_t * buffer, int64_t index)
{
	int64_t value = buffer[index];
    for (int64_t idx = index+1; idx < 110; idx++)
    {
        int64_t tmp = buffer[idx];
        buffer[idx] = value;
        value = tmp;
        if (value == 0) break;
    }
}
void put_result(int64_t * buffer, int64_t value)
{
    for (int64_t idx = 0; idx < 110; idx++)
    {
        if (value < buffer[idx]) continue;
        shift_left(buffer, idx);
        buffer[idx] = value;
        break;
    }
}
void print_result(int64_t * buffer)
{
    for (int64_t idx = 0; idx < 110; idx++)
    {
        if (0 == buffer[idx]) break;
        printf("%ld, ", buffer[idx]);
    }
    printf("\n");
}

static int64_t results[110] = { 0 };
static int64_t results_size = 0;

int64_t sonar_sweep_day6_1(char ** data, int64_t size)
{
    printf("%s, %ld\n", data[0], strlen(data[0]));
    printf("%ld\n", size);


#if 1
//    int64_t sum = 0;
    for (int64_t idx = 0; idx < size; idx++)
    {
        char buffer[1000] = {0};
        memcpy(buffer, data[idx], strlen(data[idx]));
        int64_t goresult = go_ahead(buffer, strlen(data[idx]), 0);
//        printf("%ld\n", goresult);
        while (goresult < 0)
        {
            int64_t newidx = find(buffer, strlen(data[idx]));
            goresult = go_ahead(buffer, strlen(data[idx]), newidx);
        }
        if (0 == goresult)
        {

printdata( buffer, strlen(data[idx]));
            int64_t resize = getsize( buffer, strlen(data[idx]));
            printf("%ld\n", resize);
            results_size += 1;
            put_result(results, resize);
            print_result(results);
        }
    }
    printf("%ld\n", results_size);
#endif
    print_result(results);
    return results[results_size/2];
}

void test_sonar_sweep_day6_example(void)
{
    char * test_set[] =
    {
#       include "task_day10.inc"
    };

    TEST_ASSERT_EQUAL(0, sonar_sweep_day6_1(test_set, ARRAY_SIZE(test_set)));
}

/*
"[({(<(())[]>[[{[]{<()<>>",
"[({(<()[]>[[{[]{<()<>>",
"[({(<[]>[[{[]{<()<>>",
"[({(<>[[{[]{<()<>>",
"[({(<>[[{{<()<>>",
"[({(<>[[{{",

{([(<[}>{[]{[(<()>

 *
 */
