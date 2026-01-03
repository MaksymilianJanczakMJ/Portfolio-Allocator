#ifndef PORTFOLIO_ALLOCATOR_ALLOCATOR_H
#define PORTFOLIO_ALLOCATOR_ALLOCATOR_H

#define NAME_LEN 128

typedef struct {
    char name[NAME_LEN];
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
} instrument;


instrument make_instrument(const char *name, double value, double target_percent);


double calc_total_value(instrument v[], int rows);


int calc_v(instrument v[], double total_value, double payment, int rows);


int sort_by_fulfillment(int positions[], instrument v[], int rows);


void allocate_payment(instrument v[], double payment, int rows);


void calc_v_payment(instrument v[], double total_value, double payment, int rows);


void v_to_table(instrument v[], char out[][NAME_LEN], int rows, int columns);


#endif