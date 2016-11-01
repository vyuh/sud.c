typedef struct {
  unsigned short i_v[81];
  unsigned char left;
} sudoku;
unsigned short wait = 0x20;
unsigned short open = 0x10;
unsigned short may_b[9] = {
  0x4000, 0x2000, 0x1000,
  0x0800, 0x0400, 0x0200,
  0x0100, 0x0080, 0x0040
};
unsigned short data = 0xf;
#include <string.h>
int scope_gen (unsigned char scope[81 * 20]) {
  unsigned char i, j, r, c, gr, gc;
  unsigned char *eye;
  unsigned char scope_seive[81];
  /* malloc from stdlib.h */
  for (i = 0, eye = scope; i < 81; i++) {
    memset (scope_seive, 0, 81 * sizeof (unsigned char));
    /* from string.h */
    r = i / (9);
    c = i % (9);
    gr = (r / 3) * 3;
    gc = (c / 3) * 3;
    for (j = 0; j < 9; j++) {
      scope_seive[r * 9 + j]++;
      scope_seive[j * 9 + c]++;
      scope_seive[(gr + j / 3) * 9 + gc + j % 3]++;
    }
    scope_seive[i] = 0;
    for (j = 0; j < 81; j++)
      if (scope_seive[j]) {
        *eye = j;
        eye++;
      }
  }
  return 0;
}
unsigned char scope[81 * 20];
