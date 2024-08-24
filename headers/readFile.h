#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void loadData(char nameTableFile[20]);
int loadTableData(char nameTableFile[20], table *tableData);