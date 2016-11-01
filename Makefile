all: amalgamation
	gcc -Ofast -pedantic-errors sud_amalgamation.c -o sud
amalgamation: LICENSE die.c sud_ds.c sud_dmp.c iint.c sud_core.c sud_txt.c sud_squash.c sud.c
	cat $+ | grep -v '#include "' > sud_amalgamation.c

