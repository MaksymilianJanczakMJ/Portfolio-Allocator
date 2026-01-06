#ifndef PORTFOLIO_ALLOCATOR_CONFIG_H
#define PORTFOLIO_ALLOCATOR_CONFIG_H

#define NAME_LEN 128
#define COLUMNS 7

typedef struct {
    char name[NAME_LEN];
    double value;
    double target_percentage;

    /* Computed data.txt */
    double current_percentage;
    double after_payment_percentage;
    double fulfillment_level;

    /* Results of the allocation */
    double additional_percentage;
    double additional_value;
    double after_percentage;
} asset;

#endif