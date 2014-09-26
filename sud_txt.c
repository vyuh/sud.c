void S00D(b8 *in, s00d *puzl) {
    b16 *eye, idea_v;
    b8 i;
    puzl->left = 81;
    eye = puzl->i_v;
    for(i=0; i<81 && *in; i++, eye++, in++) {
        if((idea_v=(*in)-'1')<9) *eye = idea_v|open|may_b[idea_v];
        else *eye = 0x7fe7;
    }
    for(;i<81;i++,eye++) *eye = 0x7fe7;
}
void STR(b8 *buf, s00d *puzl) {
    b16 *sun;
    b8 *eye;
    b8 i;
    eye=buf;
    for (sun=puzl->i_v, i=0; i<81; i++, sun++, eye++) {
        if ((*sun) & open) *eye = '?';
        else *eye = (b8)('1' + ((*sun) & data));
    }
    *eye = '\n';
    *(++eye) = '\0';
}
