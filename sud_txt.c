void sudoku_init (char *in, sudoku * puzzle) {
  unsigned short *eye, idea_v;
  unsigned char i;
  puzzle->left = 81;
  eye = puzzle->i_v;
  for (i = 0; i < 81 && *in; i++, eye++, in++) {
    if ((idea_v = (*in) - '1') < 9) {
      *eye = idea_v | OPEN | MAY_B[idea_v];
#ifdef LOG
      fprintf(stderr, "LOG sudoku_init: marked_input_idea, cell: %d, value: %d\n", i, idea_v);
#endif
    }
    else
      *eye = 0x7fe7;
  }
  for (; i < 81; i++, eye++)
    *eye = 0x7fe7;
}
void sudoku_to_string (char *buffer, sudoku * puzzle) {
  unsigned short *sun;
  char *eye;
  unsigned char i;
  eye = buffer;
  for (sun = puzzle->i_v, i = 0; i < 81; i++, sun++, eye++) {
    if ((*sun) & OPEN)
      *eye = '?';
    else
      *eye = (unsigned char) ('1' + ((*sun) & data));
  }
  *eye = '\n';
  *(++eye) = '\0';
}
