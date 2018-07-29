#include <node.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

static void *
alloc_node(int tag)
{
   struct ast_node *node;
   size_t size = 0;

   switch (tag) {
      case AST_NODE_:
         size = sizeof(struct ast_node);
         break;
      case AST_DECLARATION:
         size = sizeof(struct ast_declaration);
         break;
      case AST_BINARY_EXPRESSION_:
         size = sizeof(struct ast_binary_expression);
         break;
      case AST_STATEMENT_LIST:
         size = sizeof(struct ast_statement_list);
         break;
      case AST_COMPOUND_STATEMENT:
         size = sizeof(struct ast_compound_statement);
         break;
      case AST_SELECTION_STATEMENT:
         size = sizeof(struct ast_selection_statement);
         break;
      case AST_WHILE_STATEMENT:
         size = sizeof(struct ast_while_statement);
         break;
      case AST_COMPILE_UNIT:
         size = sizeof(struct ast_compile_unit);
         break;
      case AST_COMPILE_UNIT_MEMBER_LIST:
         size = sizeof(struct ast_compile_unit_member_list);
         break;
      case AST_METHOD:
         size = sizeof(struct ast_method);
         break;
      case AST_PRIMITIVE_EXPRESSION:
         size = sizeof(struct ast_primitive_expression);
         break;
      default:
         fprintf(stderr, "Unknown node type: %d\n", tag);
         exit(EXIT_FAILURE);
   }

   node = calloc(1, size);
   if (node == NULL) {
      fprintf(stderr, "Memory allocation request failed.!\n");
      exit(EXIT_FAILURE);
   }

   node->tag = tag;
   return node;
}

void
print_node_list(ast_node_list *nodes){
   int tag = nodes->tag;
   switch (tag) {
      case AST_STATEMENT_LIST:
      fprintf(stdout, "AST_STATEMENT_LIST\n");
      for (int i= 0; i < (nodes)->count; i++)
            print_node((nodes)->nodes[i]);
         break;
      case AST_COMPILE_UNIT_MEMBER_LIST:
      fprintf(stdout, "AST_COMPILE_UNIT_MEMBER_LIST\n");
      for (int i= 0; i < (nodes)->count; i++)
            print_node((nodes)->nodes[i]);
         break;
   } 
}
void
print_node(ast_node *node){
      if (!node)
            return;

   int tag = node->tag;
   switch (tag) {
      case AST_NODE_:
      fprintf(stdout, "AST_NODE\n");
         break;
      case AST_DECLARATION:
      fprintf(stdout, "AST_DECLARATION\n");
         break;
      case AST_BINARY_EXPRESSION_:
      fprintf(stdout, "AST_BINARY_EXPRESSION\n");
      print_node((ast_node*)((ast_binary_expression*)node)->subexpr[0]);
      fprintf(stdout, " + \n");
      print_node((ast_node*)((ast_binary_expression*)node)->subexpr[1]);
         break;
      case AST_COMPOUND_STATEMENT:
      fprintf(stdout, "AST_COMPOUND_STATEMENT\n");
         break;
      case AST_SELECTION_STATEMENT:
      fprintf(stdout, "AST_SELECTION_STATEMENT\n");
         break;
      case AST_WHILE_STATEMENT:
      fprintf(stdout, "AST_WHILE_STATEMENT\n");
         break;
      case AST_COMPILE_UNIT:
      fprintf(stdout, "AST_COMPILE_UNIT\n");
      print_node_list((ast_node_list*)((ast_compile_unit*)node)->compile_unit_member_list);
         break;
      case AST_COMPILE_UNIT_MEMBER_LIST:
      fprintf(stdout, "AST_COMPILE_UNIT_MEMBER_LIST\n");
      for (int i= 0; i < ((ast_node_list*)node)->count; i++)
            print_node(((ast_node_list*)node)->nodes[i]);
         break;
      case AST_METHOD:
         fprintf(stdout, "AST_METHOD:%s\n", ((ast_method*)node)->identifier);
         print_node_list((ast_node_list*)((ast_method*)node)->statement_list);
         break;
      case AST_PRIMITIVE_EXPRESSION:
         fprintf(stdout, "AST_PRIMITIVE_EXPRESSION\n");
         break;
   }
}

ast_binary_expression *
create_binary_expression(const char* _operator, ast_node *lhs,
                                ast_node *rhs)
{
   struct ast_binary_expression *expression;

   expression = alloc_node(AST_BINARY_EXPRESSION_);
   expression->_operator = _operator;
   expression->subexpr[0] = lhs;
   expression->subexpr[1] = rhs;

   return expression;
}

ast_declaration *
create_declaration(int type_specifier, const char *identifier)
{
   struct ast_declaration *declaration;

   declaration = alloc_node(AST_DECLARATION);
   declaration->type_specifier = type_specifier;
   declaration->identifier = identifier;

   return declaration;
}

ast_compound_statement *
create_compound_statement(ast_statement_list *statement_list)
{
   ast_compound_statement *compound_statement;

   compound_statement = alloc_node(AST_COMPOUND_STATEMENT);
   compound_statement->statement_list = statement_list;

   return compound_statement;
}

ast_method *
create_method(const char* identifier, ast_statement_list *statement_list) { 
   ast_method *ret;

   ret = alloc_node(AST_METHOD);
   ret->statement_list = statement_list;
   ret->identifier = identifier;
   return ret;
}

ast_selection_statement *
create_selection_statement(ast_binary_expression *condition,
                           ast_compound_statement *then_body,
                           ast_compound_statement *else_body)
{
   ast_selection_statement *selection_statement;

   selection_statement = alloc_node(AST_SELECTION_STATEMENT);

   selection_statement->condition = condition;
   selection_statement->then_body = then_body;
   selection_statement->else_body = else_body;

   return selection_statement;
}

ast_while_statement *
create_while_statement(ast_binary_expression *condition,
                       ast_compound_statement *body)
{
   ast_while_statement *while_statement;

   while_statement = alloc_node(AST_WHILE_STATEMENT);

   while_statement->condition = condition;
   while_statement->body = body;

   return while_statement;
}

ast_compile_unit *
create_compile_unit(ast_compile_unit_member_list *compile_unit_member_list)
{
   struct ast_compile_unit *compile_unit;

   compile_unit = alloc_node(AST_COMPILE_UNIT);
   compile_unit->compile_unit_member_list = compile_unit_member_list;

   return compile_unit;
}

ast_statement_list *
create_statement_list()
{
   struct ast_statement_list *statement_list;
   statement_list = alloc_node(AST_STATEMENT_LIST);
   return statement_list;
}

ast_compile_unit_member_list *
create_compile_unit_member_list()
{
   ast_compile_unit_member_list *ret;
   ret = alloc_node(AST_COMPILE_UNIT_MEMBER_LIST);
   return ret;
}

ast_node_list * 
node_list_add(ast_node_list *node_list,
              ast_node *node)
{
   int nstmts;
   size_t size;

   nstmts = node_list->count + 1;
   size = nstmts * sizeof(struct ast_node *);

   node_list->nodes = realloc(node_list->nodes, size);
   if (node_list->nodes == NULL) {
      fprintf(stderr, "Memory reallocation request failed.\n");
      exit(EXIT_FAILURE);
   }

   node_list->nodes[nstmts - 1] = node;
   node_list->count++;

   return node_list;
}

ast_primitive_expression *
create_const_int_expression(int value){
   ast_primitive_expression *ret;
   ret = alloc_node(AST_PRIMITIVE_EXPRESSION);
   ret->type = ASTPT_INT_CONSTANT;
   ret->int_constant = value;
   return ret;
}