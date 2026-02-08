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
4. In-file contribution declarationa and asset creation
5. Output in file-format and table-format for terminal
6. If the target percentage is negative, it will be set to zero.
7. If the asset value is negative, it will be set to zero.

## Limitations
1. Allocation does not include transaction fees.
2. Target percentages of all assets must sum to 100%.

## Usage
1. In `data.txt` data for allocation must be declared.
2. In the file first line represents the contribution value.
3. Rest of the lines represent assets, one for each line.
4. The Assets are described as follows `asset_name;value;target_percentage`. 

### Example:

#### Input `data.txt`
	1000
	Example 1.;1300;0.4
	Example 2.;400;0.25
	Example 3.;700;0.15
	Example 4.;200;0.2

#### Terminal output
	| Asset name | Value   | Target [%] | Current [%] | Additional value | After [%] | After value |
	|============|=========|============|=============|==================|===========|=============|
	| Example 1. | 1300.00 | 40.00      | 50.00       | 64.71            | 37.91     | 1364.71     |
	| Example 2. | 400.00  | 25.00      | 15.38       | 452.94           | 23.69     | 852.94      |
	| Example 3. | 700.00  | 15.00      | 26.92       | 0.00             | 19.44     | 700.00      |
	| Example 4. | 200.00  | 20.00      | 7.69        | 482.35           | 18.95     | 682.35      |
	Total value after contribution: 3600.00.
    
    Process finished with exit code 0

#### File output `out.txt`
	Example 1.;0.500000;64.71;0.379085;1364.71;
	Example 2.;0.153846;452.94;0.236928;852.94;
	Example 3.;0.269231;0.00;0.194444;700.00;
	Example 4.;0.076923;482.35;0.189542;682.35;

## Project structure

### main.c
The program entry point for using other files.

### allocator.c/.h
Allocation algorithm logic.

### ui.c/.h
User interface data formatting.

### config.h
Configuration data and declaration of structures and unions.

### file_reader.c/.h
File reading and data formating algorithm.

### file_writer.c/.h
After-allocation data to file writing algorithm.


## Build
The program is written in ANSI C (C90) and can be compiled using GCC.

### Example build command
	gcc -std=c90 -Wall -Wextra -pedantic -O2 main.c allocator.c ui.c -o portfolio_allocator

### Example run command
	./portfolio_allocator

## Tests
`tests` directory consists of tests for extreme cases where algorithm could act in unpredictable maner.

