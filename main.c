#include "allocator.h"
#include "ui.h"


#define COLUMNS 7
#define ROWS 6 // Total amount of instruments in portfolio.


int main(void) {
    char table[ROWS * COLUMNS][128];
    const double payment = 5000;
    char headers[COLUMNS][128] = {"Valor Name", "Value", "Target [%]", "Current [%]", "Additional value", "After [%]", "After value"};
    valor v[ROWS];
    v[0] = make_valor("Example 1.", 22000, 0.65);
    v[1] = make_valor("Example 2.", 2400, 0.10);
    v[2] = make_valor("Example 3.", 900, 0.10);
    v[3] = make_valor("Example 4.", 5400, 0.05);
    v[4] = make_valor("Example 5.", 2000, 0.05);
    v[5] = make_valor("Example 6.", 0, 0.05);

    allocate_payment(v, payment, ROWS);
    v_to_table(v, table, ROWS, COLUMNS);

    return print_table(headers, table, ROWS, COLUMNS);
}