SUDOKU LISTER
=============
The program gives a sorted list of all solutions that satisfy the
constraints of an input sudoku grid.

EXAMPLES
--------

    $ cc sud.c
    $ ./a.out 800000000003600000070090200050007000000045700000100030001000068008500010090000400

USES
----

it can be used in mathematical exploration of properties of sudoku.
or as a *very* fast sudoku solver/generator.

INPUT
-----
INPUT sudoku grid (a 9x9 matrix) is given as first command line argument.
Its `char`s represent sudoku cells, in row order. All `char`s except
`'1'`-`'9'` are interpreted as empty cells. If the argument string is
smaller than 81 `char`s the rest of the cells are assumed to be empty.

OUTPUT
------
The program lists *all* sudokus that satisfy the constraints expressed
in the INPUT sudoku grid, in form of 81 character strings, one on each
line.

If INPUT string specifies that all cells are empty (no constraint),
it will list *all* possible sudoku grids.

"123456789" is the default first argument if none is given.

DUMPING STATE OF COMPUTATION
----------------------------
If too many sudokus satisfy INPUT constraints, then computation
(and listing) of *all* solution can take a lot of time (and memory).

The keyboard interrupt signal (Ctrl+C) terminates the program after
dumping its state to a text file named `dump` in current directory.
Later, if the program is run without arguments and a file named
`dump` is present in the current directory, it tries to load state
from it and resume a previously suspended computation.

ENUMERATING RESULTS
-------------------
The program shows number of sudokus listed in each session on stderr,
i.e. the number of solutions found from resume/start to
suspension/termination of computation. You can keep track of them,
and add them up when required, to count all listed values in whole
computation. The counter will not overflow for any input string.

PORTABILITY
-----------
The source code can be compiled on any platform that has an ANSI C
compiler with standard C library implemented.

Generated dump files may have to converted to properly encoded `char`s
on different platform.

READING THE CODE
----------------
Some (very old but working) categorized source code is given in src/
directory.  src/extra/tut.c is a tutorial tries to explain the algorithm.


ME
-----
this has took 4 years of my part time attention.
born out of my jealousy about a friend solving newspaper sudokus
faster than me. :D

please point out if it does not work as exhibited. i will correct it.

i am in search of a computer with enough resources to undertake the task
of histogramming all sudokus.

or should i make a distributed system!?
but terabytes of data transfer?!
anyway.

webster15july@gmail.com
Fri Feb 28 00:38:23 IST 2014
pk
