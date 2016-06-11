#include <stdio.h>
#include <stdlib.h>

void die(char *msg){
    fputs(msg, stderr);
    exit(0);
}

#include <string.h>

int main(int argc, char **argv) {
   int n=0,p,i, j,l; /* n=0 has one purpose */
   int *clr;
   if (argc>1) n=atoi(argv[1]);
   if (n<2||n>5) die("usage: only one arg 2,3,4 or 5\n"); 
   l=n*n*n*n;
   p=n*n*3-1-n*2;
   if (!(clr = malloc(l*p*sizeof(int)))) die("no RAM alloted\n");
   /* malloc from stdlib.h */
   scope_gen(n, clr);
   for(i=0;i<l;i++) {
     for(j=0;j<p;j++) printf("%d ", clr[i*p+j]);
     puts("");
   }
   free(clr);
   return 0;
}

int scope_gen(int n, int *clr){
   int i, j,
       r, c, gr, gc,
       l, p;
   int *eye;
   unsigned char *scope;

   l=n*n*n*n;
   if (!(scope = malloc(l*sizeof(unsigned char)))) die("no RAM alloted\n");
   /* malloc from stdlib.h */
   for (i=0, eye=clr;i<l;i++) {
      memset(scope, 0, l*sizeof(unsigned char)); /* from string.h */
      r=i/(n*n);
      c=i%(n*n);
      gr=(r/n)*n;
      gc=(c/n)*n;   
      for (j=0; j<n*n; j++) {
         scope[r*n*n+j]++;
         scope[j*n*n+c]++;
         scope[(gr+j/n)*n*n+gc+j%n]++;
      }
      scope[i]=0;
      for(j=0; j<l; j++) if (scope[j]) {*eye = j; eye++;}
   }
   free(scope);
   return 0;
}
/*  generates scope of each cell of sudoku like puzzles
    sudoku has 3 as its fundamental number
    this program accepts 2-5 as the fundamental number
*/
