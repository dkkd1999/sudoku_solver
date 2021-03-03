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
