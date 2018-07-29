#ifndef redpanda_ast_node_h__
#define redpanda_ast_node_h__

#include <glib-object.h>

/*
 * Potentially, include other headers on which this header depends.
 */

G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define AST_TYPE_NODE ast_node_get_type ()
G_DECLARE_DERIVABLE_TYPE (AstNode, ast_node, AST, NODE, GObject)

struct _AstNodeClass
{
  GObjectClass parent_class;

  /* Class virtual function fields. */
  void (* open) (AstNode  *node,
                 GError     **error);

  /* Padding to allow adding up to 12 new virtual functions without
   * breaking ABI. */
  gpointer padding[12];
};

/*
 * Method definitions.
 */
AstNode *ast_node_new (void);

G_END_DECLS

#endif