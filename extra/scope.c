#include "../die.c" /* includes stdio.h and stdlib.h */
#include <string.h>

int *scope;
int main(int argc, char **argv) {
   int i,j,r,c,gr, gc, n=0,l,s,t; /* n=0 has one purpose */
   int *target;

   if (argc>1) n=atoi(argv[1]);
   if (n<2||n>5) die("usage: only one arg 2,3,4 or 5\n"); 

   l=n*n*n*n;
   if (!(scope = malloc(l*sizeof(int)))) die("no RAM alloted\n");  /* malloc from stdlib.h */
   for (i=0;i<l;i++) {
      memset(scope, 0, l*sizeof(int)); /* from string.h */
      r=i/(n*n);
      c=i%(n*n);
      gr=(r/n)*n;
      gc=(c/n)*n;   
      for (j=0; j<n*n; j++) {
         t=r*n*n+j;
         scope[t]++;
         t=j*n*n+c;
         scope[t]++;
         t=(gr+j/n)*n*n+gc+j%n;
         scope[t]++;
      }
      scope[i]=0;
      for(j=0; j<l; j++) if (scope[j]) printf("%d ",j); /* from stdio.h */
      putchar('\n');
   }
   return 0;
}
/*  generates scope of each cell of sudoku like puzzles
    sudoku has 3 as its fundamental number
    this program accepts 2-5 as the fundamental number
*/
    
