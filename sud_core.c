int sudoku_first_waiting_cell (sudoku * puzzle, unsigned char *p) {
  unsigned short *sun;
  for (sun = (&puzzle->i_v[0]), *p = 0; *p < 81; (*p)++, sun++)
    if (((*sun) & WAIT))
      return 1;
  return 0;
}
int sudoku_cell_to_fill (sudoku * puzzle, unsigned char *p, unsigned char *v) {
  unsigned short *sun;
  for (sun = puzzle->i_v, *p = 0; *p < 81; (*p)++, sun++) {
    if ((*sun) & OPEN) {
      *v = (unsigned char) ((*sun) & data);
      return 1;
    }
  }
  return 0;
}
int remove_probable (unsigned short *eye, unsigned char v) {
  if ((*eye) & MAY_B[v]) {
    if (!((*eye) & WAIT))
      return 1;
    (*eye) &= ~MAY_B[v];
    (*eye)--;
#ifdef LOG
    fprintf(stderr, "LOG remove_probable: removed_current_probable\n");
#endif
    if ((*eye) & OPEN) {
      for (v = 0; v < 9; v++)
        if ((*eye) & MAY_B[v])
          break;
      (*eye) = ((unsigned short) v) | OPEN | MAY_B[v];
#ifdef LOG
      fprintf(stderr, "LOG remove_probable: marked_logical_idea, value: %d\n", v);
#endif
    }
  }
  return 0;
}
int cell_value_to_try (unsigned short *cell, unsigned char *v) {
  for (; *v < 9; (*v)++)
    if ((*cell) & MAY_B[*v])
      return 1;
  return 0;
}
