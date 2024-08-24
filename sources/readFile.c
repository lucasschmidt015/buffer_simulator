#include "../headers/readFile.h"

int loadTableData(char nameTableFile[20], table *tableData) {

    FILE *tableFile = fopen("./data/table.dic", "rb");

    if (tableFile == NULL) {
        printf("Unable to open the table.dic\n");
        return 0;
    }

    //Determinate the number of records
    fseek(tableFile, 0, SEEK_END); // Move to the end of the file 
    long file_size = ftell(tableFile); // Get the file size
    fseek(tableFile, 0, SEEK_SET); // Move back to the start of the file

    int record_size = sizeof(table);
    int num_records = file_size / record_size;
    int hasBeenFound = 0;

    table loadedTable;

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

void loadData(char nameTableFile[20]) {
    
    if (!nameTableFile) {
        return;
    }

    table *tableData = (table *)malloc(sizeof(table));
    loadTableData(nameTableFile, tableData);

    if (loadTableData(nameTableFile, tableData)) {
        printf("Coisa de louco tchê....\n");
    } else {
        printf("Mais bahh....\n");
    }

    
}