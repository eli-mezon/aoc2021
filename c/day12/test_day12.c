#include <unity.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define ARRAY_SIZE(n) (sizeof(n)/sizeof(n[0]))

#define MAX(a,b) (a)>=(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)
#define ABS(a) (a < 0 )?-a:a

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

#define MAXNAMESIZE (10)
#define MAXPATHSIZE (1000)
#define NODECOUNT (100)

typedef struct 
{
    char * a;
    char * b;
} Link_t;

typedef struct Node Node_t;
struct Node
{
    char name[MAXNAMESIZE];
    int64_t size;
    Link_t * links[NODECOUNT];
    Node_t * nodes[NODECOUNT];
    int64_t nodecounter;
};

static Node_t nodevector[NODECOUNT];
static int64_t nodeamount = 0;
static int64_t pathamount = 0;

void print_links(Link_t * buffer, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
            printf("%s - %s", buffer[idx].a, buffer[idx].b);
        printf("\n");
    }
    printf("\n");
}

void print_nodes(Node_t * buffer, int64_t size)
{
    for (int64_t idx = 0; idx < size; idx++)
    {
        printf("%s:%ld", buffer[idx].name, buffer[idx].nodecounter);
        printf("\n");
    }
    printf("\n");
}

Node_t * add_node(char * aNodeName)
{
    int64_t index = nodeamount;
    nodeamount += 1;

    memset(&nodevector[index], 0, sizeof(nodevector[index]));
    strncpy(nodevector[index].name, aNodeName, sizeof(nodevector[index].name));
//    printf("New node %s:%ld\n", nodevector[index].name, nodevector[index].nodecounter);

    return &nodevector[index];
}

void add_link(Node_t * aNode, Node_t * aLinkedNode, Link_t * aLink)
{
    if (0 == strcmp(aNode->name, "end")) return;
    if (0 == strcmp(aLinkedNode->name, "start")) return;
    aNode->nodes[aNode->nodecounter] = aLinkedNode;
    aNode->links[aNode->nodecounter] = aLink;
    aNode->nodecounter += 1;
//    printf("Added link %s->%s\n", aNode->name, aLinkedNode->name);
}

Node_t * find_node(char * aNodeName)
{
    for (int64_t idx = 0; idx < nodeamount; idx++)
    {
        if (0 == strcmp(aNodeName, nodevector[idx].name))
        {
//            printf("Found node %s:%ld\n", nodevector[idx].name, nodevector[idx].nodecounter);
            return &nodevector[idx];
        }
    }
    return add_node(aNodeName);
}

void link_two_nodes(Node_t * aNodeA, Node_t * aNodeB, Link_t * aLink)
{
    add_link(aNodeA, aNodeB, aLink);
    add_link(aNodeB, aNodeA, aLink);
}

void process_link(Link_t * aLink)
{
//    printf("Process link %s<->%s...\n", aLink->a, aLink->b);

    Node_t * nodeA = find_node(aLink->a);
    Node_t * nodeB = find_node(aLink->b);
    link_two_nodes(nodeA, nodeB, aLink);
}

void build_path(Node_t * aNode, char * path, bool allowtwice)
{
    if (0 == strcmp(aNode->name, "end"))
    {
        pathamount += 1;
        return;
    }
    char* newpath = concat(path, aNode->name);
//    printf("Path: %s\n", newpath);

    for (int64_t idx = 0; idx < aNode->nodecounter; idx++)
    {
        char first = aNode->nodes[idx]->name[0];

        if ((first >= 97) && (first <= 122)
            && (NULL != strstr(path, aNode->nodes[idx]->name)))
        {
            if (allowtwice)
            {
                build_path(aNode->nodes[idx], newpath, false);
            }
            else
            {
                continue;
            }
        }
        else 
        {
        build_path(aNode->nodes[idx], newpath, allowtwice);
        }
    }

    free(newpath); // deallocate the string
}


int64_t sonar_sweep_day6_1(Link_t * data, int64_t size)
{
    print_links(data, size);


    for (int64_t idx = 0; idx < size; idx++)
    {
        process_link(&data[idx]);
    }
    print_nodes(nodevector, nodeamount);

    Node_t * start = find_node("start");

    // allowtwice should be:
    // - false for the first task
    // - true for the second task 
    build_path(start, "", true);

    return pathamount;
}

void test_sonar_sweep_day6_example(void)
{
    Link_t test_set[] =
    {
#       include "task_day12.inc"
    };

    TEST_ASSERT_EQUAL(0, sonar_sweep_day6_1(test_set, ARRAY_SIZE(test_set)));
}
