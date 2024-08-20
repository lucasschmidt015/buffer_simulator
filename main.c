#include <stdio.h>
#include <stdlib.h>

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


void loadData(char nameTableFile[20]) {
    
    if (!nameTableFile) {
        return;
    }

    FILE *tableFile = fopen("table.dic", "rb");

    if (tableFile == NULL) {
        printf("Unable to open the table.dic");
        return ;
    }

    //Determinate the number of records
    fseek(tableFile, 0, SEEK_END); // Move to the end of the file 
    long file_size = ftell(tableFile); // Get the file size
    fseek(tableFile, 0, SEEK_SET); // Move back to the start of the file

    int record_size = sizeof(table);
    int num_records = file_size / record_size;


    table loadedTable;
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

        // Output the data read from the file
        printf("Record %d:\n", i + 1);
        printf("ID: %d\n", loadedTable.id);
        printf("Logical Name: %s\n", loadedTable.logical_name);
        printf("Physical Name: %s\n", loadedTable.phisical_name);
        printf("\n");
    }

    // table loadedTable;
    // size_t result = fread(&loadedTable, sizeof(table), 1, tableFile);

    // if (result != 1) {
    //     printf("Fail to read the file's data");
    //     fclose(tableFile);
    //     return;
    // }

    // fclose(tableFile);

    // printf("ID: %d\n", loadedTable.id);
    // printf("Logical Name: %s\n", loadedTable.logical_name);
    // printf("Physical Name: %s\n", loadedTable.phisical_name);
}



int main(int argc, char *argv[]) {
    printf("=================Welcome=================\n");

    if (argc>1) {
        printf("It'll read the file: %s \n", argv[1]);
        loadData(argv[1]);
        return 0;
    }

    printf("You need to pass the logical file name\n");

    return 0;
}