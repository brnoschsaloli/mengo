/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "parserLLVM.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include <llvm-c/Core.h>
#include <llvm-c/Support.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include "parserLLVM.tab.h"

/* yylineno is updated by Flex */
extern int yylineno;

/* LLVM globals */
LLVMContextRef context;
LLVMModuleRef module;
LLVMBuilderRef builder;
LLVMValueRef main_func; /* Main function for code generation */

/* Simple symbol table to store variable mappings */
struct Symbol {
    char *name;
    LLVMValueRef value;
};
struct Symbol symbol_table[100]; /* Adjust size as needed */
int symbol_count = 0;

/* Find or create a variable in the symbol table */
LLVMValueRef find_or_create_variable(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return symbol_table[i].value;
        }
    }
    /* Create new global variable */
    LLVMValueRef var = LLVMAddGlobal(module, LLVMDoubleTypeInContext(context), name);
    LLVMSetInitializer(var, LLVMConstReal(LLVMDoubleTypeInContext(context), 0.0));
    symbol_table[symbol_count].name = strdup(name);
    symbol_table[symbol_count].value = var;
    symbol_count++;
    return var;
}

#define MAX_LABELS 100
#define MAX_IF_DEPTH 100
static LLVMBasicBlockRef if_then_stack[MAX_IF_DEPTH];
static LLVMBasicBlockRef if_merge_stack[MAX_IF_DEPTH];
static bool then_terminated[MAX_IF_DEPTH];
static int if_depth = 0;
static int exit_cont = 0;
static int cont_count = 0;
static char*   label_names[MAX_LABELS];
static LLVMBasicBlockRef label_blocks[MAX_LABELS];
static int     label_count = 0;

/* parserLLVM.y, no prólogo */
extern void delete_list(double elem, double *data, long *len);
extern double in_list(double elem, double *data, long len);


/* retorna NULL se a variável não existe */
LLVMValueRef find_variable(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0)
            return symbol_table[i].value;
    }
    return NULL;
}

void registerLabel(const char *name, LLVMBasicBlockRef bb) {
    label_names[label_count] = strdup(name);
    label_blocks[label_count] = bb;
    label_count++;
}

LLVMBasicBlockRef findLabel(const char *name) {
    for (int i = 0; i < label_count; i++)
        if (strcmp(label_names[i], name) == 0)
            return label_blocks[i];
    return NULL;
}

/* Error handling */
void yyerror(const char *s) {
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

/* String duplication for portability */
static char *copyString(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}

extern int yylex();
extern FILE *yyin;

#line 172 "parserLLVM.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parserLLVM.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SET = 3,                        /* SET  */
  YYSYMBOL_ADD = 4,                        /* ADD  */
  YYSYMBOL_SUB = 5,                        /* SUB  */
  YYSYMBOL_MUL = 6,                        /* MUL  */
  YYSYMBOL_DIV = 7,                        /* DIV  */
  YYSYMBOL_POW = 8,                        /* POW  */
  YYSYMBOL_MOD = 9,                        /* MOD  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_OR = 11,                        /* OR  */
  YYSYMBOL_NOT = 12,                       /* NOT  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_EQUAL = 14,                     /* EQUAL  */
  YYSYMBOL_NOTEQUAL = 15,                  /* NOTEQUAL  */
  YYSYMBOL_LESS = 16,                      /* LESS  */
  YYSYMBOL_GREATER = 17,                   /* GREATER  */
  YYSYMBOL_LESSEQUAL = 18,                 /* LESSEQUAL  */
  YYSYMBOL_GREATEREQUAL = 19,              /* GREATEREQUAL  */
  YYSYMBOL_LABEL = 20,                     /* LABEL  */
  YYSYMBOL_GOTO = 21,                      /* GOTO  */
  YYSYMBOL_EXIT = 22,                      /* EXIT  */
  YYSYMBOL_INPUT = 23,                     /* INPUT  */
  YYSYMBOL_PRINT = 24,                     /* PRINT  */
  YYSYMBOL_BIN = 25,                       /* BIN  */
  YYSYMBOL_LIST = 26,                      /* LIST  */
  YYSYMBOL_INSERT = 27,                    /* INSERT  */
  YYSYMBOL_DELETE = 28,                    /* DELETE  */
  YYSYMBOL_IN = 29,                        /* IN  */
  YYSYMBOL_IDENTIFIER = 30,                /* IDENTIFIER  */
  YYSYMBOL_STRING = 31,                    /* STRING  */
  YYSYMBOL_COMMENT = 32,                   /* COMMENT  */
  YYSYMBOL_INDENT = 33,                    /* INDENT  */
  YYSYMBOL_NEWLINE = 34,                   /* NEWLINE  */
  YYSYMBOL_TRUE = 35,                      /* TRUE  */
  YYSYMBOL_FALSE = 36,                     /* FALSE  */
  YYSYMBOL_GET = 37,                       /* GET  */
  YYSYMBOL_NUMBER = 38,                    /* NUMBER  */
  YYSYMBOL_YYACCEPT = 39,                  /* $accept  */
  YYSYMBOL_program = 40,                   /* program  */
  YYSYMBOL_line = 41,                      /* line  */
  YYSYMBOL_indent_list = 42,               /* indent_list  */
  YYSYMBOL_simple_stmt = 43,               /* simple_stmt  */
  YYSYMBOL_assignment = 44,                /* assignment  */
  YYSYMBOL_math_operation = 45,            /* math_operation  */
  YYSYMBOL_logical_operation = 46,         /* logical_operation  */
  YYSYMBOL_if_stmt = 47,                   /* if_stmt  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_then_block = 49,                /* then_block  */
  YYSYMBOL_comparator = 50,                /* comparator  */
  YYSYMBOL_label_def = 51,                 /* label_def  */
  YYSYMBOL_goto_command = 52,              /* goto_command  */
  YYSYMBOL_exit_command = 53,              /* exit_command  */
  YYSYMBOL_input_command = 54,             /* input_command  */
  YYSYMBOL_print_command = 55,             /* print_command  */
  YYSYMBOL_bin_command = 56,               /* bin_command  */
  YYSYMBOL_list_command = 57,              /* list_command  */
  YYSYMBOL_list_insert = 58,               /* list_insert  */
  YYSYMBOL_list_delete = 59,               /* list_delete  */
  YYSYMBOL_list_in_check = 60,             /* list_in_check  */
  YYSYMBOL_get_command = 61,               /* get_command  */
  YYSYMBOL_value = 62                      /* value  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   131

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   134,   134,   136,   140,   141,   145,   147,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   170,   177,   182,   187,   192,   197,   201,
     205,   213,   217,   221,   229,   228,   279,   280,   281,   285,
     286,   287,   288,   289,   290,   294,   313,   332,   353,   407,
     444,   480,   488,   518,   578,   656,   723,   764,   767,   771,
     772,   773
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SET", "ADD", "SUB",
  "MUL", "DIV", "POW", "MOD", "AND", "OR", "NOT", "IF", "EQUAL",
  "NOTEQUAL", "LESS", "GREATER", "LESSEQUAL", "GREATEREQUAL", "LABEL",
  "GOTO", "EXIT", "INPUT", "PRINT", "BIN", "LIST", "INSERT", "DELETE",
  "IN", "IDENTIFIER", "STRING", "COMMENT", "INDENT", "NEWLINE", "TRUE",
  "FALSE", "GET", "NUMBER", "$accept", "program", "line", "indent_list",
  "simple_stmt", "assignment", "math_operation", "logical_operation",
  "if_stmt", "$@1", "then_block", "comparator", "label_def",
  "goto_command", "exit_command", "input_command", "print_command",
  "bin_command", "list_command", "list_insert", "list_delete",
  "list_in_check", "get_command", "value", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-109)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
    -109,     5,  -109,  -109,    59,   -22,   -14,    -3,    -2,     1,
       3,     4,     6,     7,     8,     9,    10,    11,  -109,    12,
     -29,    13,    14,    15,    22,    23,  -109,  -109,    -6,    -8,
    -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,    -6,    -6,    -6,    -6,    -6,
      -6,    -6,    24,    25,    26,    -4,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,  -109,    27,  -109,    28,    29,    30,
    -109,    43,  -109,  -109,    -6,    -6,    -6,    -6,    -6,    -6,
      44,    45,  -109,  -109,  -109,  -109,  -109,  -109,  -109,    -6,
    -109,  -109,  -109,    46,    47,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,    55,  -109,  -109,  -109,     2,    94,  -109,
      56,     2,     2,  -109,  -109
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     6,     1,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,     0,
       0,     0,     0,     0,     0,     0,    22,     7,     0,     0,
       8,     9,    10,     4,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,    46,    48,    61,
      49,    59,    60,    57,    50,     0,    52,     0,     0,     0,
      58,     0,     5,    23,     0,     0,     0,     0,     0,    29,
       0,     0,    33,    39,    40,    41,    42,    43,    44,     0,
      51,    53,    54,     0,     0,    24,    25,    26,    27,    28,
      30,    31,    32,     0,    55,    56,    34,    36,     0,    35,
       0,    36,    36,    38,    37
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -109,  -109,  -109,  -109,   -30,  -109,  -109,  -109,   -15,  -109,
    -108,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,   -28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     3,     4,    29,    30,    31,    32,    33,   107,
     109,    89,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    64
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      71,    59,    60,   113,   114,     2,    61,    62,    45,    63,
      83,    84,    85,    86,    87,    88,    46,    73,    74,    75,
      76,    77,    78,    79,    59,    70,    72,    47,    48,    61,
      62,    49,    63,    50,    51,   108,    52,    53,    54,    55,
      56,    57,    58,    65,    66,    67,    95,    96,    97,    98,
      99,   100,    68,    69,    80,    81,    82,    90,    91,    92,
      93,   103,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    94,   101,   102,   104,   105,   110,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,   106,
     112,    26,    27,   111,     0,     0,    28,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     0,     0,
       0,     0,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,    26,     0,     0,     0,
       0,    28
};

static const yytype_int8 yycheck[] =
{
      28,    30,    31,   111,   112,     0,    35,    36,    30,    38,
      14,    15,    16,    17,    18,    19,    30,    45,    46,    47,
      48,    49,    50,    51,    30,    31,    34,    30,    30,    35,
      36,    30,    38,    30,    30,    33,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    74,    75,    76,    77,
      78,    79,    30,    30,    30,    30,    30,    30,    30,    30,
      30,    89,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    30,    30,    30,    30,    30,   108,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    34,
      34,    32,    33,   108,    -1,    -1,    37,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    37
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    40,     0,    41,    42,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    32,    33,    37,    43,
      44,    45,    46,    47,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    30,    30,
      31,    35,    36,    38,    62,    30,    30,    30,    30,    30,
      31,    62,    34,    62,    62,    62,    62,    62,    62,    62,
      30,    30,    30,    14,    15,    16,    17,    18,    19,    50,
      30,    30,    30,    30,    30,    62,    62,    62,    62,    62,
      62,    30,    30,    62,    30,    30,    34,    48,    33,    49,
      43,    47,    34,    49,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    39,    40,    40,    41,    41,    42,    42,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    44,    45,    45,    45,    45,    45,    45,
      45,    46,    46,    46,    48,    47,    49,    49,    49,    50,
      50,    50,    50,    50,    50,    51,    52,    53,    54,    55,
      55,    56,    57,    58,    59,    60,    61,    62,    62,    62,
      62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     3,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     4,     4,     4,     4,     4,     3,
       4,     4,     4,     3,     0,     7,     0,     4,     3,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     2,     2,
       2,     3,     2,     3,     3,     4,     4,     1,     1,     1,
       1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 23: /* assignment: SET IDENTIFIER value  */
#line 170 "parserLLVM.y"
                         {
        LLVMBuildStore(builder, (yyvsp[0].lval), find_or_create_variable((yyvsp[-1].sval)));
        free((yyvsp[-1].sval));
    }
#line 1304 "parserLLVM.tab.c"
    break;

  case 24: /* math_operation: ADD IDENTIFIER value value  */
#line 177 "parserLLVM.y"
                               {
        LLVMValueRef result = LLVMBuildFAdd(builder, (yyvsp[-1].lval), (yyvsp[0].lval), "addtmp");
        LLVMBuildStore(builder, result, find_or_create_variable((yyvsp[-2].sval)));
        free((yyvsp[-2].sval));
    }
#line 1314 "parserLLVM.tab.c"
    break;

  case 25: /* math_operation: SUB IDENTIFIER value value  */
#line 182 "parserLLVM.y"
                               {
        LLVMValueRef result = LLVMBuildFSub(builder, (yyvsp[-1].lval), (yyvsp[0].lval), "subtmp");
        LLVMBuildStore(builder, result, find_or_create_variable((yyvsp[-2].sval)));
        free((yyvsp[-2].sval));
    }
#line 1324 "parserLLVM.tab.c"
    break;

  case 26: /* math_operation: MUL IDENTIFIER value value  */
#line 187 "parserLLVM.y"
                               {
        LLVMValueRef result = LLVMBuildFMul(builder, (yyvsp[-1].lval), (yyvsp[0].lval), "multmp");
        LLVMBuildStore(builder, result, find_or_create_variable((yyvsp[-2].sval)));
        free((yyvsp[-2].sval));
    }
#line 1334 "parserLLVM.tab.c"
    break;

  case 27: /* math_operation: DIV IDENTIFIER value value  */
#line 192 "parserLLVM.y"
                               {
        LLVMValueRef result = LLVMBuildFDiv(builder, (yyvsp[-1].lval), (yyvsp[0].lval), "divtmp");
        LLVMBuildStore(builder, result, find_or_create_variable((yyvsp[-2].sval)));
        free((yyvsp[-2].sval));
    }
#line 1344 "parserLLVM.tab.c"
    break;

  case 28: /* math_operation: POW IDENTIFIER value value  */
#line 197 "parserLLVM.y"
                               {
        printf("Math op pow: %s (not implemented)\n", (yyvsp[-2].sval));
        free((yyvsp[-2].sval));
    }
#line 1353 "parserLLVM.tab.c"
    break;

  case 29: /* math_operation: MOD IDENTIFIER value  */
#line 201 "parserLLVM.y"
                         {
        printf("Math op mod: %s (not implemented)\n", (yyvsp[-1].sval));
        free((yyvsp[-1].sval));
    }
#line 1362 "parserLLVM.tab.c"
    break;

  case 30: /* math_operation: MOD IDENTIFIER value value  */
#line 205 "parserLLVM.y"
                               {
        LLVMValueRef result = LLVMBuildFRem(builder, (yyvsp[-1].lval), (yyvsp[0].lval), "modtmp");
        LLVMBuildStore(builder, result, find_or_create_variable((yyvsp[-2].sval)));
        free((yyvsp[-2].sval));
    }
#line 1372 "parserLLVM.tab.c"
    break;

  case 31: /* logical_operation: AND IDENTIFIER IDENTIFIER IDENTIFIER  */
#line 213 "parserLLVM.y"
                                         {
        printf("Logical and: %s %s %s (not implemented)\n", (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sval));
        free((yyvsp[-2].sval)); free((yyvsp[-1].sval)); free((yyvsp[0].sval));
    }
#line 1381 "parserLLVM.tab.c"
    break;

  case 32: /* logical_operation: OR IDENTIFIER IDENTIFIER IDENTIFIER  */
#line 217 "parserLLVM.y"
                                        {
        printf("Logical or: %s %s %s (not implemented)\n", (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sval));
        free((yyvsp[-2].sval)); free((yyvsp[-1].sval)); free((yyvsp[0].sval));
    }
#line 1390 "parserLLVM.tab.c"
    break;

  case 33: /* logical_operation: NOT IDENTIFIER IDENTIFIER  */
#line 221 "parserLLVM.y"
                              {
        printf("Logical not: %s %s (not implemented)\n", (yyvsp[-1].sval), (yyvsp[0].sval));
        free((yyvsp[-1].sval)); free((yyvsp[0].sval));
    }
#line 1399 "parserLLVM.tab.c"
    break;

  case 34: /* $@1: %empty  */
#line 229 "parserLLVM.y"
    {
        /* 1) empilha novo nível */
        int depth = if_depth++;
        /* 2) cria blocos THEN e END */
        if_then_stack[depth]  = LLVMAppendBasicBlockInContext(context, main_func, "if.then");
        if_merge_stack[depth] = LLVMAppendBasicBlockInContext(context, main_func, "if.end");
        /* 3) inicializa flag de terminador */
        then_terminated[depth] = false;

        /* 4) carrega a variável e faz a comparação */
        LLVMValueRef var = LLVMBuildLoad2(
            builder,
            LLVMDoubleTypeInContext(context),
            find_variable((yyvsp[-3].sval)),
            "if.load"
        );
        LLVMValueRef cmp;
        if      (strcmp((yyvsp[-2].sval), "==") == 0) cmp = LLVMBuildFCmp(builder, LLVMRealOEQ, var, (yyvsp[-1].lval), "if.cmp");
        else if (strcmp((yyvsp[-2].sval), "!=") == 0) cmp = LLVMBuildFCmp(builder, LLVMRealONE, var, (yyvsp[-1].lval), "if.cmp");
        else if (strcmp((yyvsp[-2].sval), "<" ) == 0) cmp = LLVMBuildFCmp(builder, LLVMRealOLT, var, (yyvsp[-1].lval), "if.cmp");
        else if (strcmp((yyvsp[-2].sval), ">" ) == 0) cmp = LLVMBuildFCmp(builder, LLVMRealOGT, var, (yyvsp[-1].lval), "if.cmp");
        else if (strcmp((yyvsp[-2].sval), "<=") == 0) cmp = LLVMBuildFCmp(builder, LLVMRealOLE, var, (yyvsp[-1].lval), "if.cmp");
        else                            cmp = LLVMBuildFCmp(builder, LLVMRealOGE, var, (yyvsp[-1].lval), "if.cmp");

        /* 5) faz o branch condicional */
        LLVMBuildCondBr(builder, cmp,
                        if_then_stack[depth],
                        if_merge_stack[depth]);

        /* 6) posiciona o builder no início do THEN */
        LLVMPositionBuilderAtEnd(builder, if_then_stack[depth]);

        free((yyvsp[-3].sval));
        free((yyvsp[-2].sval));
    }
#line 1439 "parserLLVM.tab.c"
    break;

  case 35: /* if_stmt: IF IDENTIFIER comparator value NEWLINE $@1 then_block  */
#line 265 "parserLLVM.y"
    {
        /* 7) ao sair do THEN, só emite merge se não houve goto/exit */
        int depth = --if_depth;
        if (!then_terminated[depth]) {
            LLVMBuildBr(builder, if_merge_stack[depth]);
            LLVMPositionBuilderAtEnd(builder, if_merge_stack[depth]);
        }
        /* caso contrário, já estamos no bloco de continuação apropriado */
    }
#line 1453 "parserLLVM.tab.c"
    break;

  case 39: /* comparator: EQUAL  */
#line 285 "parserLLVM.y"
                  { (yyval.sval) = copyString("=="); }
#line 1459 "parserLLVM.tab.c"
    break;

  case 40: /* comparator: NOTEQUAL  */
#line 286 "parserLLVM.y"
                  { (yyval.sval) = copyString("!="); }
#line 1465 "parserLLVM.tab.c"
    break;

  case 41: /* comparator: LESS  */
#line 287 "parserLLVM.y"
                  { (yyval.sval) = copyString("<"); }
#line 1471 "parserLLVM.tab.c"
    break;

  case 42: /* comparator: GREATER  */
#line 288 "parserLLVM.y"
                  { (yyval.sval) = copyString(">"); }
#line 1477 "parserLLVM.tab.c"
    break;

  case 43: /* comparator: LESSEQUAL  */
#line 289 "parserLLVM.y"
                  { (yyval.sval) = copyString("<="); }
#line 1483 "parserLLVM.tab.c"
    break;

  case 44: /* comparator: GREATEREQUAL  */
#line 290 "parserLLVM.y"
                  { (yyval.sval) = copyString(">="); }
#line 1489 "parserLLVM.tab.c"
    break;

  case 45: /* label_def: LABEL IDENTIFIER  */
#line 294 "parserLLVM.y"
                     {
        LLVMBasicBlockRef bb = LLVMAppendBasicBlockInContext(
            context,
            main_func,
            (yyvsp[0].sval)
        );
        // Registra no mapa
        registerLabel((yyvsp[0].sval), bb);
        // Fecha o bloco anterior com um branch
        LLVMBuildBr(builder, bb);
        // Move o builder para o rótulo
        LLVMPositionBuilderAtEnd(builder, bb);
        free((yyvsp[0].sval));
    }
#line 1508 "parserLLVM.tab.c"
    break;

  case 46: /* goto_command: GOTO IDENTIFIER  */
#line 313 "parserLLVM.y"
                    {
        LLVMBasicBlockRef target = findLabel((yyvsp[0].sval));
        if (!target) {
            yyerror("Label não encontrada");
        } else {
            /* 1) branch direto ao label */
            LLVMBuildBr(builder, target);
            /* 2) sinaliza que o THEN foi terminado */
            then_terminated[if_depth-1] = true;
            /* 3) reposiciona o builder no bloco de merge do if */
            LLVMPositionBuilderAtEnd(builder, if_merge_stack[if_depth-1]);
        }
        free((yyvsp[0].sval));
    }
#line 1527 "parserLLVM.tab.c"
    break;

  case 47: /* exit_command: EXIT  */
#line 332 "parserLLVM.y"
         {
        // 1) termina a função aqui
        LLVMBuildRetVoid(builder);
        then_terminated[if_depth-1] = true;

        // 2) cria um bloco de continuação único, para qualquer código após o exit
        char cont_name[32];
        snprintf(cont_name, sizeof(cont_name), "cont.exit.%d", exit_cont++);
        LLVMBasicBlockRef cont = LLVMAppendBasicBlockInContext(
            context,
            main_func,
            cont_name
        );

        // 3) move o builder para dentro desse bloco de continuação
        LLVMPositionBuilderAtEnd(builder, cont);
    }
#line 1549 "parserLLVM.tab.c"
    break;

  case 48: /* input_command: INPUT IDENTIFIER  */
#line 353 "parserLLVM.y"
                     {
        // 0) Garante que temos a função printf disponível
        LLVMValueRef printf_func = LLVMGetNamedFunction(module, "printf");
        LLVMTypeRef printf_ty;
        if (!printf_func) {
            LLVMTypeRef param_types[] = { LLVMPointerType(LLVMInt8TypeInContext(context), 0) };
            printf_ty = LLVMFunctionType(LLVMInt32TypeInContext(context), param_types, 1, /*isVarArg=*/1);
            printf_func = LLVMAddFunction(module, "printf", printf_ty);
            LLVMSetLinkage(printf_func, LLVMExternalLinkage);
        } else {
            printf_ty = LLVMGetElementType(LLVMTypeOf(printf_func));
        }
        // 0.1) Imprime uma mensagem padrao de input
        LLVMValueRef prompt = LLVMBuildGlobalStringPtr(builder, "input: ", "prompt");
        LLVMBuildCall2(builder, printf_ty, printf_func, (LLVMValueRef[]){ prompt }, 1, "");
        // 1) Obtem (ou adiciona) a declaração de scanf
        LLVMValueRef scanf_func = LLVMGetNamedFunction(module, "scanf");
        if (!scanf_func) {
            // scanf retorna int e recebe (i8*, double*)
            LLVMTypeRef param_types[] = {
                LLVMPointerType(LLVMInt8TypeInContext(context), 0),
                LLVMPointerType(LLVMDoubleTypeInContext(context), 0)
            };
            LLVMTypeRef scanf_type = LLVMFunctionType(
                LLVMInt32TypeInContext(context),
                param_types, 2, /*isVarArg=*/1
            );
            scanf_func = LLVMAddFunction(module, "scanf", scanf_type);
            LLVMSetLinkage(scanf_func, LLVMExternalLinkage);
        }

        // 2) Constroi a string de formato "%lf"
        LLVMValueRef fmt = LLVMBuildGlobalStringPtr(
            builder, "%lf", "fmt_scanf"
        );

        // 3) Passa (&variavel) diretamente, pois globals já são ponteiros
        LLVMValueRef var_ptr = find_or_create_variable((yyvsp[0].sval));

        // 4) Chama scanf(fmt, var_ptr)
        LLVMBuildCall2(
            builder,
            LLVMGetElementType(LLVMTypeOf(scanf_func)),
            scanf_func,
            (LLVMValueRef[]){ fmt, var_ptr },
            2,
            ""
        );

        free((yyvsp[0].sval));
    }
#line 1605 "parserLLVM.tab.c"
    break;

  case 49: /* print_command: PRINT STRING  */
#line 407 "parserLLVM.y"
                 {
        // 1) recupera/declara printf como antes
        LLVMValueRef printf_fn = LLVMGetNamedFunction(module, "printf");
        LLVMTypeRef printf_ty;
        if (!printf_fn) {
            LLVMTypeRef params[] = {
                LLVMPointerType(LLVMInt8TypeInContext(context), 0)
            };
            printf_ty = LLVMFunctionType(
                LLVMInt32TypeInContext(context),
                params, 1, /*isVarArg=*/1
            );
            printf_fn = LLVMAddFunction(module, "printf", printf_ty);
            LLVMSetLinkage(printf_fn, LLVMExternalLinkage);
        } else {
            printf_ty = LLVMGetElementType(LLVMTypeOf(printf_fn));
        }

        // 2) formato "%s\n"
        LLVMValueRef fmt_str = LLVMBuildGlobalStringPtr(
            builder, "%s\n", "fmt_str"
        );
        // 3) global string ptr para o literal $2
        LLVMValueRef str_ptr = LLVMBuildGlobalStringPtr(
            builder, (yyvsp[0].sval), "str"
        );
        // 4) call printf(fmt_str, str_ptr)
        LLVMBuildCall2(
            builder,
            printf_ty,
            printf_fn,
            (LLVMValueRef[]){ fmt_str, str_ptr },
            2,
            ""
        );
        free((yyvsp[0].sval));
    }
#line 1647 "parserLLVM.tab.c"
    break;

  case 50: /* print_command: PRINT value  */
#line 444 "parserLLVM.y"
                {
        // mesmo código que você já tinha:
        LLVMValueRef printf_fn = LLVMGetNamedFunction(module, "printf");
        LLVMTypeRef printf_ty;
        if (!printf_fn) {
            LLVMTypeRef params[] = {
                LLVMPointerType(LLVMInt8TypeInContext(context), 0)
            };
            printf_ty = LLVMFunctionType(
                LLVMInt32TypeInContext(context),
                params, 1, /*isVarArg=*/1
            );
            printf_fn = LLVMAddFunction(module, "printf", printf_ty);
            LLVMSetLinkage(printf_fn, LLVMExternalLinkage);
        } else {
            printf_ty = LLVMGetElementType(LLVMTypeOf(printf_fn));
        }

        // formato "%f\n"
        LLVMValueRef fmt_f = LLVMBuildGlobalStringPtr(
            builder, "%f\n", "fmt_f"
        );
        // call printf(fmt_f, $2)
        LLVMBuildCall2(
            builder,
            printf_ty,
            printf_fn,
            (LLVMValueRef[]){ fmt_f, (yyvsp[0].lval) },
            2,
            ""
        );
    }
#line 1684 "parserLLVM.tab.c"
    break;

  case 51: /* bin_command: BIN IDENTIFIER IDENTIFIER  */
#line 480 "parserLLVM.y"
                              {
        printf("Bin: %s to %s (not implemented)\n", (yyvsp[-1].sval), (yyvsp[0].sval));
        free((yyvsp[-1].sval)); free((yyvsp[0].sval));
    }
#line 1693 "parserLLVM.tab.c"
    break;

  case 52: /* list_command: LIST IDENTIFIER  */
#line 488 "parserLLVM.y"
                    {
        // Nome dos globals: "<nome>_data" e "<nome>_len"
        char data_name[256], len_name[256];
        snprintf(data_name, sizeof(data_name), "%s_data", (yyvsp[0].sval));
        snprintf(len_name,  sizeof(len_name),  "%s_len",  (yyvsp[0].sval));

        // 1) Se ainda não existir, cria o array [1024 x double]
        if (!LLVMGetNamedGlobal(module, data_name)) {
            LLVMTypeRef elem_ty  = LLVMDoubleTypeInContext(context);
            // vetor de tamanho fixo 1024
            LLVMTypeRef array_ty = LLVMArrayType(elem_ty, 1024);
            LLVMValueRef data_g  = LLVMAddGlobal(module, array_ty, data_name);
            // inicializa tudo a zero
            LLVMSetInitializer(data_g, LLVMConstNull(array_ty));
        }

        // 2) Se ainda não existir, cria o global i64 para o length
        if (!LLVMGetNamedGlobal(module, len_name)) {
            LLVMTypeRef i64_ty = LLVMInt64TypeInContext(context);
            LLVMValueRef len_g = LLVMAddGlobal(module, i64_ty, len_name);
            // inicializa em 0
            LLVMSetInitializer(len_g, LLVMConstInt(i64_ty, 0, /*isSigned=*/0));
        }

        free((yyvsp[0].sval));
    }
#line 1724 "parserLLVM.tab.c"
    break;

  case 53: /* list_insert: INSERT IDENTIFIER IDENTIFIER  */
#line 518 "parserLLVM.y"
                                 {
        // Monta nomes dos globals: "<lista>_data" e "<lista>_len"
        char data_name[256], len_name[256];
        snprintf(data_name, sizeof(data_name), "%s_data", (yyvsp[0].sval));
        snprintf(len_name,  sizeof(len_name),  "%s_len",  (yyvsp[0].sval));

        // Obtém os globals já criados em `list_command`
        LLVMValueRef data_g = LLVMGetNamedGlobal(module, data_name);
        LLVMValueRef len_g  = LLVMGetNamedGlobal(module, len_name);
        if (!data_g || !len_g) {
            yyerror("Lista não existe");
            free((yyvsp[-1].sval));
            free((yyvsp[0].sval));
            YYABORT;  /* aborta o parse aqui */
        } else {
            LLVMTypeRef i64_ty = LLVMInt64TypeInContext(context);

            // 1) carrega o comprimento atual
            LLVMValueRef len_val = LLVMBuildLoad2(builder, i64_ty, len_g, "len");

            // 2) calcula ponteiro para data[len]
            LLVMValueRef zero    = LLVMConstInt(i64_ty, 0, 0);
            LLVMValueRef indices[2] = { zero, len_val };
            LLVMValueRef elem_ptr = LLVMBuildInBoundsGEP(
                builder,
                data_g,
                indices,
                2,
                "elem_ptr"
            );

            // 3) carrega o valor da variável a inserir
            LLVMValueRef var = find_variable((yyvsp[-1].sval));
            if (!var) {
                yyerror("Variável não definida");
                var = find_or_create_variable((yyvsp[-1].sval));
            }
            LLVMValueRef val = LLVMBuildLoad2(
                builder,
                LLVMDoubleTypeInContext(context),
                var,
                "val"
            );

            // 4) armazena no array e incrementa len
            LLVMBuildStore(builder, val, elem_ptr);
            LLVMValueRef one     = LLVMConstInt(i64_ty, 1, 0);
            LLVMValueRef new_len = LLVMBuildAdd(builder, len_val, one, "newlen");
            LLVMBuildStore(builder, new_len, len_g);
        }

        free((yyvsp[-1].sval));
        free((yyvsp[0].sval));
    }
#line 1783 "parserLLVM.tab.c"
    break;

  case 54: /* list_delete: DELETE IDENTIFIER IDENTIFIER  */
#line 578 "parserLLVM.y"
                                 {
        // $2 = variável cujo valor será removido
        // $3 = nome da lista
        char data_name[256], len_name[256];
        snprintf(data_name, sizeof(data_name), "%s_data", (yyvsp[0].sval));
        snprintf(len_name,  sizeof(len_name),  "%s_len",  (yyvsp[0].sval));

        // recupera os globals gerados em list_command
        LLVMValueRef data_g = LLVMGetNamedGlobal(module, data_name);
        LLVMValueRef len_g  = LLVMGetNamedGlobal(module, len_name);
        if (!data_g || !len_g) {
            yyerror("Lista não existe");
            free((yyvsp[-1].sval));
            free((yyvsp[0].sval));
            YYABORT;
        }

        LLVMTypeRef dbl_ty = LLVMDoubleTypeInContext(context);
        LLVMTypeRef i64_ty = LLVMInt64TypeInContext(context);

        // carrega o valor a ser removido
        LLVMValueRef var = find_variable((yyvsp[-1].sval));
        if (!var) {
            yyerror("Variável não definida");
            var = find_or_create_variable((yyvsp[-1].sval));
        }
        LLVMValueRef elem_val = LLVMBuildLoad2(
            builder,
            dbl_ty,
            var,
            "elem"
        );

        // bitcast do array estático para double*
        LLVMValueRef data_ptr = LLVMBuildBitCast(
            builder,
            data_g,
            LLVMPointerType(dbl_ty, 0),
            "data_ptr"
        );

        // declara ou recupera a função auxiliar delete_list
        LLVMValueRef del_fn = LLVMGetNamedFunction(module, "delete_list");
        if (!del_fn) {
            LLVMTypeRef params[] = {
                dbl_ty,
                LLVMPointerType(dbl_ty, 0),
                LLVMPointerType(i64_ty, 0)
            };
            LLVMTypeRef fty = LLVMFunctionType(
                LLVMVoidTypeInContext(context),
                params,
                3,
                /*isVarArg=*/0
            );
            del_fn = LLVMAddFunction(module, "delete_list", fty);
            LLVMSetLinkage(del_fn, LLVMExternalLinkage);
        }

        // call delete_list(elem_val, data_ptr, &len)
        LLVMBuildCall2(
            builder,
            LLVMGetElementType(LLVMTypeOf(del_fn)),
            del_fn,
            (LLVMValueRef[]){ elem_val, data_ptr, len_g },
            3,
            ""
        );

        free((yyvsp[-1].sval));
        free((yyvsp[0].sval));
    }
#line 1860 "parserLLVM.tab.c"
    break;

  case 55: /* list_in_check: IN IDENTIFIER IDENTIFIER IDENTIFIER  */
#line 656 "parserLLVM.y"
                                        {
        // monta nomes dos globals
        char data_name[256], len_name[256];
        snprintf(data_name, sizeof(data_name), "%s_data",  (yyvsp[-1].sval));
        snprintf(len_name,  sizeof(len_name),  "%s_len",   (yyvsp[-1].sval));

        // pega o array e o length
        LLVMValueRef data_g = LLVMGetNamedGlobal(module, data_name);
        LLVMValueRef len_g  = LLVMGetNamedGlobal(module, len_name);
        if (!data_g || !len_g) {
            yyerror("Lista não existe");
            free((yyvsp[-2].sval)); free((yyvsp[-1].sval)); free((yyvsp[0].sval));
            YYABORT;
        }

        LLVMTypeRef dbl_ty = LLVMDoubleTypeInContext(context);
        LLVMTypeRef i64_ty = LLVMInt64TypeInContext(context);

        // carrega o length
        LLVMValueRef len_val = LLVMBuildLoad2(builder, i64_ty, len_g, "len");

        // carrega o elemento a testar
        LLVMValueRef var = find_variable((yyvsp[-2].sval));
        if (!var) {
            yyerror("Variável não definida");
            var = find_or_create_variable((yyvsp[-2].sval));
        }
        LLVMValueRef elem_val = LLVMBuildLoad2(builder, dbl_ty, var, "elem");

        // bitcast do global array para double*
        LLVMValueRef data_ptr = LLVMBuildBitCast(
            builder,
            data_g,
            LLVMPointerType(dbl_ty, 0),
            "data_ptr"
        );

        // declara ou recupera a função in_list
        LLVMValueRef in_func = LLVMGetNamedFunction(module, "in_list");
        if (!in_func) {
            LLVMTypeRef fparams[] = { dbl_ty,
                                     LLVMPointerType(dbl_ty,0),
                                     i64_ty };
            LLVMTypeRef fty = LLVMFunctionType(dbl_ty, fparams, 3, /*isVarArg=*/0);
            in_func = LLVMAddFunction(module, "in_list", fty);
            LLVMSetLinkage(in_func, LLVMExternalLinkage);
        }

        // chama in_list(elem_val, data_ptr, len_val)
        LLVMValueRef result = LLVMBuildCall2(
            builder,
            LLVMGetElementType(LLVMTypeOf(in_func)),
            in_func,
            (LLVMValueRef[]){ elem_val, data_ptr, len_val },
            3,
            "inres"
        );

        // armazena o resultado em $4
        LLVMValueRef dest_p = find_or_create_variable((yyvsp[0].sval));
        LLVMBuildStore(builder, result, dest_p);

        free((yyvsp[-2].sval)); free((yyvsp[-1].sval)); free((yyvsp[0].sval));
    }
#line 1929 "parserLLVM.tab.c"
    break;

  case 56: /* get_command: GET value IDENTIFIER IDENTIFIER  */
#line 723 "parserLLVM.y"
                                    {
        // $2 = índice (LLVMValueRef, double)
        // $3 = nome da lista (IDENTIFIER)
        // $4 = variável destino (IDENTIFIER)

        // monta nome do array global
        char data_name[256];
        snprintf(data_name, sizeof(data_name), "%s_data", (yyvsp[-1].sval));
        LLVMValueRef data_g = LLVMGetNamedGlobal(module, data_name);
        if (!data_g) {
            yyerror("Lista não existe");
        } else {
            LLVMTypeRef dbl_ty = LLVMDoubleTypeInContext(context);
            LLVMTypeRef i64_ty = LLVMInt64TypeInContext(context);

            // converte índice de double para i64
            LLVMValueRef idx_d = (yyvsp[-2].lval);
            LLVMValueRef idx_i = LLVMBuildFPToSI(builder, idx_d, i64_ty, "idx");

            // calcula &data[idx]
            LLVMValueRef zero = LLVMConstInt(i64_ty, 0, 0);
            LLVMValueRef gep = LLVMBuildInBoundsGEP(
                builder,
                data_g,
                (LLVMValueRef[]){ zero, idx_i },
                2,
                "elem_ptr"
            );

            // carrega o valor e armazena em dest
            LLVMValueRef elem = LLVMBuildLoad2(builder, dbl_ty, gep, "getval");
            LLVMBuildStore(builder, elem, find_or_create_variable((yyvsp[0].sval)));
        }

        free((yyvsp[-1].sval));
        free((yyvsp[0].sval));
    }
#line 1971 "parserLLVM.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 764 "parserLLVM.y"
           {
        (yyval.lval) = LLVMConstReal(LLVMDoubleTypeInContext(context), (yyvsp[0].dval));
    }
#line 1979 "parserLLVM.tab.c"
    break;

  case 58: /* value: STRING  */
#line 767 "parserLLVM.y"
           {
        (yyval.lval) = LLVMBuildGlobalStringPtr(builder, (yyvsp[0].sval), "str");
        free((yyvsp[0].sval));
    }
#line 1988 "parserLLVM.tab.c"
    break;

  case 59: /* value: TRUE  */
#line 771 "parserLLVM.y"
                 { (yyval.lval) = LLVMConstReal(LLVMDoubleTypeInContext(context), 1.0); }
#line 1994 "parserLLVM.tab.c"
    break;

  case 60: /* value: FALSE  */
#line 772 "parserLLVM.y"
                 { (yyval.lval) = LLVMConstReal(LLVMDoubleTypeInContext(context), 0.0); }
#line 2000 "parserLLVM.tab.c"
    break;

  case 61: /* value: IDENTIFIER  */
#line 773 "parserLLVM.y"
               {
      LLVMValueRef var = find_variable((yyvsp[0].sval));
      if (!var) {
          yyerror("Variável não definida");
          /* para não quebrar o parser, cria provisoriamente
             ou aponta para um dummy, conforme seu gosto */
          var = find_or_create_variable((yyvsp[0].sval));
      }
      (yyval.lval) = LLVMBuildLoad2(builder,
                          LLVMDoubleTypeInContext(context),
                          var,
                          "loadtmp");
      free((yyvsp[0].sval));
  }
#line 2019 "parserLLVM.tab.c"
    break;


#line 2023 "parserLLVM.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 788 "parserLLVM.y"


/* parserLLVM.y, no epílogo */
void delete_list(double elem, double *data, long *len) {
    /* encontra o índice da primeira ocorrência */
    long i;
    for (i = 0; i < *len; ++i) {
        if (data[i] == elem) break;
    }
    /* se achou, desloca tudo para “fechar o buraco” */
    if (i < *len) {
        for (; i + 1 < *len; ++i) {
            data[i] = data[i+1];
        }
        --*len;
    }
}


double in_list(double elem, double *data, long len) {
    for (long i = 0; i < len; ++i) {
        if (data[i] == elem) return 1.0;
    }
    return 0.0;
}


int main(int argc, char **argv) {
    /* Initialize LLVM */
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    context = LLVMContextCreate();
    module = LLVMModuleCreateWithNameInContext("mengo", context);
    builder = LLVMCreateBuilderInContext(context);

    /* Create main function */
    LLVMTypeRef main_type = LLVMFunctionType(LLVMVoidTypeInContext(context), NULL, 0, 0);
    main_func = LLVMAddFunction(module, "main", main_type);
    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(context, main_func, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);

    /* Parse input */
    if (argc > 1) yyin = fopen(argv[1], "r");
    int result = yyparse();
    if (result != 0) {
        fprintf(stderr, "Parse failed, aborting LLVM emission.\n");
        return result;
    }

    // só daqui pra baixo se parse OK
    LLVMBuildRetVoid(builder);

    char *error = NULL;
    if (LLVMVerifyModule(module, LLVMReturnStatusAction, &error)) {
        fprintf(stderr, "Module verification error: %s\n", error);
        LLVMDisposeMessage(error);
        return 1;
    }


    /* Write bitcode (for debugging) */
    LLVMWriteBitcodeToFile(module, "mengo.bc");

    /* Execute with JIT */
    LLVMExecutionEngineRef engine;
    if (LLVMCreateExecutionEngineForModule(&engine, module, &error)) {
        fprintf(stderr, "Error creating execution engine: %s\n", error);
        LLVMDisposeMessage(error);
        return 1;
    }
    
    LLVMLoadLibraryPermanently(NULL);

    LLVMRunFunction(engine, main_func, 0, NULL);

    /* Cleanup */
    for (int i = 0; i < symbol_count; i++) {
        free(symbol_table[i].name);
    }
    LLVMDisposeExecutionEngine(engine);
    LLVMDisposeBuilder(builder);
    LLVMContextDispose(context);

    return result;
}
