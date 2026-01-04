#ifndef PORTFOLIO_ALLOCATOR_ALLOCATOR_H
#define PORTFOLIO_ALLOCATOR_ALLOCATOR_H
#include "config.h"

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
} asset;


asset make_asset(const char *name, double value, double target_percentage);


double calc_total_value(asset v[], int rows);


int calc_v(asset v[], double total_value, double contribution, int rows);


int sort_by_fulfillment(int positions[], asset v[], int rows);


int allocate_contribution(asset v[], double contribution, int rows);


void calc_v_contribution(asset v[], double total_value, double contribution, int rows);


void v_to_table(asset v[], char out[][NAME_LEN], int rows, int columns);


#endif