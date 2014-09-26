typedef struct {
    s00d *s;
    int p;
    int v;
} state;
struct {
    char *buf;
    state *stack;
    int top;
    int pos;
} d;
int dmp(s00d *s, int p, int v){
    char *eye;
    b16 *sun;
    int l;

    for(l=0, eye=d.buf+d.pos, sun=s->i_v; l<405; sun++, eye+=5) l+=sprintf(eye, "%04x ", (int)*sun);

    l+=sprintf(eye, "%02x ", (int)s->left); eye+=3;
    l+=sprintf(eye, "%02x ", p); eye+=3;
    l+=sprintf(eye, "%02x\n", v);

    return l;//the characters written d.pos to be incremented outside
}
int burn(state *n){
    for(;n>=d.stack;n--) free(n->s);
    free(d.stack);
    d.stack=0;
    free(d.buf);
    d.buf=0;
    return 1;
}
#include <string.h>
void rq(int sig){
    fputs("\ndump requested\n", stderr);
    if(!(d.buf=malloc(81*414))) die("RAM denied");
    memset(d.buf, 0, 81*414);
}
int rd(){
    FILE *dump;
    int depth, i;
    char *line, *this, *nxt;
    b16 *eye;
    state *now;

    if(!(dump=fopen("dump", "rb"))) return 2;
    if(!(d.buf=(char *)malloc(81*414))) die("RAM denied\n");
    memset(d.buf, 0, 81*414);
    depth=fread(d.buf, 414, 81, dump); //if CRLF & fread doesnt copy the last incomplete line
    fclose(dump);
    if(!depth) return 1;

    if(!(d.stack=(state *)malloc(sizeof(state)*depth))) die("RAM denied\n");
    memset(d.stack, 0, sizeof(state)*depth);

    line=strtok(d.buf,"\r\n");
    d.top=0;
    while(line&&depth){
        now=d.stack+d.top;
        if(!(now->s=(s00d *)malloc(sizeof(s00d)))) die("RAM denied\n");
        for(i=0,this=line,eye=now->s->i_v;i<81;i++,eye++){
            *eye=(b16)strtoul(this,&nxt,16);
            if((this+5!=nxt)&&(i!=0||(this+4!=nxt))) return burn(now);
            this=nxt; 
        }
	now->s->left=(b8)strtoul(this,&nxt,16);
	if(this+3!=nxt) return burn(now);
	this=nxt;
	now->p=(b8)strtoul(this,&nxt,16);
	if(this+3!=nxt) return burn(now);
	this=nxt;
	now->v=(b8)strtoul(this,&nxt,16);
	if(this+3!=nxt) return burn(now);
        line=strtok(0,"\r\n");
	d.top++;
	depth--;
    }
    free(d.buf);
    d.buf=0;
    return 0;
}
