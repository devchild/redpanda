/* A Bison parser, made by GNU Bison 3.0.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_USERS_MARIO_PROJECTS_REDPANDA_BUILD_LIB_REDPANDA_PARSER_H_INCLUDED
# define YY_YY_USERS_MARIO_PROJECTS_REDPANDA_BUILD_LIB_REDPANDA_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 10 "/Users/mario/Projects/redpanda/lib/redpanda/parser.y" /* yacc.c:1916  */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <val.h>

#define YYSTYPE val_ptr

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
  typedef void *yyscan_t;
#endif

#ifdef _WIN32
#   include <io.h>
#   ifdef _MSC_VER
#     define isatty _isatty
#     define fileno _fileno
// '_isatty' : inconsistent dll linkage.  dllexport assumed.
#     pragma warning( disable : 4273 )
#   endif
#endif


#line 70 "/Users/mario/Projects/redpanda/build/lib/redpanda/parser.h" /* yacc.c:1916  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    END = 0,
    EOL = 258,
    BLOCK_END = 259,
    T_DEF = 260,
    T_RETURN = 261,
    ELSE = 262,
    T_IF = 263,
    T_IDENT = 264,
    T_INT = 265,
    T_FLOAT = 266,
    T_STRING = 267,
    T_AND = 268,
    T_XOR = 269,
    T_OR = 270,
    T_PLUS = 271,
    T_MINUS = 272,
    T_MULTIPLY = 273,
    T_DIVIDE = 274,
    T_EQ = 275,
    T_NOT = 276,
    T_COLON = 277,
    T_LEFTP = 278,
    T_RIGHTP = 279,
    T_POW = 280,
    T_SQRT = 281,
    T_LT = 282,
    T_GT = 283,
    OP_LESS_THAN_OR_EQUAL = 284,
    OP_GREATER_THAN_OR_EQUAL = 285,
    T_QM = 286,
    OP_SHIFT_RIGHT = 287,
    OP_SHIFT_LEFT = 288,
    T_NEQ = 289,
    OP_OROR = 290,
    OP_ANDAND = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (yyscan_t scanner, val_callback_t callback);

#endif /* !YY_YY_USERS_MARIO_PROJECTS_REDPANDA_BUILD_LIB_REDPANDA_PARSER_H_INCLUDED  */
