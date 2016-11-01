#include "die.c"
#include "sud_ds.c"
#include "sud_dmp.c"
#include "iint.c"
#include "sud_core.c"
#include "sud_txt.c"

char out[83] = "";
iint *count;
int hook (sudoku * puzzle, dump_struct * dump_structure) {
  unsigned char x;
  unsigned char *eye;
  unsigned char pos, val;
  if (dump_structure->stack) {
    if (dump_structure->top)
      return 0;
    free (dump_structure->stack);
    dump_structure->stack = 0;
    dump_structure->top = -1;
    return 1;
  }
  while (sudoku_cell_to_fill (puzzle, &pos, &val)) {
#ifdef LOG
    fprintf(stderr, "LOG hook: set_current_idea, cell: %d, value: %d\n", pos, val);
#endif
    for (x = 0, eye = &scope[pos * 20]; x < 20; x++, eye++) {
#ifdef LOG
      fprintf(stderr, "LOG hook: set_current_probable, cell: %d, value: %d\n", *eye, val);
#endif
      if (remove_probable (&(puzzle->i_v[*eye]), val))
        return -1;
    }
    puzzle->i_v[pos] &= (~open);
#ifdef LOG
    fprintf(stderr, "LOG hook: lock_current_idea\n");
#endif
    if (!(--(puzzle->left))) {
#ifdef LOG
      fprintf(stderr, "LOG hook: a_solution_reached\n");
#endif
      sudoku_to_string (out, puzzle);
      fputs (out, stdout);
      iint_add (count, 1L);     /* cant possibly overflow, should i check? */
      if (dump_structure->buffer) {
        dump_structure->position = 0;
        return 2;
      }
      else
        return 1;
    }
  }
  return 0;
}
int squash (sudoku * puzzle, dump_struct * dump_structure);
int crook (sudoku * master, dump_struct * dump_structure) {
  sudoku *copy;
  unsigned short *mc, *cc;
  unsigned char pos, val = 0, dummy;
  if (dump_structure->stack) {
    if (!dump_structure->top--)
      die ("stack underflow");
    copy = (dump_structure->stack + dump_structure->top)->s;
    pos = (unsigned char) (dump_structure->stack + dump_structure->top)->p;
    val = (unsigned char) (dump_structure->stack + dump_structure->top)->v;
    mc = &master->i_v[pos];
    cc = &copy->i_v[pos];
  }
  else {
    if (!(copy = (sudoku *) malloc (sizeof (sudoku))))
      die ("RAM denied\n");
    if (sudoku_first_waiting_cell (master, &pos)) {
      mc = &master->i_v[pos];
      cc = &copy->i_v[pos];
    }
    else
      return 1;
  }
  while (dump_structure->stack || cell_value_to_try (mc, &val)) {
    if (!dump_structure->stack) {
      *copy = *master;
      *cc = (((unsigned short) val) | open | may_b[val]);
#ifdef LOG
      fprintf(stderr, "LOG crook: push_guess, cell: %d, value: %d\n", pos, val);
#endif
    }
    switch (squash (copy, dump_structure)) {
    case 1:
#ifdef LOG
      fprintf(stderr, "LOG crook: pop_guess\n");
#endif
      val++;
      break;
    case 2:
      dump_structure->position +=
        sudoku_dump (copy, (int) pos, (int) val,
                     dump_structure->buffer + dump_structure->position);
      return 2;
    case -1:
#ifdef LOG
      fprintf(stderr, "LOG crook: pop_wrong_guess_and_remove_probable, cell: %d, value: %d\n", pos, val);
#endif
      remove_probable (mc, val);        /* should i check? */
      if (sudoku_cell_to_fill (master, &pos, &dummy) && (dummy > val)) {
        free (copy);
        return 0;
      }
    }
  }
  free (copy);
  return 1;
}
int squash (sudoku * puzzle, dump_struct * dump_structure) {
  /* TODO the log_struct * log_structure then probably env_struct *
     environment which encapsulates log, dump, count and more */
  int ret;
  do
    if (ret = hook (puzzle, dump_structure))
      return ret;
  while (!(ret = crook (puzzle, dump_structure)));
  return ret;
}
