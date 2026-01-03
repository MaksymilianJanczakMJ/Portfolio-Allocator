#include "allocator.h"
#include "ui.h"
#include "config.h"

#define COLUMNS 7

/* Total amount of instruments in portfolio. */
#define ROWS 5


int main(void) {
    char table[ROWS * COLUMNS][NAME_LEN];
    char headers[COLUMNS][NAME_LEN] = {"Instrument name", "Value", "Target [%]", "Current [%]", "Additional value", "After [%]", "After value"};
    instrument v[ROWS];

    /* Amount of money to be distributed. */
    const double payment = 500;

    /* Creation of instruments. */
    v[0] = make_instrument("Example 1.", 700, 0.65);
    v[1] = make_instrument("Example 2.", 300, 0.10);
    v[2] = make_instrument("Example 3.", 50, 0.10);
    v[3] = make_instrument("Example 4.", 100, 0.15);
    v[4] = make_instrument("Example 5.", 500, -0.05);


    if (allocate_payment(v, payment, ROWS)) {return 1;}
    v_to_table(v, table, ROWS, COLUMNS);

    return print_table(headers, table, ROWS, COLUMNS);
}