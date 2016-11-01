# SUDOKU LISTER
The program gives a sorted list of all solutions that satisfy the
constraints of an input sudoku grid.

## EXAMPLES

    $ make
    $ ./sud 800000000003600000070090200050007000000045700000100030001000068008500010090000400

## USES

It can be used in mathematical exploration of properties of sudoku.
or as a *very* fast sudoku solver/generator.

## INPUT

INPUT sudoku grid (a 9x9 matrix) is given as first command line argument.
Its `char`s represent sudoku cells, in row order. All `char`s except
`'1'`-`'9'` are interpreted as empty cells. If the argument string is
smaller than 81 `char`s the rest of the cells are assumed to be empty.

## OUTPUT

The program lists *all* sudokus that satisfy the constraints expressed
in the INPUT sudoku grid, in form of 81 character strings, one on each
line.

If INPUT string specifies that all cells are empty (no constraint),
it will list *all* sudoku grids that exist.

"123456789" is the default first argument if none is given.

## DUMPING STATE OF COMPUTATION

If too many sudokus satisfy INPUT constraints, then listing of all 
solutions may take a lot of time. For this reason, a method to suspend
and resume the calculation is supported. A program can be suspended by
pressing Ctrl+C.

The keyboard interrupt signal (Ctrl+C) terminates the program after
dumping its state to a text file named `dump` in current directory.
Later, if the program is run without arguments and a file named
`dump` is present in the current directory, it tries to load state
from it and resume a previously suspended lising.

## ENUMERATING RESULTS

The program shows number of sudokus listed in each session on stderr,
i.e. the number of solutions found from resume/start to
suspension/termination of computation. You can keep track of them,
and add them up when required, to count all listed values in whole
computation. The counter will not overflow for any input string.

## PORTABILITY

The source code can be compiled on any platform that has an ANSI C
compiler with standard C library implemented.

Generated dump files may have to converted to properly encoded `char`s
on different platform.

## READING THE CODE

Some (very old but working) categorized source code is given in `extra/`
directory.  `extra/tut.c` is a tutorial, it tries to explain the algorithm.


## ME

This has took 4 years of my part time attention.
born out of my jealousy about a friend solving newspaper sudokus
faster than me. :D

Please point out if it does not work as exhibited. I will correct it.

I am in search of a computer with enough resources to undertake the task
of histogramming all sudokus.

or should i make a distributed system!?
but terabytes of data transfer?!
anyway.

webster15july@gmail.com
Fri Feb 28 00:38:23 IST 2014
pk
