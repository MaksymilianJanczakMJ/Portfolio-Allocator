#ifndef PORTFOLIO_ALLOCATOR_CONFIG_H
#define PORTFOLIO_ALLOCATOR_CONFIG_H

#define NAME_LEN 128
#define COLUMNS 7


typedef struct {
    /* Data from file. */
    char name[NAME_LEN];
    double value;
    double target_percentage;

    /* Computing data. */
    double current_percentage;
    double after_payment_percentage;
    double fulfillment_level;

    /* Results of the allocation. */
    double additional_percentage;
    double additional_value;
    double after_percentage;
} asset;


typedef union {
    char string[NAME_LEN];
    double integer;
} str_or_dbl;


#endif