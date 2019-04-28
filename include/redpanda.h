#include <stdio.h>

#include <ast_binary_expression.h>
#include <ast_compile_unit.h>
#include <ast_compile_unit_member_list.h>
#include <ast_compound_statement.h>
#include <ast_declaration.h>
#include <ast_method.h>
#include <ast_node.h>
#include <ast_node_list.h>
#include <ast_node_visitor.h>
#include <ast_primitive_expression.h>
#include <ast_return_statement.h>
#include <ast_selection_statement.h>
#include <ast_statement_list.h>
#include <ast_while_statement.h>

#ifndef redpanda_exports_h__
#define redpanda_exports_h__

#ifdef _WIN32
#    ifdef LIBRARY_EXPORTS
#        define LIBRARY_API __declspec(dllexport)
#    else
#        define LIBRARY_API __declspec(dllimport)
#    endif
#else
#    define LIBRARY_API
#endif

#ifdef __cplusplus
extern "C" {  
	// only need to export C interface if
	// used by C++ source code
#endif

	LIBRARY_API int parser_parse(FILE* in, FILE* out);
    LIBRARY_API int compiler__compile(const char* fileName);

#ifdef __cplusplus
}
#endif

#endif