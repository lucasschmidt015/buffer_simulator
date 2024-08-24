#include "../headers/readFile.h"

int readTableFile(char nameTableFile[20], Table *tableData) {

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

int readAttributeFile(AttributeList **attributeData, int tableId) {
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

int readDataFile(AttributeList *attributes, char phisicalName[20]) {
    char filePath[50] = "./data/";
    strcat(filePath, phisicalName);

    FILE *dataFile = fopen(filePath, "rb");

    if (dataFile == NULL) {
        printf("Unable to open\n");
        return 0;
    }

    AttributeList *currentAttribute;
    int recordCount = 0;

    while (1) {
        currentAttribute = attributes;
        int recordValid = 1;  

        while (currentAttribute != NULL) {
            Attribute attribute = currentAttribute->data;

            if (attribute.type[0] == 'I') { 
                int value;
                if (fread(&value, sizeof(int), 1, dataFile) != 1) {
                    recordValid = 0;
                    break;
                }
                printf("%-20s: %d\n", attribute.name, value);
            } else if (attribute.type[0] == 'D') { 
                double value;
                if (fread(&value, sizeof(double), 1, dataFile) != 1) {
                    recordValid = 0;
                    break;
                }
                printf("%-20s: %.6f\n", attribute.name, value);
            } else if (attribute.type[0] == 'S') { 
                char *value = (char *)malloc(attribute.size + 1);
                if (fread(value, sizeof(char), attribute.size, dataFile) != attribute.size) {
                    free(value);
                    recordValid = 0;
                    break;
                }
                value[attribute.size] = '\0'; 
                printf("%-20s: %s\n", attribute.name, value);
                free(value);
            } else {
                printf("Unknown type for attribute %s\n", attribute.name);
                recordValid = 0;
                break;
            }

            currentAttribute = currentAttribute->next;
        }

        if (!recordValid) {
            break;  
        }

        printf("\n"); 
        recordCount++;
    }

    fclose(dataFile);

    printf("Total records read: %d\n", recordCount);
    return 1;
}

void loadData(char nameTableFile[20]) {
    
    if (!nameTableFile) {
        return;
    }

    Table *tableData = (Table *)malloc(sizeof(Table));

    if (!readTableFile(nameTableFile, tableData)) {
        printf("No record found for '%s\n", nameTableFile);
        return;
    } 

    AttributeList *attributeData = NULL;
    if (!readAttributeFile(&attributeData, tableData->id)) {
        printf("No attributes found for table '%s'.\n", nameTableFile);
        return;
    } 

    readDataFile(attributeData, tableData->phisical_name);

    AttributeList *current = attributeData;
    while (current != NULL) {
        AttributeList *next = current->next;
        free(current);
        current = next;
    }
}
//===========================================================================================================