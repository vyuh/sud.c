#include "die.c"
#include "sud_ds.c"
#include "sud_dmp.c"
#include "iint.c"
#include "sud_core.c"
#include "sud_txt.c"

b8 out[83]="";
iint *cnt;
int hook(s00d *puzl) {
    b8 x;
    b8 *eye; 
    b8 pos, val;
    if(d.stack) {
        if(d.top) return 0;
        free(d.stack);
	d.stack=0;
	d.top=-1;
        return 1;
    }
    while(idea(puzl, &pos, &val)) {
        for(x=0, eye=&clr[pos*20]; x<20; x++, eye++) {       
             if(rm(&(puzl->i_v[*eye]), val)) return -1;
        }
        puzl->i_v[pos]&=(~open);
        if (!(--(puzl->left))) {
            STR(out,puzl);
            fputs(out ,stdout);
            add(cnt,1L); //cant possibly overflow, should i check?
            if(d.buf){
		d.pos=0;
                return 2;
            } else return 1;
        }
    }
    return 0;
}
int crook(s00d *master) {
    s00d *copy;
    b16 *mc, *cc;
    b8 pos, val=0, dummy;
    if(d.stack){
	if(!d.top--) die("stack underflow");
        copy=(d.stack+d.top)->s;
	pos=(b8)(d.stack+d.top)->p;
	val=(b8)(d.stack+d.top)->v;
        mc=&master->i_v[pos];
        cc=&copy->i_v[pos];
    } else {
        if(!(copy=(s00d *)malloc(sizeof(s00d)))) die("RAM denied\n");
        if(first(master, &pos)) {
            mc=&master->i_v[pos];
            cc=&copy->i_v[pos];
        } else return 1;
    }
    while(d.stack||trial(mc, &val)) {
        if(!d.stack){
            *copy=*master;
            *cc=(((b16)val)|open|may_b[val]);
        }
        switch(squash(copy)){
            case 1:
	    val++;
	    break;
            case 2:
	    d.pos+=dmp(copy, (int)pos, (int)val);
            return 2;
            case -1:
            rm(mc,val);
            /* should i check? */
            if(idea(master, &pos, &dummy)&&(dummy>val)) {
                free(copy);
                return 0;
            }
        }
    }
    free(copy);
    return 1;
}
int squash(s00d *puzl){
    int ret;
    do if(ret=hook(puzl)) return ret; while (!(ret=crook(puzl)));
    return ret;
}
