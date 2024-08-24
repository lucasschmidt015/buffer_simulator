#include "./headers/readFile.h"

int main(int argc, char *argv[]) {
    printf("=================Welcome=================\n");

    if (argc>1) {
        loadData(argv[1]);
        return 0;
    }

    printf("Logical file name is required.\n");

    return 0;
}