int best(s00d *puzl, b8 *p) {
    b8 x, level;
    b16 * sun;
    for(sun=(&puzl->i_v[0]),level=9, x=0; x<81; x++, sun++) {
        if(((*sun)&wait)) {
            if(((*sun)&data)<level) {
                level=(b8)(*sun&data);
                *p=x;
            }
        }
    }
    return level<9;
}
/*  returns the cell with minimum 
    number of probables
    converges to a solution faster
    than selecting the first empty cell
*/

int (*f[2])(s00d *puzl,b8 *p)={first, best};
