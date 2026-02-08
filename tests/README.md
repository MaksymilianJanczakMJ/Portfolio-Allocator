# TESTS
Directories contain data for extreme cases.

## few assets


### Input `data.txt`
    500
    Example 1.;1700;0.6
    Example 2.;400;0.4

### Terminal output
    | Asset name     | Value   | Target [%] | Current [%] | Additional value | After [%] | After value |
    |================|=========|============|=============|==================|===========|=============|
    |     Example 1. | 1700.00 | 60.00      | 80.95       | 0.00             | 65.38     | 1700.00     |
    |     Example 2. | 400.00  | 40.00      | 19.05       | 500.00           | 34.62     | 900.00      |
    Total value after contribution: 2600.00.
    
    Process finished with exit code 0

### File output `out.txt`
    Example 1.;0.809524;0.00;0.653846;1700.00;
    Example 2.;0.190476;500.00;0.346154;900.00;

## high contribution


### Input `data.txt`
    1000000
    Example 1.;1300;0.4
    Example 2.;400;0.25
    Example 3.;700;0.15
    Example 4.;200;0.2

### Terminal output
    | Asset name | Value   | Target [%] | Current [%] | Additional value | After [%] | After value |
    |============|=========|============|=============|==================|===========|=============|
    | Example 1. | 1300.00 | 40.00      | 50.00       | 399740.00        | 40.00     | 401040.00   |
    | Example 2. | 400.00  | 25.00      | 15.38       | 250250.00        | 25.00     | 250650.00   |
    | Example 3. | 700.00  | 15.00      | 26.92       | 149690.00        | 15.00     | 150390.00   |
    | Example 4. | 200.00  | 20.00      | 7.69        | 200320.00        | 20.00     | 200520.00   |
    Total value after contribution: 1002600.00.
    
    Process finished with exit code 0

### File output `out.txt`
    Example 1.;0.500000;399740.00;0.400000;401040.00;
    Example 2.;0.153846;250250.00;0.250000;250650.00;
    Example 3.;0.269231;149690.00;0.150000;150390.00;
    Example 4.;0.076923;200320.00;0.200000;200520.00;


## high value


### Input `data.txt`
    5000000
    Example 1.;52000000000;0.4
    Example 2.;37000000000;0.25
    Example 3.;8000000000;0.15
    Example 4.;12000000000;0.2

### Terminal output
    | Asset name | Value          | Target [%] | Current [%] | Additional value | After [%] | After value    |
    |============|================|============|=============|==================|===========|================|
    | Example 1. | 52000000000.00 | 40.00      | 47.71       | 0.00             | 47.70     | 52000000000.00 |
    | Example 2. | 37000000000.00 | 25.00      | 33.94       | 0.00             | 33.94     | 37000000000.00 |
    | Example 3. | 8000000000.00  | 15.00      | 7.34        | 5000000.00       | 7.34      | 8005000000.00  |
    | Example 4. | 12000000000.00 | 20.00      | 11.01       | 0.00             | 11.01     | 12000000000.00 |
    Total value after contribution: 109005000000.00.
    
    Process finished with exit code 0

### File output `out.txt`
    Example 1.;0.477064;0.00;0.477042;52000000000.00;
    Example 2.;0.339450;0.00;0.339434;37000000000.00;
    Example 3.;0.073394;5000000.00;0.073437;8005000000.00;
    Example 4.;0.110092;0.00;0.110087;12000000000.00;

## high value spread


### Input `data.txt`
    3000
    Example 1.;900000;0.399
    Example 2.;80000;0.25
    Example 3.;700;0.15
    Example 4.;2;0.2
    Example 5.;0.01;0.001

### Terminal output
    | Asset name | Value     | Target [%] | Current [%] | Additional value | After [%] | After value |
    |============|===========|============|=============|==================|===========|=============|
    | Example 1. | 900000.00 | 39.90      | 91.77       | 0.00             | 91.49     | 900000.00   |
    | Example 2. | 80000.00  | 25.00      | 8.16        | 0.00             | 8.13      | 80000.00    |
    | Example 3. | 700.00    | 15.00      | 0.07        | 882.06           | 0.16      | 1582.06     |
    | Example 4. | 2.00      | 20.00      | 0.00        | 2107.41          | 0.21      | 2109.41     |
    | Example 5. | 0.01      | 0.10       | 0.00        | 10.54            | 0.00      | 10.55       |
    Total value after contribution: 983702.01.
    
    Process finished with exit code 0

### File output `out.txt`
    Example 1.;0.917710;0.00;0.914911;900000.00;
    Example 2.;0.081574;0.00;0.081325;80000.00;
    Example 3.;0.000714;882.06;0.001608;1582.06;
    Example 4.;0.000002;2107.41;0.002144;2109.41;
    Example 5.;0.000000;10.54;0.000011;10.55;


## many assets


### Input `data.txt`
    30000
    Example 1.;12000;0.03
    Example 2.;3700;0.07
    Example 3.;4500;0.02
    Example 4.;15600;0.06
    Example 5.;650;0.05
    Example 6.;7700;0.04
    Example 7.;8460;0.08
    Example 8.;3100;0.01
    Example 9.;9900;0.09
    Example 10.;5600;0.04
    Example 11.;14300;0.06
    Example 12.;7500;0.05
    Example 13.;2300;0.03
    Example 14.;450;0.07
    Example 15.;5100;0.02
    Example 16.;11000;0.06
    Example 17.;10500;0.04
    Example 18.;4300;0.05
    Example 19.;6400;0.02
    Example 20.;3700;0.11

### Terminal output
    | Asset name  | Value    | Target [%] | Current [%] | Additional value | After [%] | After value |
    |=============|==========|============|=============|==================|===========|=============|
    | Example 1.  | 12000.00 | 3.00       | 8.77        | 0.00             | 7.20      | 12000.00    |
    | Example 2.  | 3700.00  | 7.00       | 2.71        | 4376.73          | 4.84      | 8076.73     |
    | Example 3.  | 4500.00  | 2.00       | 3.29        | 0.00             | 2.70      | 4500.00     |
    | Example 4.  | 15600.00 | 6.00       | 11.41       | 0.00             | 9.35      | 15600.00    |
    | Example 5.  | 650.00   | 5.00       | 0.48        | 5119.09          | 3.46      | 5769.09     |
    | Example 6.  | 7700.00  | 4.00       | 5.63        | 0.00             | 4.62      | 7700.00     |
    | Example 7.  | 8460.00  | 8.00       | 6.19        | 770.55           | 5.54      | 9230.55     |
    | Example 8.  | 3100.00  | 1.00       | 2.27        | 0.00             | 1.86      | 3100.00     |
    | Example 9.  | 9900.00  | 9.00       | 7.24        | 484.36           | 6.23      | 10384.36    |
    | Example 10. | 5600.00  | 4.00       | 4.09        | 0.00             | 3.36      | 5600.00     |
    | Example 11. | 14300.00 | 6.00       | 10.46       | 0.00             | 8.58      | 14300.00    |
    | Example 12. | 7500.00  | 5.00       | 5.48        | 0.00             | 4.50      | 7500.00     |
    | Example 13. | 2300.00  | 3.00       | 1.68        | 1161.45          | 2.08      | 3461.45     |
    | Example 14. | 450.00   | 7.00       | 0.33        | 7626.73          | 4.84      | 8076.73     |
    | Example 15. | 5100.00  | 2.00       | 3.73        | 0.00             | 3.06      | 5100.00     |
    | Example 16. | 11000.00 | 6.00       | 8.04        | 0.00             | 6.60      | 11000.00    |
    | Example 17. | 10500.00 | 4.00       | 7.68        | 0.00             | 6.30      | 10500.00    |
    | Example 18. | 4300.00  | 5.00       | 3.14        | 1469.09          | 3.46      | 5769.09     |
    | Example 19. | 6400.00  | 2.00       | 4.68        | 0.00             | 3.84      | 6400.00     |
    | Example 20. | 3700.00  | 11.00      | 2.71        | 8992.00          | 7.61      | 12692.00    |
    Total value after contribution: 166760.00.
    
    Process finished with exit code 0

### File output `out.txt`
    Example 1.;0.087745;0.00;0.071960;12000.00;
    Example 2.;0.027055;4376.73;0.048433;8076.73;
    Example 3.;0.032904;0.00;0.026985;4500.00;
    Example 4.;0.114068;0.00;0.093548;15600.00;
    Example 5.;0.004753;5119.09;0.034595;5769.09;
    Example 6.;0.056303;0.00;0.046174;7700.00;
    Example 7.;0.061860;770.55;0.055352;9230.55;
    Example 8.;0.022667;0.00;0.018590;3100.00;
    Example 9.;0.072390;484.36;0.062271;10384.36;
    Example 10.;0.040948;0.00;0.033581;5600.00;
    Example 11.;0.104563;0.00;0.085752;14300.00;
    Example 12.;0.054841;0.00;0.044975;7500.00;
    Example 13.;0.016818;1161.45;0.020757;3461.45;
    Example 14.;0.003290;7626.73;0.048433;8076.73;
    Example 15.;0.037292;0.00;0.030583;5100.00;
    Example 16.;0.080433;0.00;0.065963;11000.00;
    Example 17.;0.076777;0.00;0.062965;10500.00;
    Example 18.;0.031442;1469.09;0.034595;5769.09;
    Example 19.;0.046797;0.00;0.038379;6400.00;
    Example 20.;0.027055;8992.00;0.076109;12692.00;

## small contribution


### Input `data.txt`
    0.13
    Example 1.;12000;0.4
    Example 2.;3700;0.25
    Example 3.;4500;0.35

### Terminal output
    | Asset name | Value    | Target [%] | Current [%] | Additional value | After [%] | After value |
    |============|==========|============|=============|==================|===========|=============|
    | Example 1. | 12000.00 | 40.00      | 59.41       | 0.00             | 59.41     | 12000.00    |
    | Example 2. | 3700.00  | 25.00      | 18.32       | 0.00             | 18.32     | 3700.00     |
    | Example 3. | 4500.00  | 35.00      | 22.28       | 0.13             | 22.28     | 4500.13     |
    Total value after contribution: 20200.13.
    
    Process finished with exit code 0

### File output `out.txt`
    Example 1.;0.594059;0.00;0.594056;12000.00;
    Example 2.;0.183168;0.00;0.183167;3700.00;
    Example 3.;0.222772;0.13;0.222777;4500.13;

## small value


### Input `data.txt`
    0.75
    Example 1.;2.47;0.4
    Example 2.;0.27;0.25
    Example 3.;1.23;0.35

### Terminal output
    | Asset name | Value | Target [%] | Current [%] | Additional value | After [%] | After value |
    |============|=======|============|=============|==================|===========|=============|
    | Example 1. | 2.47  | 40.00      | 62.22       | 0.00             | 52.33     | 2.47        |
    | Example 2. | 0.27  | 25.00      | 6.80        | 0.67             | 19.86     | 0.94        |
    | Example 3. | 1.23  | 35.00      | 30.98       | 0.08             | 27.81     | 1.31        |
    Total value after contribution: 4.72.
    
    Process finished with exit code 0

### File output `out.txt`
    Example 1.;0.622166;0.00;0.523305;2.47;
    Example 2.;0.068010;0.67;0.198623;0.94;
    Example 3.;0.309824;0.08;0.278072;1.31;


## small value spread


### Input `data.txt`
    25
    Example 1.;100.01;0.2
    Example 2.;100;0.2
    Example 3.;99.99;0.2
    Example 4.;101;0.2
    Example 5.;99.75;0.2

### Terminal output
    | Asset name | Value  | Target [%] | Current [%] | Additional value | After [%] | After value |
    |============|========|============|=============|==================|===========|=============|
    | Example 1. | 100.01 | 20.00      | 19.97       | 5.14             | 20.00     | 105.15      |
    | Example 2. | 100.00 | 20.00      | 19.97       | 5.15             | 20.00     | 105.15      |
    | Example 3. | 99.99  | 20.00      | 19.97       | 5.16             | 20.00     | 105.15      |
    | Example 4. | 101.00 | 20.00      | 20.17       | 4.15             | 20.00     | 105.15      |
    | Example 5. | 99.75  | 20.00      | 19.92       | 5.40             | 20.00     | 105.15      |
    Total value after contribution: 525.75.
    
    Process finished with exit code 0

### File output `out.txt`
    Example 1.;0.199720;5.14;0.200000;105.15;
    Example 2.;0.199700;5.15;0.200000;105.15;
    Example 3.;0.199680;5.16;0.200000;105.15;
    Example 4.;0.201697;4.15;0.200000;105.15;
    Example 5.;0.199201;5.40;0.200000;105.15;