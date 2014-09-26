typedef unsigned char b8;
/* to shorten frequent declarations */ 
typedef struct {
    b8 i_v[16];
    b8 left;
} d00d;
/*  the dudoku stucture :D */
/*  Statistically analysing a list of all sudokus was
    consuming huge effort, time and memory so i tried
    to change what is three in sudokus to two and 
    name it dudoku.
    Yes, that is cheap.
    Anyway.
    
    I hoped to find expressions for 
    generating such numbers and their distribution.
    Expressions, that are empirical and approximate, but
    faster and reasonably accurate.
    
    List of all dudokus turned out too small to
    allow any 'statistics'.
    
    Still, this well documented dudoku lister is an
    exact analogoue of sudoku lister code but
    a lot easier to grasp.
    
*/
b8 wait=0x8;
b8 open=0x4;
b8 may_b[4]={
    0x80, 0x40,
    0x20, 0x10
};
b8 data=0x3;
/*  masks to check state of cells 
*/  
b8 clr[16*7]={
    1,2,3,4,5,8,12,
    0,2,3,4,5,9,13,
    0,1,3,6,7,10,14,
    0,1,2,6,7,11,15,
    0,1,5,6,7,8,12,
    0,1,4,6,7,9,13,
    2,3,4,5,7,10,14,
    2,3,4,5,6,11,15,
    0,4,9,10,11,12,13,
    1,5,8,10,11,12,13,
    2,6,8,9,11,14,15,
    3,7,8,9,10,14,15,
    0,4,8,9,13,14,15,
    1,5,8,9,12,14,15,
    2,6,10,11,12,13,15,
    3,7,10,11,12,13,14
};
/*  scope of each cell in dudoku
    total 16 cells in dudoku
    7 cells in scope of each cell
    generated with scope.c
*/
  
b8 def[5]="1234";
b8 out[18]="";
/*  the default input argument and
    output string placeholder
*/
int first(d00d *puzl, b8 *p) {
    b8 * sun;
    for(sun=(&puzl->i_v[0]), *p=0; *p<16; (*p)++, sun++) if(((*sun)&wait)) return 1;
    return 0;
}
/*  gives the first unfilled cell to caller function
    required for generating sudokus in lexical order
*/
#include <stdlib.h>
void D00D(b8 *in, d00d *puzl) {
    b8 *eye, idea_v;
    b8 i;
    puzl->left = 16;
    eye = puzl->i_v;
    for(i=0; i<16 && *in; i++, eye++, in++) {
        if((idea_v=(*in)-'1')<4) *eye = idea_v|open|may_b[idea_v];
        else *eye = 0xfa;
    }
    for(;i<16;i++,eye++) *eye = 0xfa;
}
/*  constructs the sudoku structure from
    input string
*/
void STR(b8 *buf, d00d *puzl) {
    b8 *sun;
    b8 *eye;
    b8 i;
    eye=buf;
    for (sun=puzl->i_v, i=0; i<16; i++, sun++, eye++) {
        if ((*sun) & open) *eye = '?';
        else *eye = (b8)('1' + ((*sun) & data));
    }
    *eye = '\n';
    *(++eye) = '\0';
}
/*  prepares a printable string representing the
    input sudoku structure
*/
int idea(d00d *puzl, b8 *p, b8 *v) {
    b8 *sun;
    for (sun=puzl->i_v, *p=0; *p<16; (*p)++, sun++) {
        if ((*sun)&open) {
            *v=(b8)((*sun)&data);
            return 1;
        }
    }
    return 0;
}    
/*  gives the position of the first fillable cell in sudoku and
    the value to be filled in it
*/
int rm(b8 *eye, b8 v) {
    if ((*eye)&may_b[v]) {
        if (!((*eye)&wait)) return 1;
        (*eye)&=~may_b[v];
        (*eye)--;
        if((*eye)&open) {
            for(v=0; v<4; v++) if((*eye)&may_b[v]) break;
            (*eye) = ((b8)v)|open|may_b[v];
        }
    }
    return 0;
}
/*  removes probable from cell
*/
int trial(b8 *cell, b8 *v) {
    for(; *v<4; (*v)++) if((*cell)&may_b[*v]) return 1;
    return 0;
}
/*  gives the first probable of an unfilled cell
*/
#include <stdio.h>
int hook(d00d *puzl) {
    b8 x;
    b8 *eye; 
    b8 pos, val;
    while(idea(puzl, &pos, &val)) {
        for(x=0, eye=&clr[pos*7]; x<7; x++, eye++) {       
             if(rm(&(puzl->i_v[*eye]), val)) {
                 return -1;
             }
        }
        puzl->i_v[pos]&=(~open);
        if (!(--(puzl->left))) {
            STR(out,puzl);
            fputs(out ,stdout);
        }
    }
    return 1;
}
/*  deduces input sudoku cells until
    all logic is exhausted and
    sudoku becomes stagnant
*/
#include <stdlib.h>
int crook(d00d *master) {
    d00d *copy;
    b8 *mc, *cc;
    b8 pos, val=0, dummy;
    if(!(copy=(d00d *)malloc(sizeof(d00d)))) {
        fputs("crook: RAM denied, 0", stderr);
        exit(0);
    }    
    if(first(master, &pos)) {
        mc=&master->i_v[pos];
        cc=&copy->i_v[pos];
    } else return 0;
    while(trial(mc, &val)) {
        *copy=*master;
        *cc=(((b8)val)|open|may_b[val]);
        if(squash(copy)){
            rm(mc,val);
            /* should i check? :\ */
            if(idea(master, &pos, &dummy)&&(dummy>val)) {
                free(copy);
                return 1;
            }  
        } else val++;
    }
    free(copy);
    return 0;
}
/*  input is a stagnant dudoku
    makes a copy of it
    reports and returns to OS if it denies RAM
    picks the first unfilled cell to iterate guesses on
    lists all solutions for each probable of this cell
    removes a probable from original dudoku if
    it contradicts contraints
    if this removal gives an idea it
    releases RAM and returns 1
    after all probables are processed it releases RAM and
    returns 0
*/
    
    
    
    
int squash(d00d *puzl){
    do {
        switch(hook(puzl)){
            case 0: return 0;
            case -1: return 1;
        }
    } while (crook(puzl));
    return 0;
}
/*  solves input dudoku by hook or crook coroutines
    returns 1 if input is incorrect
*/
int main(int argc, char **argv){
    d00d *master;
    char *in;
    if(!(master = (d00d *)malloc(sizeof(d00d)))) {
        fputs("main: RAM denied, 0", stderr);
        return 0;
    }
    in=argc>1?argv[1]:def;
    D00D(in, master);
    if(squash(master)) fputs("invalid constraints\n",stderr);
    free(master);
    return 0;
}
/*  report and quit if OS denies RAM
    select default input if none given
    construct dudoku structure which models input
    list all possible dudokus satisfying given input constraints
    report if they are invalid 
    release RAM occupied
    return control to OS
*/
/* pk 20131117 0244  */
