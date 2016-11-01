typedef struct {
  sudoku *s;
  int p;
  int v;
} sudoku_state;
typedef struct {
  char *buffer;
  int position;

  sudoku_state *stack;
  int top;
} dump_struct;
dump_struct dump_data;
void dump_request (int sig) {
  fputs ("\ndump requested\n", stderr);
  if (!(dump_data.buffer = malloc (81 * 414)))
    die ("RAM denied");
  memset (dump_data.buffer, 0, 81 * 414);
}
int sudoku_dump (sudoku * s, int p, int v, char *buffer) {
  char *eye;
  unsigned short *sun;
  int l;

  for (l = 0, eye = buffer, sun = s->i_v; l < 405; sun++, eye += 5)
    l += sprintf (eye, "%04x ", (int) *sun);

  l += sprintf (eye, "%02x ", (int) s->left);
  eye += 3;
  l += sprintf (eye, "%02x ", p);
  eye += 3;
  l += sprintf (eye, "%02x\n", v);

  return l;                     /* the characters written dump_data.position
                                   to be incremented outside */
}
int dump_struct_free (dump_struct * dump_structure) {
  sudoku_state *n;
  for (; n >= dump_structure->stack + dump_structure->top; n--)
    free (n->s);
  free (dump_structure->stack);
  dump_structure->stack = 0;
  free (dump_structure->buffer);
  dump_structure->buffer = 0;
  return 1;
}
int dumpfile_try_read (dump_struct * dump_structure) {
  FILE *dumpfile;
  int depth, i;
  char *line, *this, *nxt;
  unsigned short *eye;
  sudoku_state *now;

  if (!(dumpfile = fopen ("dump", "rb")))
    return 2;
  if (!(dump_structure->buffer = (char *) malloc (81 * 414)))
    die ("RAM denied\n");
  memset (dump_structure->buffer, 0, 81 * 414);
  depth = fread (dump_structure->buffer, 414, 81, dumpfile);    /* if CRLF &
                                                                   fread
                                                                   doesnt
                                                                   copy the
                                                                   last
                                                                   incomplete
                                                                   line */
  fclose (dumpfile);
  if (!depth)
    return 1;

  if (!
      (dump_structure->stack =
       (sudoku_state *) malloc (sizeof (sudoku_state) * depth)))
    die ("RAM denied\n");
  memset (dump_structure->stack, 0, sizeof (sudoku_state) * depth);

  line = strtok (dump_structure->buffer, "\r\n");
  dump_structure->top = 0;
  while (line && depth) {
    now = dump_structure->stack + dump_structure->top;
    if (!(now->s = (sudoku *) malloc (sizeof (sudoku))))
      die ("RAM denied\n");
    for (i = 0, this = line, eye = now->s->i_v; i < 81; i++, eye++) {
      *eye = (unsigned short) strtoul (this, &nxt, 16);
      if ((this + 5 != nxt) && (i != 0 || (this + 4 != nxt)))
        return dump_struct_free (dump_structure);
      this = nxt;
    }
    now->s->left = (unsigned char) strtoul (this, &nxt, 16);
    if (this + 3 != nxt)
      return dump_struct_free (dump_structure);
    this = nxt;
    now->p = (unsigned char) strtoul (this, &nxt, 16);
    if (this + 3 != nxt)
      return dump_struct_free (dump_structure);
    this = nxt;
    now->v = (unsigned char) strtoul (this, &nxt, 16);
    if (this + 3 != nxt)
      return dump_struct_free (dump_structure);
    line = strtok (0, "\r\n");
    dump_structure->top++;
    depth--;
  }
  free (dump_structure->buffer);
  dump_structure->buffer = 0;
  return 0;
}
