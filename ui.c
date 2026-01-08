#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ui.h"


int print_table(
    char headers[][NAME_LEN],
    char table[],
    const int rows,
    const int columns
    ) {

    int chr, column, row;
    size_t i;
    size_t size;
    size_t *sizes;

    if (rows <= 0 || columns <= 0) {
        fprintf(stderr, "Error: incorrect dimensions of the table.\n");
        return 1;
    }

    sizes = malloc((size_t)columns * sizeof *sizes);
    if (sizes == NULL) {
        fprintf(stderr, "Error: could not allocate memory.\n");
        return 1;
    }

    /* Calculating optimal size of each column. */
    for (column = 0; column < columns; column++) {
        sizes[column] = strlen(headers[column]);

        for (row = 0; row < rows; row++) {
            chr = 0;
            while (table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] != '\0') {
                chr++;
            }

            if (sizes[column] < chr) {
                sizes[column] = chr;
            }
        }
    }

    /* Printing headers. */
    printf("|");
    for (column = 0; column < columns; column++) {
        printf(" %s", headers[column]);
        size = sizes[column] - strlen(headers[column]);
        for (i = 0; i < size; i++) {printf(" ");}
        printf(" |");
    }
    printf("\n");

    /* Printing line separating headers from the rest of the table. */
    printf("|");
    for (column = 0; column < columns; column++) {
        for (i = 0; i < sizes[column] + 1; i++) {
            printf("=");
        }
        printf("=|");
    }
    printf("\n");

    /* Printing the rest of the table. */
    for (row = 0; row < rows; row++) {
        printf("|");
        for (column = 0; column < columns; column++) {
            chr = 0;
            printf(" ");
            while (table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] != '\0') {
                printf("%c", table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row]);
                chr++;
            }
            size = sizes[column] - chr;
            for (i = 0; i < size; i++) {printf(" ");}
            printf(" |");
        }
        printf("\n");
    }

    free(sizes);
    return 0;
}