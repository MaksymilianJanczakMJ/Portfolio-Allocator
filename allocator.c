#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allocator.h"


asset make_asset(
    const char *name,
    double value,
    double target_percentage
    ) {

    asset v;

    strncpy(v.name, name, NAME_LEN - 1);
    v.name[NAME_LEN - 1] = '\0';

    v.value = value;

    if (target_percentage < 0) {
        v.target_percentage = 0;
    } else {
        v.target_percentage = target_percentage;
    }

    v.additional_percentage = 0;
    v.after_percentage = 0;
    v.current_percentage = 0;
    v.after_payment_percentage = 0;
    v.fulfillment_level = 0;
    v.additional_value = 0;

    return v;
}


double calc_total_value(
    asset v[],
    int rows
    ) {

    int row;
    double total_value = 0;

    for (row = 0; row < rows; row++) {
        total_value += v[row].value;
    }

    return total_value;
}


int calc_v(
    asset v[],
    double total_value,
    double contribution,
    int rows
    ) {

    int row;
    double sum_target_percentages = 0;

    for (row = 0; row < rows; row++) {
        sum_target_percentages += v[row].target_percentage;

        /* Calculation of the current percentage of total value(value of asset only) for each asset. */
        if (total_value == 0) {
            v[row].current_percentage = 0;
        } else {
            v[row].current_percentage = v[row].value / total_value;
        }

        /* Calculation of the percentage of total value(value of instruments + payment) for each asset. */
        if (total_value == 0 && contribution == 0) {
            v[row].after_payment_percentage = 0;
        } else {
            v[row].after_payment_percentage = v[row].value / (total_value + contribution);
        }

        /* Calculation of the fulfillment level for each asset. */
        if (v[row].target_percentage == 0) {
            v[row].fulfillment_level = 1;
        } else {
            v[row].fulfillment_level = v[row].after_payment_percentage / v[row].target_percentage;
        }

        /* Calculation of the additional value that needs to be put into each asset to achieve or get closer to
         the target percentage. */
        v[row].additional_value = v[row].additional_percentage * (total_value + contribution);
    }

    if (sum_target_percentages > 1 + 1e-12 || sum_target_percentages < 1 - 1e-12) {
        fprintf(stderr, "Error: total sum of target percentages must be equal 100 percent.\n");
        return 1;
    }

    return 0;
}


int sort_by_fulfillment(
    int positions[],
    asset v[],
    int rows
    ) {

    int row;
    int stop, pos;
    int tmp;
    int *sorted;
    sorted = malloc(rows * sizeof *sorted);
    if (sorted == NULL) {
        fprintf(stderr, "Error: could not allocate memory.\n");
        return 1;
    }

    for (row = 0; row < rows; row++) {
        sorted[row] = row;
    }

    for (stop = rows - 2; stop >= 0; stop--) {
        for (pos = 0; pos <= stop; pos++) {
            if (v[sorted[pos]].fulfillment_level > v[sorted[pos + 1]].fulfillment_level) {
                tmp = sorted[pos];
                sorted[pos] = sorted[pos + 1];
                sorted[pos + 1] = tmp;
            }
        }
    }

    memcpy(positions, sorted, rows * sizeof (int));
    free(sorted);
    return 0;
}


int allocate_contribution(
    asset v[],
    double contribution,
    int rows
    ) {

    int i, j;
    double additional_percentages, sum_additional_percentages, sum_target_percentages, total_value = 0;
    int *positions;

    if (rows < 2) {
        fprintf(stderr, "Error: there must be at least 2 assets.\n");
        return 1;
    }

    positions = malloc(rows * sizeof *positions);
    if (positions == NULL) {
        fprintf(stderr, "Error: could not allocate memory.");
        return 1;
    }

    total_value = calc_total_value(v, rows);
    additional_percentages = contribution / (contribution + total_value);
    if (calc_v(v, total_value, contribution, rows)) {
        free(positions);
        return 1;
    }

    for (i = 0; i < rows - 1 && additional_percentages > 1e-12; i++) {
        sum_additional_percentages = 0;
        sum_target_percentages = 0;
        sort_by_fulfillment(positions, v, rows);
        for (j = 0; j <= i; j++) {
            sum_additional_percentages += v[positions[j]].target_percentage * (v[positions[i + 1]].fulfillment_level - v[positions[j]].fulfillment_level);
            sum_target_percentages += v[positions[j]].target_percentage;
        }

        if (sum_additional_percentages > additional_percentages) {
            sum_additional_percentages = additional_percentages;
        }

        for (j = 0; j <= i; j++) {
            v[positions[j]].additional_percentage += sum_additional_percentages * (v[positions[j]].target_percentage / sum_target_percentages);
            v[positions[j]].fulfillment_level += sum_additional_percentages / sum_target_percentages;
        }

        additional_percentages -= sum_additional_percentages;
    }

    if (additional_percentages > 0) {
        for (j = 0; j < rows; j++) {
            v[positions[j]].additional_percentage += additional_percentages * v[positions[j]].target_percentage;
            v[positions[j]].fulfillment_level += additional_percentages;
        }
    }

    calc_v_contribution(v, total_value, contribution, rows);
    free(positions);
    return 0;
}


void calc_v_contribution(
    asset v[],
    double total_value,
    double contribution,
    int rows
    ) {

    int row;
    for (row = 0; row < rows; row++) {
        v[row].additional_value = v[row].additional_percentage * (total_value + contribution);
        v[row].after_percentage = (v[row].value + v[row].additional_value) / (total_value + contribution);
    }
}


void v_to_table(
    asset v[],
    char *table_out,
    const int rows
    ) {

    int row, column;
    char chr;
    char string[NAME_LEN];
    char table[rows * COLUMNS * NAME_LEN];

    for (row = 0; row < rows; row++) {
        /*
            1. Column.
        */
        column = 0;
        chr = 0;
        while (v[row].name[chr] != '\0') {
            table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = v[row].name[chr];
            chr++;
        }
        table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = '\0';

        /*
            2. Column.
        */
        column = 1;
        chr = 0;
        sprintf(string, "%.2f", v[row].value);
        while (string[chr] != '\0') {
            table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = string[chr];
            chr++;
        }
        table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = '\0';

        /*
            3. Column.
        */
        column = 2;
        chr = 0;
        sprintf(string, "%.2f", v[row].target_percentage * 100);
        while (string[chr] != '\0') {
            table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = string[chr];
            chr++;
        }
        table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = '\0';

        /*
            4. Column.
        */
        column = 3;
        chr = 0;
        sprintf(string, "%.2f", v[row].current_percentage * 100);
        while (string[chr] != '\0') {
            table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = string[chr];
            chr++;
        }
        table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = '\0';

        /*
            5. Column.
        */
        column = 4;
        chr = 0;
        sprintf(string, "%.2f", v[row].additional_value);
        while (string[chr] != '\0') {
            table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = string[chr];
            chr++;
        }
        table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = '\0';

        /*
            6. Column.
        */
        column = 5;
        chr = 0;
        sprintf(string, "%.2f", v[row].after_percentage * 100);
        while (string[chr] != '\0') {
            table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = string[chr];
            chr++;
        }
        table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = '\0';

        /*
            7. Column.
        */
        column = 6;
        chr = 0;
        sprintf(string, "%.2f", v[row].value + v[row].additional_value);
        while (string[chr] != '\0') {
            table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = string[chr];
            chr++;
        }
        table[chr + NAME_LEN * column + NAME_LEN * COLUMNS * row] = '\0';
    }

    memcpy(table_out, table, rows * COLUMNS * NAME_LEN);
}