#include "allocator.h"
#include "ui.h"

#define COLUMNS 7

// Total amount of instruments in portfolio.
#define ROWS 6


int main(void) {
    char table[ROWS * COLUMNS][NAME_LEN];
    char headers[COLUMNS][NAME_LEN] = {"Valor Name", "Value", "Target [%]", "Current [%]", "Additional value", "After [%]", "After value"};
    instrument v[ROWS];

    // Amount of money to be distributed.
    const double payment = 500;

    // Creation of
    v[0] = make_instrument("Example 1.", 2200, 0.65);
    v[1] = make_instrument("Example 2.", 240, 0.10);
    v[2] = make_instrument("Example 3.", 90, 0.10);
    v[3] = make_instrument("Example 4.", 540, 0.05);
    v[4] = make_instrument("Example 5.", 200, 0.05);
    v[5] = make_instrument("Example 6.", 0, 0.05);

    allocate_payment(v, payment, ROWS);
    v_to_table(v, table, ROWS, COLUMNS);

    return print_table(headers, table, ROWS, COLUMNS);
}