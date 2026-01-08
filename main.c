#include "allocator.h"
#include "ui.h"
#include "config.h"
#include "file_reader.h"

#include <stdlib.h>
#define ROWS 5


int main(void) {
    char path[NAME_LEN] = "data.txt";
    char *table;
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

    if (allocate_contribution(v, contribution, rows)) {
        return 1;
    }

    table = malloc(rows * COLUMNS * NAME_LEN * sizeof *table);
    v_to_table(v, table, rows);

    print_table(headers, table, rows, COLUMNS);

    free(v);
    free(table);

    return 0;
}