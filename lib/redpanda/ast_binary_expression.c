#include <ast_binary_expression.h>

struct _AstBinaryExpression
{
  AstNodeClass parent_instance;

  /* instance members */
};

G_DEFINE_TYPE (AstBinaryExpression, ast_binary_expression, AST_TYPE_NODE)

static void
ast_binary_expression_class_init (AstBinaryExpressionClass *klass)
{
}

static void
ast_binary_expression_init (AstBinaryExpression *self)
{
    AstBinaryExpression *priv = ast_binary_expression_get_instance_private (self);

    /* initialize all public and private members to reasonable default values.
    * They are all automatically initialized to 0 to begin with. */
}