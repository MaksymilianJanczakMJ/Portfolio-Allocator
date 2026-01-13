#include <stdio.h>
#include <string.h>

#include "config.h"
#include "file_writer.h"


int write_to_file(
    asset v[],
    char path[NAME_LEN],
    int rows
    ) {

    str_or_dbl total_value;
    int row;
    char string[NAME_LEN];
    FILE *file = fopen(path, "w");
    if (file == NULL) {
        fprintf(stderr, "Error in write_to_file() function: could not open \"%s\" file.\n", path);
        return 1;
    }

    /* Writing data to the file. */
    for (row = 0; row < rows; row++) {
        fwrite(v[row].name, 1, strlen(v[row].name), file);
        fwrite(";", 1, 1, file);

        sprintf(string, "%f", v[row].current_percentage);
        fwrite(string, 1, strlen(string), file);
        fwrite(";", 1, 1, file);

        sprintf(string, "%.2f", v[row].additional_value);
        fwrite(string, 1, strlen(string), file);
        fwrite(";", 1, 1, file);

        sprintf(string, "%f", v[row].after_percentage);
        fwrite(string, 1, strlen(string), file);
        fwrite(";", 1, 1, file);

        sprintf(string, "%.2f", v[row].value + v[row].additional_value);
        fwrite(string, 1, strlen(string), file);
        fwrite(";", 1, 1, file);

        fwrite("\n", 1, 1, file);
    }

    fclose(file);

    /* Usage of the union. */
    total_value.integer = 0;
    for (row = 0; row < rows; row++) {
        total_value.integer += v[row].value + v[row].additional_value;
    }
    sprintf(string, "%.2f", total_value.integer);
    strncpy(total_value.string, string, NAME_LEN * sizeof (char));
    printf("Total value after contribution: %s.\n", total_value.string);

    return 0;
}