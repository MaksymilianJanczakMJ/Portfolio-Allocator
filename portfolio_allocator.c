#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct {
    char name[128];
    double value;
    double target_percent;
    double current_percent;
    double after_payment_percent;
    double fulfillment_level;
    double additional_percent;
    double additional_value;
    double after_percent;
} valor;


valor make_valor(char name[128], double value, double percent) {
    int i;
    valor v;
    strcpy(v.name, name);
    v.value = value;
    v.target_percent = percent;
    v.additional_percent = 0;
    return v;
}


int print_table(const char headers[][128], const char data[][128], const int rows, const int columns) {
    int row, column;
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

    //Calculating optimal size of every column.
    for (column = 0; column < columns; column++) {
        sizes[column] = strlen(headers[column]);

        for (row = 0; row < rows; row++) {
            if (sizes[column] < strlen(data[columns * row + column])) {
                sizes[column] = strlen(data[columns * row + column]);
            }
        }
    }

    //Printing headers.
    printf("|");
    for (column = 0; column < columns; column++) {
        printf(" %s", headers[column]);
        size = sizes[column] - strlen(headers[column]);
        for (i = 0; i < size; i++) {printf(" ");}
        printf(" |");
    }
    printf("\n");

    //Printing line separating headers from the rest of the table.
    printf("|");
    for (column = 0; column < columns; column++) {
        for (i = 0; i < sizes[column] + 1; i++) {
            printf("=");
        }
        printf("=|");
    }
    printf("\n");

    //Printing the rest of the table.
    for (row = 0; row < rows; row++) {
        printf("|");
        for (column = 0; column < columns; column++) {
            printf(" %s", data[columns * row + column]);
            size = sizes[column] - strlen(data[columns * row + column]);
            for (i = 0; i < size; i++) {printf(" ");}
            printf(" |");
        }
        printf("\n");
    }

    free(sizes);
    return 0;
}


void v_to_table(valor v[], char string[][128], const int rows, const int columns) {
    int row;
    char str[128];

    for (row = 0; row < rows; row++) {
        strcpy(string[columns * row], v[row].name);
        sprintf(str, "%.2f", v[row].value);
        strcpy(string[columns * row + 1], str);
        sprintf(str, "%.2f", v[row].target_percent * 100);
        strcpy(string[columns * row + 2], str);
        sprintf(str, "%.2f", v[row].current_percent * 100);
        strcpy(string[columns * row + 3], str);
        sprintf(str, "%.2f", v[row].additional_value);
        strcpy(string[columns * row + 4], str);
        sprintf(str, "%.2f", v[row].after_percent * 100);
        strcpy(string[columns * row + 5], str);
        sprintf(str, "%.2f", v[row].value + v[row].additional_value);
        strcpy(string[columns * row + 6], str);
    }
}


double calc_total_value(valor v[], int rows) {
    int row;
    double total_value = 0;

    for (row = 0; row < rows; row++) {
        total_value += v[row].value;
    }

    return total_value;
}


void calc_v(valor v[], double total_value, double payment, int rows) {
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
        exit (1);
    }
}


void calc_v_payment(valor v[], double total_value, double payment, int rows) {
    int row;
    for (row = 0; row < rows; row++) {
        v[row].additional_value = v[row].additional_percent * (total_value + payment);
        v[row].after_percent = (v[row].value + v[row].additional_value) / (total_value + payment);
    }
}


int small(valor v[], int rows, int n) {
    int row, position;
    int stop, pos;
    int tmp;
    int *positions;
    positions = malloc(rows * sizeof *positions);
    if (positions == NULL) {
        fprintf(stderr, "Error: could not allocate memory.\n");
        return 1;
    }

    for (row = 0; row < rows; row++) {
        positions[row] = row;
    }

    for (stop = rows - 2; stop >= 0; stop--) {
        for (pos = 0; pos <= stop; pos++) {
            if (v[positions[pos]].fulfillment_level > v[positions[pos + 1]].fulfillment_level) {
                tmp = positions[pos];
                positions[pos] = positions[pos + 1];
                positions[pos + 1] = tmp;
            }
        }
    }

    position = positions[n];
    free(positions);
    return position;
}


int main(void) {
    const int rows = 6;
    const int columns = 7;
    double total_value = 0;
    int i, j;
    int referance, taker;
    char table[rows * columns][128];
    double additional_percents, sum_additional_percent, sum_target_percent;
    const double payment = 60000;
    char headers[7][128] = {"Valor Name", "Value", "Target [%]", "Current [%]", "Additional value", "After [%]", "After value"};
    valor v[rows];
    v[0] = make_valor("Akcje IKE", 26309.99, 0.65);
    v[1] = make_valor("TQQQ", 2385.68, 0.10);
    v[2] = make_valor("Kryptowaluty", 909.22, 0.10);
    v[3] = make_valor("Metale szlachetne", 5399.96, 0.05);
    v[4] = make_valor("Obligacje skarbowe", 2056.15, 0.05);
    v[5] = make_valor("Tactical buffer", 0, 0.05);

    total_value = calc_total_value(v, rows);
    additional_percents = payment / (payment + total_value);
    calc_v(v, total_value, payment, rows);

    for (i = 0; i < rows - 1 && additional_percents != 0; i++) {
        sum_additional_percent = 0;
        sum_target_percent = 0;
        referance = small(v, rows, i + 1);
        for (j = 0; j <= i; j++) {
            taker = small(v, rows, j);
            sum_additional_percent += v[taker].target_percent * (v[referance].fulfillment_level - v[taker].fulfillment_level);
            sum_target_percent += v[taker].target_percent;
        }

        if (sum_additional_percent > additional_percents) {
            sum_additional_percent = additional_percents;
        }

        for (j = 0; j <= i; j++) {
            taker = small(v, rows, 0);
            v[taker].additional_percent += sum_additional_percent * (v[taker].target_percent / sum_target_percent);
            v[taker].fulfillment_level += sum_additional_percent * (v[taker].target_percent / sum_target_percent) / v[taker].target_percent;
        }

        additional_percents -= sum_additional_percent;
    }

    if (additional_percents > 0) {
        for (j = 0; j < rows; j++) {
            taker = small(v, rows, 0);
            v[taker].additional_percent += additional_percents * v[taker].target_percent;
            v[taker].fulfillment_level += additional_percents * v[taker].target_percent / v[taker].target_percent;
        }
    }

    calc_v_payment(v, total_value, payment, rows);
    v_to_table(v, table, rows, columns);
    print_table(headers, table, rows, columns);

    return 0;
}