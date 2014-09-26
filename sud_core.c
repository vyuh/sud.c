int first(s00d *puzl, b8 *p) {
    b16 * sun;
    for(sun=(&puzl->i_v[0]), *p=0; *p<81; (*p)++, sun++) if(((*sun)&wait)) return 1;
    return 0;
}
int idea(s00d *puzl, b8 *p, b8 *v) {
    b16 *sun;
    for (sun=puzl->i_v, *p=0; *p<81; (*p)++, sun++) {
        if ((*sun)&open) {
            *v=(b8)((*sun)&data);
            return 1;
        }
    }
    return 0;
}
int rm(b16 *eye, b8 v) {
    if ((*eye)&may_b[v]) {
        if (!((*eye)&wait)) return 1;
        (*eye)&=~may_b[v];
        (*eye)--;
        if((*eye)&open) {
            for(v=0; v<9; v++) if((*eye)&may_b[v]) break;
            (*eye) = ((b16)v)|open|may_b[v];
        }
    }
    return 0;
}
int trial(b16 *cell, b8 *v) {
    for(; *v<9; (*v)++) if((*cell)&may_b[*v]) return 1;
    return 0;
}

