#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "allocator.h"


valor make_valor(const char *name, double value, double percent) {
    valor v;
    strcpy(v.name, name);
    v.value = value;
    v.target_percent = percent;
    v.additional_percent = 0;
    return v;
}


double calc_total_value(valor v[], int rows) {
    int row;
    double total_value = 0;

    for (row = 0; row < rows; row++) {
        total_value += v[row].value;
    }

    return total_value;
}


int calc_v(valor v[], double total_value, double payment, int rows) {
    int row;
    double sum_target_percent = 0;
    for (row = 0; row < rows; row++) {
        sum_target_percent += v[row].target_percent;
        v[row].current_percent = v[row].value / total_value;
        v[row].after_payment_percent = v[row].value / (total_value + payment);
        v[row].fulfillment_level = v[row].after_payment_percent / v[row].target_percent;
        v[row].additional_value = v[row].additional_percent * (total_value + payment);
    }

    if (sum_target_percent > 1) {
        fprintf(stderr, "Error: total sum of target percentages must be equal 100%.\n");
        return 1;
    }

    return 0;
}


int sort_by_fulfillment(int positions[], valor v[], int rows) {
    int row, position[rows];
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


void allocate_payment(valor v[], double payment, int rows) {
    int i, j;
    int positions[rows];
    double additional_percents, sum_additional_percent, sum_target_percent, total_value = 0;

    total_value = calc_total_value(v, rows);
    additional_percents = payment / (payment + total_value);
    calc_v(v, total_value, payment, rows);

    for (i = 0; i < rows - 1 && additional_percents != 0; i++) {
        sum_additional_percent = 0;
        sum_target_percent = 0;
        sort_by_fulfillment(positions, v, rows);
        for (j = 0; j <= i; j++) {
            sum_additional_percent += v[positions[j]].target_percent * (v[positions[i + 1]].fulfillment_level - v[positions[j]].fulfillment_level);
            sum_target_percent += v[positions[j]].target_percent;
        }

        if (sum_additional_percent > additional_percents) {
            sum_additional_percent = additional_percents;
        }

        for (j = 0; j <= i; j++) {
            v[positions[j]].additional_percent += sum_additional_percent * (v[positions[j]].target_percent / sum_target_percent);
            v[positions[j]].fulfillment_level += sum_additional_percent / sum_target_percent;
        }

        additional_percents -= sum_additional_percent;
    }

    if (additional_percents > 0) {
        for (j = 0; j < rows; j++) {
            v[positions[j]].additional_percent += additional_percents * v[positions[j]].target_percent;
            v[positions[j]].fulfillment_level += additional_percents;
        }
    }

    calc_v_payment(v, total_value, payment, rows);
}


void calc_v_payment(valor v[], double total_value, double payment, int rows) {
    int row;
    for (row = 0; row < rows; row++) {
        v[row].additional_value = v[row].additional_percent * (total_value + payment);
        v[row].after_percent = (v[row].value + v[row].additional_value) / (total_value + payment);
    }
}


void v_to_table(valor v[], char out[][NAME_LEN], const int rows, const int columns) {
    int row;
    char str[128];

    for (row = 0; row < rows; row++) {
        strcpy(out[columns * row], v[row].name);
        sprintf(str, "%.2f", v[row].value);
        strcpy(out[columns * row + 1], str);
        sprintf(str, "%.2f", v[row].target_percent * 100);
        strcpy(out[columns * row + 2], str);
        sprintf(str, "%.2f", v[row].current_percent * 100);
        strcpy(out[columns * row + 3], str);
        sprintf(str, "%.2f", v[row].additional_value);
        strcpy(out[columns * row + 4], str);
        sprintf(str, "%.2f", v[row].after_percent * 100);
        strcpy(out[columns * row + 5], str);
        sprintf(str, "%.2f", v[row].value + v[row].additional_value);
        strcpy(out[columns * row + 6], str);
    }
}