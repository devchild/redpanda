#ifndef snowball_ast_h__
#define snowball_ast_h__

enum relational_operator
{
    LESS,
    LESS_OR_EQUAL,
    GREATER,
    GREATER_OR_EQUAL
};

enum equality_operator
{
    EQUAL,
    NOT_EQUAL
};

struct ast_node // for binary/unary operators and expression lists
{
	int node_type;

	struct ast_node * left;

	struct ast_node * right;
};

struct ast_relational_node // for relational operators
{
	int node_type;

	enum relational_operator operator;

	struct ast_node * left;

	struct ast_node * right;
};

struct ast_equality_node // for equality operators
{
	int node_type;

	enum equality_operator operator;

	struct ast_node * left;

	struct ast_node * right;
};

struct ast_function_node // for function calls
{
	int node_type;

	struct ast_node * arguments;

	struct symbol_node * symbol;
};

struct ast_symbol_reference_node // for symbol references
{
	int node_type;

	struct symbol_node * symbol;
};

struct ast_if_node // for "if/else" statements
{
	int node_type;

	struct ast_node * condition;

	struct ast_node * if_branch;

	struct ast_node * else_branch;
};

struct ast_while_node // for "while" statements
{
	int node_type;

	struct ast_node * condition;

	struct ast_node * while_branch;
};

struct ast_assignment_node // for assignment expressions
{
	int node_type;

	struct symbol_node * symbol;

	struct ast_node * value;
};

struct ast_number_node // for constant floating-point numbers
{
	int node_type;

	double value;
};

void free_ast_tree(struct ast_node * ast_tree);

#endif
