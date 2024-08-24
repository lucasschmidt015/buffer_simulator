#include "../headers/readFile.h"

void loadData(char nameTableFile[20]) {
    
    if (!nameTableFile) {
        return;
    }

    FILE *tableFile = fopen("./data/table.dic", "rb");

    if (tableFile == NULL) {
        printf("Unable to open the table.dic\n");
        return ;
    }

    //Determinate the number of records
    fseek(tableFile, 0, SEEK_END); // Move to the end of the file 
    long file_size = ftell(tableFile); // Get the file size
    fseek(tableFile, 0, SEEK_SET); // Move back to the start of the file

    int record_size = sizeof(table);
    int num_records = file_size / record_size;


    table loadedTable;

    int hasBeenFound = 0;

    for (int i = 0; i < num_records; ++i) {
        int result = fread(&loadedTable, record_size, 1, tableFile);

        if (result != 1) {
            if (feof(tableFile)) {
                printf("End of file reached\n");
            } else {
                printf("Error to read the file\n");
            }

            break;
        }

        if (strcmp(loadedTable.logical_name, nameTableFile) == 0) {
            // printf("Record %d:\n", i + 1);
            // printf("ID: %d\n", loadedTable.id);
            // printf("Logical Name: %s\n", loadedTable.logical_name);
            // printf("Physical Name: %s\n", loadedTable.phisical_name);
            // printf("\n");    
            hasBeenFound = 1;
            break;
        }


        // printf("Record %d:\n", i + 1);
        // printf("ID: %d\n", loadedTable.id);
        // printf("Logical Name: %s\n", loadedTable.logical_name);
        // printf("Physical Name: %s\n", loadedTable.phisical_name);
        // printf("\n");
    }

    if (!hasBeenFound) {
        printf("We don't find a record with the name %s\n", nameTableFile);
        return;
    }

    printf("Record has been founded.\n");

}