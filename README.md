# Portfolio Allocator
A C90 tool that allocates contribution between created financial asstes according to given percentages of total value using equalization algorithm.

## Purpose
When investing in many different financial assets and making strategic decisions about target percentages of total portfolio value for each asset after some time we encounter an allocation problem. Since different financial assets change their value over time independently from each other they hardly ever maintain their target percentage in portfolio. Every time we want to make an additional contribution we need to think about how to allocate our funds to stay consistent with our strategy. Spliting our contribution across assets just by using target percentages as ratio to that process is naive as it does not work in broder time horizon. This tool is made to address this problem, help in allocation of new funds between financial assets in a way that is more correct than simplier methods and to rise consistency in a realization of given strategy.

## Algorithm
The algorithm is based on increasing additonal percantage of each asset by calculation of fulfillemnt level for every asset by using given contribution. Fulfillment level is a value that indicates how far from target percantage current value of an assets is. It is calculated based on given value of the asset, target percentage of the asset and total value of the portfolio including new contribution(total value of all assets combined + contribution). Total percentage of all assets in portfolio is less than 100% as contribution is contained within total value of the portfolio and has it's own percantage(additonal percentages). Algorithm aims to discribute that percentage across assets. After calculation of fulfillment level for each asset it is possible to state to which asset the funds should go in the first place and how much of the contribution percantage should be put in that asset. It is done by finding assets with the smallest fulfillemnt level and the second smallest fullfillment level. Then the fulfillment level of the asset with the smallest fullfilment level is substracted from the asset with the second smallest fulfillment level. Obtained value indicates by how much the smallest fulfillemnt can be increased before it is no longer the smallest. Using that information additonal percantage of the least fulfilled asset is increased by the value of multiplication of target percentage and substraction value. Also the same value is substracted from additional percentages. At that point there are two assets with the smallest fulfillment level. Next, the steps are repeated, but this time for three assets. Common value of the fulfillment level of the least fulfilled assets is substracted from value of the fulfillment level of the second least fulfilled asset. Again, the additional percentage of each asset is increased by the value of the multiplication. This time additional percenteges is decreased by sum of the multiplication values. This proccess continues till all assets have the same fullfilment level or substraction from additional percentages is no longer possible as it would decrease it below zero. If all assets have the same level of fullfilement level rest of the additional percentages is distributed between all assets in ratio described by target precentages of each asset. If substraction from additional percenteges is not possible at some point additonal percentage for each asset that takes part in increasing fulfillment level is adjusted in a way that sum of multiplication values is equal to adittional percentages. After this proccess additional value for each asset is calculated by multiplication of total value of portfolio and additional percentage of each asset and is displayed for the user. The algorithm only distributes given contribution betwen assets and do not sell any.

## Features
1. C90 compliance
2. Contribution-only allocation
3. No selling
4. Unlimited asset creation
5. Table data display

## Limitations
1. Target percentage must be non-negative.
2. Allocation does not include additional fees that may come with purchase of certain assets.
3. Sum of target percentages of all assets must be equal 100%.
4. Algorithm is not selling assets.
5. Value of each asset must be non-negative.
6. Amount of assets needs to be given.
7. Data for allocation needs to be hardcoded.

## Usage
In "main.c" data for allocation needs to be hardcoded. Describtion of how to do it is there.

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
