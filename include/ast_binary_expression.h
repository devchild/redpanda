#ifndef redpanda_ast_binary_expression_h__
#define redpanda_ast_binary_expression_h__

#include <glib-object.h>
#include <ast_node.h>

/*
 * Potentially, include other headers on which this header depends.
 */

G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define AST_TYPE_BINARY_EXPRESSION ast_binary_expression_get_type ()
G_DECLARE_FINAL_TYPE (AstBinaryExpression, ast_binary_expression, AST, BINARY_EXPRESSION, AstNode)

/*
 * Method definitions.
 */
AstBinaryExpression *ast_binary_expression_new (void);

G_END_DECLS

#endif