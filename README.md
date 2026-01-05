# Portfolio Allocator
A C90 tool that allocates an additional portfolio contribution across financial assets according to given target percentages using a contribution-only fulfillment equalization algorithm.

## Purpose
This tool is made to address an allocation problem that occurs while making repeated contributions over time. As different financial assets change in value independently, their portfolio weights drift away from target percentages. Simply splitting a new contribution according to target percentages is a naive approach that does not reliably correct this drift over longer time horizons.

## Algorithm
1. The algorithm is based on the fulfillment level of each asset. It is defined as the ratio between its current percentage of total value to its target percentage. It represents how far from achieving target percentage an asset is.
2. New contribution is allocated in least fulfilled assets first, to the point where fulfillment level meets level of better aligned assets or until the available contribution is exhausted. It can be compared to filling buckets to the same level, but the buckets differ in bottom surface area which represents target percentage. The higher the surface area the more water it takes to fill the bucket to a certain level. Also the higher the target percentage the more contribution it takes to raise the fulfillment level to a certain value.
3. The algorithm can change the value of assets only by using the given contribution. It cannot sell assets or exchange them for each other. It would not always make percentages of assets equal to their target percentages, but it will always move them closer to the intended ratio.

## Features
1. C90 compliance
2. Contribution-only allocation
3. No selling
4. Hardcoded asset creation
5. Table-formatted output

## Limitations
1. Target percentages must be non-negative.
2. Allocation does not include transaction fees.
3. Target percentages of all assets must sum to 100%.
4. Value of each asset must be non-negative.
5. Number of assets and data for allocation need to be hardcoded.

## Usage
In `main.c` data for allocation must be hardcoded.

### Example:

#### Input:
	#define ROWS 5
	const double contribution = 500;
	v[0] = make_asset("Example 1.", 700, 0.50);
	v[1] = make_asset("Example 2.", 300, 0.20);
	v[2] = make_asset("Example 3.", 50, 0.15);
	v[3] = make_asset("Example 4.", 100, 0.10);
	v[4] = make_asset("Example 5.", 500, 0.05);

#### Output:
	| Asset name | Value  | Target [%] | Current [%] | Additional value | After [%] | After value |
	|============|========|============|=============|==================|===========|=============|
	| Example 1. | 700.00 | 50.00      | 42.42       | 168.42           | 40.39     | 868.42      |
	| Example 2. | 300.00 | 20.00      | 18.18       | 47.37            | 16.16     | 347.37      |
	| Example 3. | 50.00  | 15.00      | 3.03        | 210.53           | 12.12     | 260.53      |
	| Example 4. | 100.00 | 10.00      | 6.06        | 73.68            | 8.08      | 173.68      |
	| Example 5. | 500.00 | 5.00       | 30.30       | 0.00             | 23.26     | 500.00      |

## Project structure

### main.c
The program entry point for hardcoding data and using other files.

### allocator.c/.h
Allocation algorithm logic.

### ui.c/.h
User interface data formatting.

### config.h
Configuration data.

## Build
The program is written in ANSI C (C90) and can be compiled using GCC.

### Example build command
	gcc -std=c90 -Wall -Wextra -pedantic -O2 main.c allocator.c ui.c -o portfolio_allocator

### Example run command
	./portfolio_allocator

