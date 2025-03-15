# 2-SAT Solver in C++

This project implements a 2-Satisfiability (2-SAT) solver using strongly connected components (SCC) with Kosaraju's algorithm.

## Compilation

A `Makefile` is provided for easy compilation. To build the project, run:

```
make
```

## Running

After compilation, execute the solver with:

```
./2sat "(x1Vx2)&(x3V-x4)&(-x1V-x2)&(-x2Vx1)"
```

The input should contain a CNF formula with two literals per clause. The assignments are printed in the order that the variables are given in the input.

## Cleaning

- To remove compiled binaries and object files:

  ```
  make clean
  ```

- To remove only object files:

  ```
  make clean_objs
  ```
