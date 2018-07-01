#include <snowball.h>
#include <parser.h>
#include <scanner.h>
#include <val.h>
#include <stdio.h>

// Prints a parse tree in pre-order.
void val_print_pre(struct val_s *v) {
  fputs(v->s, stdout);
  if (v->nkid) {
    putchar('(');
    for (int i = 0; i < v->nkid; i++) {
      if (i) printf(", ");
      val_print_pre(v->kid[i]);
    }
    putchar(')');
  }
}

// Prints a parse tree in the style of 'pstree'.
// Uses UTF-8 line-drawing characters.
void val_print_tree(const char *prefix, struct val_s *v) {
  fputs(v->s, stdout);
  if (v->nkid) {
    for (int i = 0; i < v->nkid; i++) {
      char s[strlen(prefix) + 3 + strlen(v->s) + 1];
      strcpy(s, prefix);
      for (int i = strlen(v->s); i; i--) strcat(s, " ");
      if (!i) {
        if (v->nkid == 1) {
          fputs("───", stdout); strcat(s, "   ");
        } else {
          fputs("─┬─", stdout); strcat(s, " │ ");
        }
      } else {
        fputs(s, stdout);
        if (v->nkid == i + 1) {
          fputs(" └─", stdout); strcat(s, "   ");
        } else {
          fputs(" ├─", stdout); strcat(s, " │ ");
        }
      }
      val_print_tree(s, v->kid[i]);
    }
  } else {
    putchar('\n');
  }
}
int f(struct val_s *v) {
      val_print_pre(v);
      putchar('\n');
      val_print_tree("", v);
      // val_free(v);
      return 0;
}

int yyparse_callback(val_ptr val) {
    printf("\n");
    f(val);
    return 0;    
}

int parser_parse(FILE* in, FILE* out) {
	int result = 0;
    yyscan_t scanner;
    if (yylex_init(&scanner))
	    result = 1;
    else
    {

    yyset_in(in, scanner);
    yyset_out(out, scanner);
    
	  result = (yyparse(scanner, yyparse_callback));
    		yylex_destroy(scanner);
    }

    return (result);
}
