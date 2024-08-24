#include "../headers/readFile.h"


//=================================Utilities=================================================================

void printAttributeList(AttributeList *attributeData) {
    AttributeList *current = attributeData;

    if (current == NULL) {
        printf("No attributes found.\n");
        return;
    }

    while (current != NULL) {
        printf("ID: %d\n", current->data.id);
        printf("Name: %s\n", current->data.name);
        printf("Type: %s\n", current->data.type);
        printf("Is Optional: %s\n", current->data.isOptional);
        printf("Size: %d\n", current->data.size);
        printf("--------------------------\n");

        current = current->next;
    }
}

void freeMemory(AttributeList *attributeData) {
    AttributeList *current = attributeData;
    while (current != NULL) {
        AttributeList *next = current->next;
        free(current);
        current = next;
    }
}


//===========================================================================================================

//=================================load File Data============================================================
int loadTableData(char nameTableFile[20], Table *tableData) {

    FILE *tableFile = fopen("./data/table.dic", "rb");

    if (tableFile == NULL) {
        printf("Unable to open the table.dic\n");
        return 0;
    }

    fseek(tableFile, 0, SEEK_END); 
    long file_size = ftell(tableFile); 
    fseek(tableFile, 0, SEEK_SET); 

    int record_size = sizeof(Table);
    int num_records = file_size / record_size;
    int hasBeenFound = 0;

    Table loadedTable;

    for (int i = 0; i < num_records; ++i) {
        if (fread(&loadedTable, record_size, 1, tableFile) != 1) {
            break;
        }

        if (strcmp(loadedTable.logical_name, nameTableFile) == 0) {
            *tableData = loadedTable;
            hasBeenFound = 1;
            break;
        }
    }

    fclose(tableFile);

    return hasBeenFound;
}

int loadAttributeData(AttributeList **attributeData, int tableId) {
    FILE *attributeFile = fopen("./data/att.dic", "rb");

    if (attributeFile == NULL) {
        printf("Unable to open the att.dic\n");
        return 0;
    }

    fseek(attributeFile, 0, SEEK_END);
    long file_size = ftell(attributeFile); 
    fseek(attributeFile, 0, SEEK_SET); 

    int record_size = sizeof(Attribute);
    int num_records = file_size / record_size;
    int hasBeenFound = 0;

    Attribute loadedAttribute;
    AttributeList *newNode = NULL;

    for (int i = 0; i < num_records; ++i) {
        if (fread(&loadedAttribute, record_size, 1, attributeFile) != 1) {
            break;
        }

        if (loadedAttribute.id == tableId) {
            newNode = (AttributeList *)malloc(sizeof(AttributeList));
            newNode->data = loadedAttribute;
            newNode->next = NULL;

            if (*attributeData == NULL) {
                *attributeData = newNode;
            } else {
                AttributeList *current = *attributeData;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newNode;
            }

            hasBeenFound = 1; 
        }
    }

    fclose(attributeFile);

    return hasBeenFound;
}

void loadData(char nameTableFile[20]) {
    
    if (!nameTableFile) {
        return;
    }

    Table *tableData = (Table *)malloc(sizeof(Table));
    loadTableData(nameTableFile, tableData);

    if (!loadTableData(nameTableFile, tableData)) {
        printf("No record found with the name %s\n", nameTableFile);
        return;
    } 

    printf("phisical path archve: %s\n", tableData->phisical_name);

    AttributeList *attributeData = NULL;

    if (!loadAttributeData(&attributeData, tableData->id)) {
        printf("No record found with the id %d\n", tableData->id);
        return;
    } 

    printAttributeList(attributeData);

    freeMemory(attributeData);
}
//===========================================================================================================