#ifndef PORTFOLIO_ALLOCATOR_ALLOCATOR_H
#define PORTFOLIO_ALLOCATOR_ALLOCATOR_H

#define NAME_LEN 128

typedef struct {
    char name[NAME_LEN];
    double value;
    double target_percentage;

    // Computed data
    double current_percentage;
    double after_payment_percentage;
    double fulfillment_level;

    // Results of the allocation
    double additional_percentage;
    double additional_value;
    double after_percentage;
} instrument;


instrument make_instrument(const char *name, double value, double target_percentage);


double calc_total_value(instrument v[], int rows);


int calc_v(instrument v[], double total_value, double payment, int rows);


int sort_by_fulfillment(int positions[], instrument v[], int rows);


int allocate_payment(instrument v[], double payment, int rows);


void calc_v_payment(instrument v[], double total_value, double payment, int rows);


void v_to_table(instrument v[], char out[][NAME_LEN], int rows, int columns);


#endif