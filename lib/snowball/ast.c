#include <ast.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void * err_malloc(size_t size);
void err_printf(char * format, ...);

struct ast_node * 
	new_ast_node(int node_type, struct ast_node * left, struct ast_node * right)
{
	struct ast_node * ast_node =
		err_malloc(sizeof(struct ast_node));

	ast_node->node_type = node_type;

	ast_node->left = left;
	ast_node->right = right;

	return ast_node;
}

struct ast_node *
	new_ast_relational_node(enum relational_operator operator, struct ast_node * left, struct ast_node * right)
{
	struct ast_relational_node * ast_node =
		err_malloc(sizeof(struct ast_relational_node));

	ast_node->node_type = 'R';

	ast_node->operator = operator;
	ast_node->left = left;
	ast_node->right = right;

	return (struct ast_node *) ast_node;
}

struct ast_node *
	new_ast_equality_node(enum equality_operator operator, struct ast_node * left, struct ast_node * right)
{
	struct ast_equality_node * ast_node =
		err_malloc(sizeof(struct ast_equality_node));

	ast_node->node_type = 'E';

	ast_node->operator = operator;
	ast_node->left = left;
	ast_node->right = right;

	return (struct ast_node *) ast_node;
}

struct ast_node *
	new_ast_function_node(struct symbol_node * symbol, struct ast_node * arguments)
{
	struct ast_function_node * ast_node =
		err_malloc(sizeof(struct ast_function_node));

	ast_node->node_type = 'F';

	ast_node->arguments = arguments;
	ast_node->symbol = symbol;

	return (struct ast_node *) ast_node;
}

struct ast_node *
	new_ast_symbol_reference_node(struct symbol_node * symbol)
{
	struct ast_symbol_reference_node * ast_node =
		err_malloc(sizeof(struct ast_symbol_reference_node));

	ast_node->node_type = 'S';

	ast_node->symbol = symbol;

	return (struct ast_node *) ast_node;
}

struct ast_node *
	new_ast_if_node(struct ast_node * condition, struct ast_node * if_branch, struct ast_node * else_branch)
{
	struct ast_if_node * ast_node =
		err_malloc(sizeof(struct ast_if_node));

	ast_node->node_type = 'I';

	ast_node->condition = condition;
	ast_node->if_branch = if_branch;
	ast_node->else_branch = else_branch;

	return (struct ast_node *) ast_node;
}

struct ast_node *
	new_ast_while_node(struct ast_node * condition, struct ast_node * while_branch)
{
	struct ast_while_node * ast_node =
		err_malloc(sizeof(struct ast_while_node));

	ast_node->node_type = 'W';

	ast_node->condition = condition;
	ast_node->while_branch = while_branch;

	return (struct ast_node *) ast_node;
}

struct ast_node *
	new_ast_assignment_node(struct symbol_node * symbol, struct ast_node * value)
{
	struct ast_assignment_node * ast_node =
		err_malloc(sizeof(struct ast_assignment_node));

	ast_node->node_type = 'A';

	ast_node->symbol = symbol;
	ast_node->value = value;

	return (struct ast_node *) ast_node;
}

struct ast_node *
	new_ast_number_node(double value)
{
	struct ast_number_node * ast_node =
		err_malloc(sizeof(struct ast_number_node));

	ast_node->node_type = 'N';

	ast_node->value = value;

	return (struct ast_node *) ast_node;
}

void
	err_printf(char * format, ...)
{
	va_list args;

	va_start(args, format);

	vfprintf(stderr, format, args);

	va_end(args);

	exit(EXIT_FAILURE);
}

void *
	err_malloc(size_t size)
{
	void * pointer = malloc(size);

	if (!pointer)
		err_printf("Error: malloc(%u) failed!\n", size);

	return pointer;
}

void
	free_ast_tree(struct ast_node * ast_tree)
{
	if (!ast_tree) return;

	switch (ast_tree->node_type)
	{
		/* two sub trees */
	case '+':
	case '-':
	case '*':
	case '/':
	case 'L':
		free_ast_tree(ast_tree->right);

		/* one sub tree */
	case 'M':
		free_ast_tree(ast_tree->left);

		/* no sub trees */
	case 'S':
	case 'N':
		break;

	case 'R':
	{
		struct ast_relational_node * node =
			(struct ast_relational_node *) ast_tree;

		free_ast_tree(node->left);

		free_ast_tree(node->right);
	}
	break;

	case 'E':
	{
		struct ast_equality_node * node =
			(struct ast_equality_node *) ast_tree;

		free_ast_tree(node->left);

		free_ast_tree(node->right);
	}
	break;

	case 'A':
	{
		struct ast_assignment_node * node =
			(struct ast_assignment_node *) ast_tree;

		free_ast_tree(node->value);
	}
	break;

	case 'I':
	{
		struct ast_if_node * node =
			(struct ast_if_node *) ast_tree;

		free_ast_tree(node->condition);

		if (node->if_branch)
		{
			free_ast_tree(node->if_branch);
		}

		if (node->else_branch)
		{
			free_ast_tree(node->else_branch);
		}
	}
	break;

	case 'W':
	{
		struct ast_while_node * node =
			(struct ast_while_node *) ast_tree;

		free_ast_tree(node->condition);

		if (node->while_branch)
		{
			free_ast_tree(node->while_branch);
		}
	}
	break;

	case 'F':
	{
		struct ast_function_node * node =
			(struct ast_function_node *) ast_tree;

		if (node->arguments)
		{
			free_ast_tree(node->arguments);
		}
	}
	break;

	default:
		err_printf("Error: Bad node type '%c' to free!\n", ast_tree->node_type);
	}

	free(ast_tree);
}