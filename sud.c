#include "sud_squash.c"
#include <signal.h>
char def[10] = "123456789";
int main (int argc, char **argv) {
  sudoku *master;
  char *in;
  FILE *dumpfile;

  dump_data.buffer = 0;
  dump_data.stack = 0;
  dump_data.position = dump_data.top = -1;

  scope_gen (scope);

  in = argc > 1 ? argv[1] : def;

  if (argc > 1 || dumpfile_try_read (&dump_data)) {
    /* we have not read a dumpfile */
    if (!(master = (sudoku *) malloc (sizeof (sudoku))))
      die ("RAM denied\n");
    sudoku_init (in, master);
  }
  else {
    /* we have read dumpfile */
    dump_data.top--;
    master = (dump_data.stack + dump_data.top)->s;
    /* pop a sudoku_state */
  }

  if (signal (SIGINT, dump_request) == SIG_ERR)
    fputs ("could not enable dump feature for SIGINT\n", stderr);
#ifdef DEBUG
  else
    fputs ("DEBUG: dump feature enabled for SIGINT\n", stderr);
#endif

  if (signal (SIGPIPE, dump_request) == SIG_ERR)
    fputs ("could not enable dump feature for SIGPIPE\n", stderr);
#ifdef DEBUG
  else
    fputs ("DEBUG: dump feature enabled for SIGPIPE\n", stderr);
#endif

  count = iint_new (10);

  switch (squash (master, &dump_data)) {
  case -1:
#ifdef LOG
    fprintf(stderr, "LOG main: input_idea_wrong, cell: last_checked, value: last_checked\n");
#endif
    fputs ("no solution\n", stderr);
    break;
  case 2:
    sudoku_dump (master, 10, 10, dump_data.buffer + dump_data.position);
    if (!(dumpfile = fopen ("dump", "wb"))) {
      fputs ("couldn't create dumpfile\n", stderr);
      fputs (dump_data.buffer, stderr);
    }
    else {
      fputs (dump_data.buffer, dumpfile);
      fclose (dumpfile);
    }
    free (dump_data.buffer);
    break;
  default:
#ifdef LOG
    fprintf(stderr, "LOG main: pop_main\n");
#endif
    break;
  }
  free (master);

  *out = '#';
  iint_to_string (out + 1, count);      /* haha! passing a global :D */
  fputs (out, stderr);

  return 0;
}
