#include "allocator.h"
#include "ui.h"
#include "config.h"
#include "file_reader.h"

#include <stdio.h>
#include <stdlib.h>
#define ROWS 5


int main(void) {
    int i;
    char path[NAME_LEN] = "data.txt";
    char *table[NAME_LEN];
    char headers[COLUMNS][NAME_LEN] = {"Asset name", "Value", "Target [%]", "Current [%]", "Additional value", "After [%]", "After value"};
    int rows;
    asset *v;

    /* Amount of funds to be distributed. */
    const double contribution = 500;

    if (check_file_len(&rows, path)) {
        return 1;
    }

    v = malloc(rows * sizeof *v);
    read_from_file(v, path);

    for (i = 0; i < rows; i++) {
        printf("%s\n", v[i].name);
        printf("%f\n", v[i].value);
        printf("%f\n", v[i].target_percentage);
    }

    if (allocate_contribution(v, contribution, rows)) {return 1;}
    //v_to_table(v, &table, rows);

    //printf("%s\n", table[0]);

    //print_table(headers, table, rows, COLUMNS);

    return 0;
}