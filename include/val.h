#ifndef snowball_val_h__
#define snowball_val_h__
struct val_s {
  int type;
  struct {
    char *s;
    struct val_s **kid;
    int nkid;
  };
};
typedef struct val_s *val_ptr;
typedef int (*val_callback_t)(val_ptr);

val_ptr val_new_int(char *s);
val_ptr val_new_s(char *s);
val_ptr val_new_ident(char *s);
val_ptr val_new_op(int t, char *s);

val_ptr val_return(val_ptr v);
void val_free(val_ptr v);
val_ptr val_fun(val_ptr fun, val_ptr args);

// Adds a child 'v' to 'op'.
val_ptr val_append(val_ptr op, val_ptr v);

// Adds a NULL-terminated list of children to 'op'.
val_ptr val_append0(val_ptr op, ...);
#endif
