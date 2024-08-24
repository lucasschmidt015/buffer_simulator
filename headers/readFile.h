#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This struct is difinig how the table dictionare should looks like
typedef struct
{
    int id;
    char logical_name[20];
    char phisical_name[20];
} Table;

//This is struct is defining how the attributes dictionare should looks like
typedef struct
{
    int id;
    char name[20];
    char type[1];
    char isOptional[1];
    int size;
} Attribute;


typedef struct AttributeList AttributeList;
struct AttributeList
{
    Attribute data;
    AttributeList *next;
};

void freeMemory(AttributeList *attributeData);
void loadData(char nameTableFile[20]);
void printAttributeList(AttributeList *attributeData);

int loadAttributeData(AttributeList **attributeData, int tableId);
int loadTableData(char nameTableFile[20], Table *tableData);
