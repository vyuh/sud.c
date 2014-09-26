typedef struct {
    unsigned long *i;
    unsigned int n;
} iint;


iint *new (unsigned bound) {
    long szl;
    iint *egg;
    if(!(egg=malloc(sizeof(iint)))) die("RAM denied\n"); 
    szl=sizeof(long);
    egg->n=bound/szl+((bound%szl)&&1);
    if(!(egg->i=malloc(egg->n*szl))) die("RAM denied\n");
    memset(egg->i, 0, egg->n*szl);
    return egg;
}


int add(iint *eye, unsigned long x) {
    int ret=0;
    *(eye->i)+=x;
    if (*(eye->i)<x){
        if(--(eye->n)){
            eye->i++;
            ret=add(eye, 1L);
            eye->i--;
        } else ret=1; 
        (eye->n)++;
    }
    return ret;
}

int vyu(char *eye, iint *num) {
    static char zp_lu[7];
    unsigned i;
    i=num->n;
    sprintf(zp_lu, "%%0%lulx", 2*sizeof(unsigned long)); 
    while(i--) eye+=sprintf(eye, zp_lu, num->i[i]); // woah!
    strcat(eye,"\n");
    return 0;
}
