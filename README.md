# sudoku_solver
数独ソルバをC++で実装してみました.  
9x9の数独を1秒位で解きます.  
DFSを使用したので総当りよりかは早いはず.  
尚入力及び出力は改行しないで, 空白部分は0を入力してください.

実行例:
~~~bash
$ g++ solver.cpp -o solve
$ ./solve 
800000000003600000070090200050007000000045700000100030001000068008500010090000400
812753649943682175675491283154237896369845721287169534521974368438526917796318452
~~~

気が向いたら16x16もできるようにするつもり.

(追記)実装しました.

実行例:
$ g++ solver_ecp.cpp -o solve
$ ./solve 
13 0 0 0 3 4 1 2 6 0 0 15 0 0 8 0
0 1 0 10 0 11 0 0 2 0 5 16 0 0 15 7
2 0 16 15 7 0 0 13 11 4 3 8 10 5 0 0
0 6 0 4 0 15 0 5 7 0 0 1 12 0 3 0
0 0 15 12 0 0 0 8 13 0 7 0 0 0 2 9
0 0 0 0 0 12 0 0 0 6 0 0 0 0 0 0
0 0 3 0 0 0 2 0 5 0 0 14 0 12 0 0 
6 0 4 0 10 0 0 0 0 0 9 12 0 0 0 0 
0 0 0 0 13 0 0 0 0 0 0 6 0 0 0 0
0 0 8 0 6 0 0 1 15 0 0 5 0 3 14 0
0 2 0 0 0 0 0 0 12 0 0 4 16 0 13 10
0 0 0 0 15 0 0 12 9 0 0 13 0 0 0 0
12 0 0 0 11 0 0 0 0 5 0 0 0 0 9 2
0 10 0 0 0 6 5 16 0 0 1 0 0 0 0 0
0 7 6 0 0 0 14 15 4 0 12 3 0 0 16 11
0 13 9 0 0 0 12 0 0 14 0 0 0 0 4 0

13 9 7 5 3 4 1 2 6 12 10 15 14 11 8 16 
3 1 14 10 12 11 8 6 2 13 5 16 9 4 15 7 
2 12 16 15 7 14 9 13 11 4 3 8 10 5 6 1 
8 6 11 4 16 15 10 5 7 9 14 1 12 2 3 13 
16 14 15 12 5 3 6 8 13 11 7 10 4 1 2 9 
7 11 13 1 14 12 15 9 3 6 4 2 8 16 10 5 
10 8 3 9 1 7 2 4 5 16 15 14 13 12 11 6 
6 5 4 2 10 16 13 11 1 8 9 12 3 14 7 15 
4 15 12 7 13 5 11 3 14 10 16 6 2 9 1 8 
9 16 8 13 6 10 4 1 15 7 2 5 11 3 14 12 
1 2 5 6 8 9 7 14 12 3 11 4 16 15 13 10 
14 3 10 11 15 2 16 12 9 1 8 13 6 7 5 4 
12 4 1 14 11 8 3 10 16 5 13 7 15 6 9 2 
11 10 2 3 4 6 5 16 8 15 1 9 7 13 12 14 
5 7 6 8 9 13 14 15 4 2 12 3 1 10 16 11 
15 13 9 16 2 1 12 7 10 14 6 11 5 8 4 3 
