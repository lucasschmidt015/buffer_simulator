#include <stdio.h>

//This struct is difinig how the table dictionare should looks like
typedef struct
{
    int id;
    char logical_name[20];
    char phisical_name[20];
} table;

//This is struct is defining how the attributes dictionare should looks like
typedef struct
{
    int id;
    char name[20];
    char type;
    char isOptional;
    int size;
} att;



int main(int argc, char *argv[]) {
    printf("=================Welcome=================\n");

    if (argc>1) {
        printf("It'll read the file: %s \n", argv[1]);
        return 0;
    }

    printf("You need to pass the logical file name\n");

    return 0;
}