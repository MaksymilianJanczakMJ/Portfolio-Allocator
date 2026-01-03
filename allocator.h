#ifndef PORTFOLIO_ALLOCATOR_ALLOCATOR_H
#define PORTFOLIO_ALLOCATOR_ALLOCATOR_H

#define NAME_LEN 128

typedef struct {
    char name[128];
    double value;
    double target_percent;

    // Computed data
    double current_percent;
    double after_payment_percent;
    double fulfillment_level;

    // Results of the allocation
    double additional_percent;
    double additional_value;
    double after_percent;
} valor;


valor make_valor(const char *name, double value, double percent);


double calc_total_value(valor v[], int rows);


int calc_v(valor v[], double total_value, double payment, int rows);


int sort_by_fulfillment(int positions[], valor v[], int rows);


void allocate_payment(valor v[], double payment, int rows);


void calc_v_payment(valor v[], double total_value, double payment, int rows);


void v_to_table(valor v[], char out[][NAME_LEN], int rows, int columns);


#endif