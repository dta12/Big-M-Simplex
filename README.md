# Big-M-Simplex
This program is a linear optimization solver that uses the Big M Simplex Algorithm.  
**Warning**:  
DO NOT USE THIS ON HOMEWORK. I AM NOT RESPONSIBLE IF YOU FAIL. THIS PROJECT IS A WORK IN PROGRESS.
## How to run: 
1. To compile run the command:  
   `gcc -o simplex simplex.c tabelau.c tokenizer.c`
3. To start the program run the command  
   ```./simplex``` or ```./simplex.exe```  
   depending on compiler and OS.  
## Sample output
This output is from running the current `eq.txt` file in the repository.  
```
1.0     2.0     1.0     0.0     0.0     40.0
2.0     3.0     0.0     1.0     0.0     72.0
-60.0   -90.0   0.0     0.0     1.0     0.0
MAX P = 0.0
------------------------------------------------
Iteration: 1    Pivot chosen: (r: 1, c: 2)
0.5     1.0     0.5     0.0     0.0     20.0
0.5     0.0     -1.5    1.0     0.0     12.0
-15.0   0.0     45.0    0.0     1.0     1800.0
MAX P = 1800.0
------------------------------------------------
Iteration: 2    Pivot chosen: (r: 2, c: 1)
0.0     1.0     2.0     -1.0    0.0     8.0
1.0     0.0     -3.0    2.0     0.0     24.0
0.0     0.0     0.0     30.0    1.0     2160.0
The optimal solution has been found
0.0     1.0     2.0     -1.0    0.0     8.0
1.0     0.0     -3.0    2.0     0.0     24.0
0.0     0.0     0.0     30.0    1.0     2160.0
MAX P = 2160.0
```
