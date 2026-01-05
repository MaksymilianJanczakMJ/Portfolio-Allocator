#include "allocator.h"
#include "ui.h"
#include "config.h"

#define COLUMNS 7

/* Total amount of assets in portfolio. */
#define ROWS 5


int main(void) {
    char table[ROWS * COLUMNS][NAME_LEN];
    char headers[COLUMNS][NAME_LEN] = {"Asset name", "Value", "Target [%]", "Current [%]", "Additional value", "After [%]", "After value"};
    asset v[ROWS];

    /* Amount of funds to be distributed. */
    const double contribution = 500;

    /* Creation of assets. */
    v[0] = make_asset("Example 1.", 700, 0.50);
    v[1] = make_asset("Example 2.", 300, 0.20);
    v[2] = make_asset("Example 3.", 50, 0.15);
    v[3] = make_asset("Example 4.", 100, 0.10);
    v[4] = make_asset("Example 5.", 500, 0.05);

    if (allocate_contribution(v, contribution, ROWS)) {return 1;}
    v_to_table(v, table, ROWS, COLUMNS);
    print_table(headers, table, ROWS, COLUMNS);

    return 0;
}