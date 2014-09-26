#include "sud_squash.c"
b8 def[10]="123456789";
int main(int argc, char **argv){
    s00d *master;
    char *in;
    FILE *dump;

    d.buf=d.stack=0;
    d.pos=d.top=-1;

    if(argc>1) {
        in=argv[1];
    } else {
        if(rd()) in=def; else {
            d.top--;
            master=(d.stack+d.top)->s;
        }
    }

#include <signal.h>
    if(!d.stack) {
        if(!(master=(s00d *)malloc(sizeof(s00d)))) die("RAM denied\n");
        S00D(in, master);
    }

    if(signal(SIGINT, rq)==SIG_ERR) fputs("could not enable dump feature\n", stderr);
    else fputs("dump feature enabled\n", stderr);

    cnt=new(10);
        
    switch(squash(master)) {
        case -1:
        fputs("no solution\n",stderr);
        break;
        case 2:
        dmp(master,10,10);
        if(!(dump=fopen("dump","wb"))) die("couldn't create dumpfile\n");
        //rather dump to stderr
        fputs(d.buf, dump);
        fclose(dump);
        free(d.buf);
    }
    free(master);

    *out='#'; vyu(out+1, cnt); // haha! passing a global :D
    fputs(out, stderr);

    return 0;
}
/* pk 20140124 0246 */
