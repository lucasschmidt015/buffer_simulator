#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("=================Welcome=================\n");

    if (argc>1) {
        printf("It'll read the file: %s \n", argv[1]);
        return 0;
    }

    printf("You need to pass the logical file name\n");

    return 0;
}