# csp2sat

csp2sat is a full C++ program based on Tamura's et al. "Compiling finite linear CSP into SAT" (2008).

## Principle

Briefly, the paper introduces the 'order encoding', a method which basically transforms any input inequation aixi <= b into a set of elementary "primitive" ones (x <= a). 

Each of these primitive comparisons are then encoded into literal p(x,i) that represents x <= i.

## How-to-use

In the main program there is an example of the encoding of the following inequation : 3x + 5y + 2z + t <= 14.

The clauses are written in a file (dimacs formatted) and can be tested with any sat solver.

## Usage

```
mkdir bin
mkdir obj
make
./bin/csp2sat
```
..Voilà!
