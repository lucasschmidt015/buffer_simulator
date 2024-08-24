#include "../headers/readFile.h"

int loadTableData(char nameTableFile[20], Table *tableData) {

    FILE *tableFile = fopen("./data/table.dic", "rb");

    if (tableFile == NULL) {
        printf("Unable to open the table.dic\n");
        return 0;
    }

    //Determinate the number of records
    fseek(tableFile, 0, SEEK_END); // Move to the end of the file 
    long file_size = ftell(tableFile); // Get the file size
    fseek(tableFile, 0, SEEK_SET); // Move back to the start of the file

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

int loadAttributeData(Attribute *attributeData, int tableId) {
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

    for (int i = 0; i < num_records; ++i) {
        if (fread(&loadedAttribute, record_size, 1, attributeFile) != 1) {
            break;
        }

        if (loadedAttribute.id == tableId) {
            *attributeData = loadedAttribute;
            hasBeenFound = 1;
            break;
        }
    }

    printf("\n");
    printf("id: %d \n", loadedAttribute.id);
    printf("isOptional: %s \n", loadedAttribute.isOptional);
    printf("name: %s \n", loadedAttribute.name);
    printf("size: %d \n", loadedAttribute.size);
    printf("type: %s \n", loadedAttribute.type);
    printf("\n");


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

    Attribute *attributeData = (Attribute *)malloc(sizeof(Attribute));

    loadAttributeData(attributeData, tableData->id);

    if (!loadAttributeData(attributeData, tableData->id)) {
        printf("No record found with the id %d\n", tableData->id);
        return;
    } 

    printf("Attribute: %s\n", attributeData->name);
}