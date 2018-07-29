#ifndef redpanda_node_h__
#define redpanda_node_h__

struct ast_node;
struct ast_declaration;
struct ast_binary_expression;
struct ast_statement_list;
struct ast_compound_statement;
struct ast_selection_statement;
struct ast_while_statement;
struct ast_compile_unit;

#define AST_NODE_                        1
#define AST_DECLARATION                 2
#define AST_BINARY_EXPRESSION_           3
#define AST_STATEMENT_LIST              4
#define AST_COMPOUND_STATEMENT          5
#define AST_SELECTION_STATEMENT         6
#define AST_WHILE_STATEMENT             7
#define AST_COMPILE_UNIT                8
#define AST_COMPILE_UNIT_MEMBER_LIST    9
#define AST_METHOD                      10
#define AST_PRIMITIVE_EXPRESSION        11

#define ASTPT_INT_CONSTANT                101
#define ASTPT_FLOAT_CONSTANT              102
#define ASTPT_IDENTIFIER                  103

typedef struct ast_node {
   int tag;
} ast_node;

typedef struct ast_node_list {
   int tag;
   int count;
   ast_node **nodes;
} ast_node_list;

typedef int (*node_callback_t)(struct ast_compile_unit *);

typedef struct ast_declaration {
   ast_node base;

   int type_specifier;
   const char *identifier;
} ast_declaration;

typedef struct ast_method {
   ast_node base;

   const char *identifier;
   struct ast_statement_list *statement_list;
} ast_method;

typedef struct ast_binary_expression {
   ast_node base;

   const char* _operator;
   struct ast_node *subexpr[2];
} ast_binary_expression;

typedef struct ast_primitive_expression {
   ast_node base;
   int type;

   int int_constant;
   float float_constant;
   const char *identifier;
} ast_primitive_expression;

typedef struct ast_statement_list {
    ast_node_list base;
} ast_statement_list;

typedef struct ast_compile_unit_member_list {
    ast_node_list base;
} ast_compile_unit_member_list;

typedef struct ast_compound_statement {
   ast_node base;

   ast_statement_list *statement_list;
} ast_compound_statement;

typedef struct ast_selection_statement {
   ast_node base;

   /* if (condition) { then_body } else { else_body } */
   ast_binary_expression *condition;
   ast_compound_statement *then_body;
   ast_compound_statement *else_body;
} ast_selection_statement;

typedef struct ast_while_statement {
   ast_node base;

   /* while (condition) { body } */
   ast_binary_expression *condition;
   ast_compound_statement *body;
} ast_while_statement;

typedef struct ast_compile_unit {
   ast_node base;

   ast_compile_unit_member_list *compile_unit_member_list;
} ast_compile_unit;

ast_declaration *
create_declaration(int type_specifier, const char *identifier);

ast_binary_expression *
create_binary_expression(const char* _operator, ast_node *lhs,
                                 ast_node *rhs);

ast_statement_list *
create_statement_list();

ast_compound_statement *
create_compound_statement(ast_statement_list *statement_list);

ast_method *
create_method(const char* identifier, ast_statement_list *statement_list);

ast_selection_statement *
create_selection_statement(ast_binary_expression *condition,
                           ast_compound_statement *then_body,
                           ast_compound_statement *else_body);

ast_while_statement *
create_while_statement(ast_binary_expression *condition,
                       ast_compound_statement *body);

ast_compile_unit *
create_compile_unit(ast_compile_unit_member_list *compile_unit_member_list);

ast_compile_unit_member_list *
create_compile_unit_member_list();

ast_node_list *
node_list_add(ast_node_list *node_list,
                             ast_node *node);

ast_primitive_expression *
create_const_int_expression(int value);

void
print_node(ast_node *node);

void
print_node_list(ast_node_list *nodes);


#endif