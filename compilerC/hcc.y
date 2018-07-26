%{
/*
**Grammatical specification for HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/
#include "c.h"

static void yyerror(char *s);

/* current translation unit */
ASTTranslationunit * translationunit;
/* current function declaration */
ASTFunctiondeclaration *curfunc;

extern Coordinate tcoord;
extern Tvalue tval;
%}

%union {
  ASTBase *ast;
};

/* researved keywords */
%token AUTO
%token BREAK
%token CASE CHAR CONST CONTINUE
%token DEFAULT DO DOUBLE
%token ELSE ENUM EXTERN
%token FLOAT FOR
%token GOTO
%token IF INT
%token LONG
%token REGISTER RETURN
%token SHORT SIGNED SIZEOF STATIC STRUCT SWITCH
%token TYPEDEF TYPENAME
%token UNION UNSIGNED
%token VOID VOLATILE
%token WHILE
%token LOGIN
%token LOGOUT


/* identifiers and constants */
%token IDENTIFIER
%token INTCONST UINT LINT ULINT LLINT ULLINT
%token DOUBLECONST LDOUBLECONST FLOATCONST
%token STRING

/* multi-character operators */
%token ELLIPSIS
%token RIGHT_ASSIGN LEFT_ASSIGN
%token SUB_ASSIGN ADD_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN
%token AND_ASSIGN OR_ASSIGN XOR_ASSIGN
%token RIGHT_SHIFT LEFT_SHIFT
%token INC_OP DEC_OP
%token PTR_OP
%token AND_OP OR_OP
%token LE_OP GE_OP EQ_OP NE_OP

/* implicit operators */
%token CAST_OP INDEX_OP CALL_OP MEMBER_OP POST_INC_DEC_OP COND_OP
%token CALL_LOGIN CALL_LOGOUT
/* solve the dangling else REDUCE/SHIFT conflict */
%nonassoc IFX
%nonassoc ELSE

%{
/* operator precedence and associativity definition */
/* currently, I simply rewrite the garmmer to deal with this. */
/* we should switch to this precedence table later */
/*
%left ','
%right ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN
%right '?' ':'
%left OR_OP
%left AND_OP
%left '|'
%left '^'
%left '&'
%left EQ_OP NE_OP
%left '<' LE_OP GE_OP '>'
%left LEFT_SHIFT RIGHT_SHIFT
%left '+' '-'
%left '*' '/' '%'
%right '!' '~' INC_OP DEC_OP SIZEOF CAST_OP 
%left '(' '[' PTR_OP '.'
*/
%}

/* non-terminals in the grammar */
%type<ast> extdecls extdecl
%type<ast> declaration function_declaration declaration_list
%type<ast> declaration_specifiers declarator 
%type<ast> init_declarator_list init_declarator initializer initializer_list
%type<ast> storage_class_specifier type_specifier type_qualifier type_qualifier_list
%type<ast> enum_specifier struct_or_union_specifier
%type<ast> enumerator_list enumerator
%type<ast> identifier identifier_list
%type<ast> struct_or_union struct_declaration_list struct_declaration
%type<ast> specifier_qualifier_list struct_declarator_list struct_declarator
%type<ast> pointer pointer_mark direct_declarator
%type<ast> parameter_type_list parameter_list parameter_declaration
%type<ast> abstract_declarator direct_abstract_declarator
%type<ast> constant_expression conditional_expression assignment_expression expression
%type<ast> assignment_operator unary_expression cast_expression 
%type<ast> postfix_expression argument_expression_list primary_expression
%type<ast> unary_operator type_name inc_dec_op sizeof_op
%type<ast> logical_or_expression logical_and_expression inclusive_or_expression
%type<ast> exclusive_or_expression and_expression
%type<ast> multiplicative_expression additive_expression shift_expression 
%type<ast> relational_expression equality_expression
%type<ast> statement compound_statement labeled_statement statement_list
%type<ast> expression_statement selection_statement iteration_statement jump_statement
%type<ast> default_keyword case_keyword left_paren left_bracket left_brace semicolon
%type<ast> if_keyword else_keyword switch_keyword enum_keyword 
%type<ast> while_keyword do_keyword for_keyword goto_keyword
%type<ast> return_keyword break_keyword continue_keyword
%type<ast> notype_declaration data_declaration

/* start point of the parser */
%start translation_unit

%%
translation_unit: extdecls  {translationunit = create_translationunit($1);}
                  ;

extdecls: extdecl           {$$=$1;}
         |extdecls extdecl  {$$=append_astnode($1,$2);}
         ;

extdecl: function_declaration {$$=$1;}
         | data_declaration   {$$=$1;}
         ;

declaration: declaration_specifiers init_declarator_list semicolon
              {$$=base_of(create_declaration($1,$2));}
            |declaration_specifiers semicolon
              {$$=base_of(create_declaration($1,NULL));}
            ;

notype_declaration: init_declarator_list semicolon
              {$$=base_of(create_declaration(NULL,$1));}
              ;

data_declaration: declaration         {$$=$1;}
                 |notype_declaration  {$$=$1;}
                 ;

function_declaration: declaration_specifiers declarator declaration_list compound_statement
                       {$$=base_of(create_functiondeclaration($1,$2,$3,$4));}
                     |declaration_specifiers declarator compound_statement
                       {$$=base_of(create_functiondeclaration($1,$2,NULL,$3));}
                     |declarator declaration_list compound_statement
                       {$$=base_of(create_functiondeclaration(NULL,$1,$2,$3));}
                     |declarator compound_statement
                       {$$=base_of(create_functiondeclaration(NULL,$1,NULL,$2));}
                     ;

declaration_list: declaration                  {$$=$1;}
                 |declaration_list declaration {$$=append_astnode($1,$2);}
                 ;

init_declarator_list: init_declarator                          {$$=$1;}
                     |init_declarator_list ',' init_declarator {$$=append_astnode($1,$3);}
                     ;

declaration_specifiers: storage_class_specifier
                          {$$ = base_of(create_declarationspecifier1($1));}
                       |storage_class_specifier declaration_specifiers
                          {$$ = base_of(create_declarationspecifier2($1,$2));}
                       |type_specifier
                          {$$ = base_of(create_declarationspecifier3($1));}
                       |type_specifier declaration_specifiers
                          {$$ = base_of(create_declarationspecifier4($1,$2));}
                       |type_qualifier
                          {$$ = base_of(create_declarationspecifier5($1));}
                       |type_qualifier declaration_specifiers
                          {$$ = base_of(create_declarationspecifier6($1,$2));}
                       ;

storage_class_specifier: AUTO      {$$ = base_of(create_atom(AUTO,tval,tcoord));}
                        |REGISTER  {$$ = base_of(create_atom(REGISTER,tval,tcoord));}
                        |STATIC    {$$ = base_of(create_atom(STATIC,tval,tcoord));}
                        |EXTERN    {$$ = base_of(create_atom(EXTERN,tval,tcoord));}
                        |TYPEDEF   {$$ = base_of(create_atom(TYPEDEF,tval,tcoord));}
                        ;

type_qualifier: CONST    {$$ = base_of(create_atom(CONST,tval,tcoord));}
               |VOLATILE {$$ = base_of(create_atom(VOLATILE,tval,tcoord));}
               ;

type_specifier: VOID                      {$$ = base_of(create_atom(VOID,tval,tcoord));}
               |CHAR                      {$$ = base_of(create_atom(CHAR,tval,tcoord));}
               |SHORT                     {$$ = base_of(create_atom(SHORT,tval,tcoord));}
               |INT                       {$$ = base_of(create_atom(INT,tval,tcoord));}
               |LONG                      {$$ = base_of(create_atom(LONG,tval,tcoord));}
               |SIGNED                    {$$ = base_of(create_atom(SIGNED,tval,tcoord));}
               |UNSIGNED                  {$$ = base_of(create_atom(UNSIGNED,tval,tcoord));}
               |FLOAT                     {$$ = base_of(create_atom(FLOAT,tval,tcoord));}
               |DOUBLE                    {$$ = base_of(create_atom(DOUBLE,tval,tcoord));}
               |TYPENAME                  {$$ = base_of(create_atom(TYPENAME,tval,tcoord));}
               |enum_specifier            {$$ = $1;}
               |struct_or_union_specifier {$$ = $1;}
               ;

enum_specifier: enum_keyword identifier                
                 {$$=base_of(create_enumspec($1,$2,NULL));}        
               |enum_keyword left_brace enumerator_list '}'
                 {$$=base_of(create_enumspec($1,NULL,$3));}
               |enum_keyword left_brace enumerator_list ',' '}'
                 {$$=base_of(create_enumspec($1,NULL,$3));}
               |enum_keyword identifier left_brace enumerator_list '}'  
                 {$$=base_of(create_enumspec($1,$2,$4));}
               |enum_keyword identifier left_brace enumerator_list ',' '}' 
                 {$$=base_of(create_enumspec($1,$2,$4));}
               ;

enum_keyword: ENUM {$$=base_of(create_atom(ENUM,tval,tcoord));}
           ;

identifier: IDENTIFIER {$$ = base_of(create_atom(IDENTIFIER,tval,tcoord));}
            ;


enumerator_list: enumerator                 {$$=$1;}
                |enumerator_list ',' enumerator {$$=append_astnode($1,$3);}
                ;

enumerator: identifier                         {$$=base_of(create_enumerator($1,NULL));}
           |identifier '=' constant_expression {$$=base_of(create_enumerator($1,$3));}
           ;

constant_expression: conditional_expression {$$=$1;}
                     ;

struct_or_union_specifier: struct_or_union identifier
                            {$$=base_of(create_structorunion($1,$2,NULL));}
                          |struct_or_union identifier left_brace struct_declaration_list '}'
                            {$$=base_of(create_structorunion($1,$2,$4));}
                          |struct_or_union left_brace struct_declaration_list '}'
                            {$$=base_of(create_structorunion($1,NULL,$3));}
                          ;

struct_or_union: STRUCT {$$=base_of(create_atom(STRUCT,tval,tcoord));}
                |UNION  {$$=base_of(create_atom(UNION,tval,tcoord));}
                ;

struct_declaration_list: struct_declaration
                          {$$=$1;}
                        |struct_declaration_list struct_declaration
                          {$$=append_astnode($1,$2);}
                        ;

struct_declaration: specifier_qualifier_list struct_declarator_list semicolon
                     {$$=base_of(create_structdeclaration($1,$2));}
                    ;

specifier_qualifier_list: type_specifier 
                          {$$ = base_of(create_declarationspecifier3($1));}
                         |type_specifier specifier_qualifier_list
                          {$$ = base_of(create_declarationspecifier4($1,$2));}
                         |type_qualifier 
                          {$$ = base_of(create_declarationspecifier5($1));}
                         |type_qualifier specifier_qualifier_list
                          {$$ = base_of(create_declarationspecifier6($1,$2));}
                         ;

struct_declarator_list: struct_declarator                            {$$=$1;}
                       |struct_declarator_list ',' struct_declarator {$$=append_astnode($1,$3);}
                       ;

struct_declarator: declarator
                    {$$=base_of(create_structdeclarator($1,NULL));}
                  | ':' constant_expression
                    {$$=base_of(create_structdeclarator(NULL,$2));}
                  |declarator ':' constant_expression
                    {$$=base_of(create_structdeclarator($1,$3));}
                  ;
 
declarator: pointer direct_declarator
             {$$=base_of(chain_pointerdeclarator($1,$2));}
           |direct_declarator
             {$$=$1;}
           ;

pointer: pointer_mark
          { $$ = base_of(create_pointerdeclarator($1->coord,NULL,NULL));}
        |pointer_mark type_qualifier_list
          { $$ = base_of(create_pointerdeclarator($1->coord,$2,NULL));}
        |pointer_mark pointer
          { $$ = base_of(create_pointerdeclarator($1->coord,NULL,$2));}
        |pointer_mark type_qualifier_list pointer
          { $$ = base_of(create_pointerdeclarator($1->coord,$2,$3));}
        ;

pointer_mark: '*' {$$=base_of(create_atom('*',tval,tcoord));}
              ;

type_qualifier_list: type_qualifier                     {$$=$1;}
                    |type_qualifier_list type_qualifier {$$=append_astnode($1,$2);}
                    ;

direct_declarator: identifier
                    {$$=base_of(create_directdeclarator($1));}
                  |left_paren declarator ')'
                    {$$=$2; $$->has_paren = 1;}
                  |direct_declarator left_bracket constant_expression ']'
                    {$$=base_of(create_arraydeclarator($1,$3));}
                  |direct_declarator left_bracket ']'
                    {$$=base_of(create_arraydeclarator($1,NULL));}
                  |direct_declarator left_paren parameter_type_list ')'
                    {$$=base_of(create_funcdeclarator($1,$3,NULL));}
                  |direct_declarator left_paren identifier_list ')'
                    {$$=base_of(create_funcdeclarator($1,NULL,$3));}
                  |direct_declarator left_paren ')'
                    {$$=base_of(create_funcdeclarator($1,NULL,NULL));}
                  ;

identifier_list: identifier                 {$$=$1;}
                |identifier_list ',' identifier {$$=append_astnode($1,$3);}
                ;

parameter_type_list: parameter_list              {$$=base_of(create_paramtypelist($1,0));}
                    |parameter_list ',' ELLIPSIS {$$=base_of(create_paramtypelist($1,1));}
                    ;

parameter_list: parameter_declaration                    {$$=$1;}
               |parameter_list ',' parameter_declaration {$$=append_astnode($1,$3);}
               ;

parameter_declaration: declaration_specifiers
                        {$$=base_of(create_paramdeclaration($1,NULL));}
                      |declaration_specifiers declarator
                        {$$=base_of(create_paramdeclaration($1,$2));}
                      |declaration_specifiers abstract_declarator
                        {$$=base_of(create_paramdeclaration($1,$2));}
                      ;

abstract_declarator: pointer
                      {$$=$1;}
                    |direct_abstract_declarator
                      {$$=$1;}
                    |pointer direct_abstract_declarator
                      {$$=base_of(chain_pointerdeclarator($1,$2));}
                    ;

direct_abstract_declarator: left_paren abstract_declarator ')'
                             {$$=$2; $$->has_paren = 1;}
                           |left_bracket ']'
                             {$$=base_of(create_arraydeclarator(base_of(create_abstractdeclarator($1->coord)),NULL));} 
                           |left_bracket constant_expression ']'
                             {$$=base_of(create_arraydeclarator(base_of(create_abstractdeclarator($1->coord)),$2));} 
                           |direct_abstract_declarator left_bracket ']'
                             {$$=base_of(create_arraydeclarator($1,NULL));}
                           |direct_abstract_declarator left_bracket constant_expression ']'
                             {$$=base_of(create_arraydeclarator($1,$3));}
                           |left_paren ')'
                             {$$=base_of(create_funcdeclarator(base_of(create_abstractdeclarator($1->coord)),NULL,NULL));}
                           |left_paren parameter_type_list ')'
                             {$$=base_of(create_funcdeclarator(base_of(create_abstractdeclarator($1->coord)),$2,NULL));}
                           |direct_abstract_declarator left_paren ')'
                             {$$=base_of(create_funcdeclarator($1,NULL,NULL));}
                           |direct_abstract_declarator left_paren parameter_type_list ')'
                             {$$=base_of(create_funcdeclarator($1,$3,NULL));}
                           ;

left_bracket: '[' {$$=base_of(create_atom('[',tval,tcoord));}
             ;

left_paren: '(' {$$=base_of(create_atom('(',tval,tcoord));}
           ;

init_declarator: declarator
                 {$$=base_of(create_initdeclarator($1,NULL));}
                |declarator '=' initializer
                 {$$=base_of(create_initdeclarator($1,$3));}
                ;

initializer: assignment_expression
              {$$=base_of(create_initializer(0,$1));}
            |left_brace initializer_list '}'
              {$$=base_of(create_initializer(1,$2));}
            |left_brace initializer_list ',' '}'
              {$$=base_of(create_initializer(1,$2));}
            ;

initializer_list: initializer
                   {$$=$1;}
                 |initializer_list ',' initializer
                   {$$=append_astnode($1,$3);}
                 ;

expression: assignment_expression
             {$$=$1;}
           |expression ',' assignment_expression
             {$$=base_of(create_binaryexpression(',',$1,$3));}
           ;

assignment_expression: conditional_expression
                        {$$=$1;}
                      |unary_expression assignment_operator assignment_expression
                        {$$=base_of(create_binaryexpression1($2,$1,$3));}
                      ;

assignment_operator: '='          {$$=base_of(create_atom('=',tval,tcoord));}
                    |MUL_ASSIGN   {$$=base_of(create_atom(MUL_ASSIGN,tval,tcoord));}
                    |DIV_ASSIGN   {$$=base_of(create_atom(DIV_ASSIGN,tval,tcoord));}
                    |MOD_ASSIGN   {$$=base_of(create_atom(MOD_ASSIGN,tval,tcoord));}
                    |ADD_ASSIGN   {$$=base_of(create_atom(ADD_ASSIGN,tval,tcoord));}
                    |SUB_ASSIGN   {$$=base_of(create_atom(SUB_ASSIGN,tval,tcoord));}
                    |LEFT_ASSIGN  {$$=base_of(create_atom(LEFT_ASSIGN,tval,tcoord));}
                    |RIGHT_ASSIGN {$$=base_of(create_atom(RIGHT_ASSIGN,tval,tcoord));}
                    |AND_ASSIGN   {$$=base_of(create_atom(AND_ASSIGN,tval,tcoord));}
                    |XOR_ASSIGN   {$$=base_of(create_atom(XOR_ASSIGN,tval,tcoord));}
                    |OR_ASSIGN    {$$=base_of(create_atom(OR_ASSIGN,tval,tcoord));}
                    ;

unary_expression: postfix_expression
                   {$$=$1;}
                 |inc_dec_op unary_expression
                   {$$=base_of(create_unaryexpression($1,$2));}
                 |unary_operator cast_expression
                   {$$=base_of(create_unaryexpression($1,$2));}
                 |sizeof_op unary_expression
                   {$$=base_of(create_unaryexpression($1,$2));}
                 |sizeof_op left_paren type_name ')'
                   {$$=base_of(create_unaryexpression1($1,$3));}
                 ;

inc_dec_op: INC_OP {$$=base_of(create_atom(INC_OP,tval,tcoord));}
           |DEC_OP {$$=base_of(create_atom(DEC_OP,tval,tcoord));}
           ;

sizeof_op: SIZEOF {$$=base_of(create_atom(SIZEOF,tval,tcoord));}
           ;

unary_operator: '&' {$$=base_of(create_atom('&',tval,tcoord));}
               |'+' {$$=base_of(create_atom('+',tval,tcoord));}
               |'-' {$$=base_of(create_atom('-',tval,tcoord));}
               |'~' {$$=base_of(create_atom('~',tval,tcoord));}
               |'!' {$$=base_of(create_atom('!',tval,tcoord));}
               | pointer_mark {$$=$1;}
               ;

type_name: specifier_qualifier_list
            {$$=base_of(create_typename($1,NULL));}
          |specifier_qualifier_list abstract_declarator
            {$$=base_of(create_typename($1,$2));}
          ;

cast_expression: unary_expression
                  {$$=$1;}
                |left_paren type_name ')' cast_expression
                  {$$=base_of(create_castexpression(CAST_OP,$2,$4));}
                ;

postfix_expression: primary_expression
                    {$$=$1;}
                   |postfix_expression left_bracket expression ']'
                    {$$=base_of(create_postfixexpression(INDEX_OP,$1,$3));}
                   |postfix_expression left_paren ')'
                    {$$=base_of(create_postfixexpression(CALL_OP,$1,NULL));}
                   |postfix_expression left_paren argument_expression_list ')'
                    {$$=base_of(create_postfixexpression(CALL_OP,$1,$3));}
                   |postfix_expression '.' identifier
                    {$$=base_of(create_postfixexpression(MEMBER_OP,$1,$3));}
                   |postfix_expression PTR_OP identifier
                    {$$=base_of(create_postfixexpression(PTR_OP,$1,$3));}
                   |postfix_expression inc_dec_op
                    {$$=base_of(create_postfixexpression(POST_INC_DEC_OP,$1,$2));}
                   ;

argument_expression_list: assignment_expression
                           {$$=$1;}
                         |argument_expression_list ',' assignment_expression
                           {$$=append_astnode($1,$3);}
                         ;

primary_expression: identifier
                     {$$=base_of(create_primaryexpression($1));}
                   |INTCONST
                     {$$=base_of(create_primaryexpression(base_of(create_atom(INTCONST,tval,tcoord))));}
                   |UINT
                     {$$=base_of(create_primaryexpression(base_of(create_atom(UINT,tval,tcoord))));}
                   |LINT
                     {$$=base_of(create_primaryexpression(base_of(create_atom(LINT,tval,tcoord))));}
                   |ULINT
                     {$$=base_of(create_primaryexpression(base_of(create_atom(ULINT,tval,tcoord))));}
                   |LLINT
                     {$$=base_of(create_primaryexpression(base_of(create_atom(LLINT,tval,tcoord))));}
                   |ULLINT
                     {$$=base_of(create_primaryexpression(base_of(create_atom(ULLINT,tval,tcoord))));}
                   |DOUBLECONST
                     {$$=base_of(create_primaryexpression(base_of(create_atom(DOUBLECONST,tval,tcoord))));}
                   |LDOUBLECONST
                     {$$=base_of(create_primaryexpression(base_of(create_atom(LDOUBLECONST,tval,tcoord))));}
                   |FLOATCONST
                     {$$=base_of(create_primaryexpression(base_of(create_atom(FLOATCONST,tval,tcoord))));}
                   |STRING
                     {$$=base_of(create_primaryexpression(base_of(create_atom(STRING,tval,tcoord))));}
                   |left_paren expression ')'
                     {$$=$2; $$->has_paren = 1;}
                   ;

conditional_expression: logical_or_expression
                         {$$=$1;}
                       |logical_or_expression '?' expression ':' conditional_expression
                         {$$=base_of(create_conditionalexpression(COND_OP,$1,$3,$5));}
                       ;

logical_or_expression: logical_and_expression
                        {$$=$1;}
                      |logical_or_expression OR_OP logical_and_expression
                        {$$=base_of(create_binaryexpression(OR_OP,$1,$3));}
                      ;

logical_and_expression: inclusive_or_expression
                        {$$=$1;}
                       |logical_and_expression AND_OP inclusive_or_expression
                        {$$=base_of(create_binaryexpression(AND_OP,$1,$3));}
                       ;

inclusive_or_expression: exclusive_or_expression
                        {$$=$1;}
                        |inclusive_or_expression '|' exclusive_or_expression
                        {$$=base_of(create_binaryexpression('|',$1,$3));}
                        ;

exclusive_or_expression: and_expression
                        {$$=$1;}
                        |exclusive_or_expression '^' and_expression
                        {$$=base_of(create_binaryexpression('^',$1,$3));}
                        ;

and_expression: equality_expression
                 {$$=$1;}
               |and_expression '&' equality_expression
                 {$$=base_of(create_binaryexpression('&',$1,$3));}
               ;

equality_expression: relational_expression
                      {$$=$1;}
                    |equality_expression EQ_OP relational_expression
                      {$$=base_of(create_binaryexpression(EQ_OP,$1,$3));}
                    |equality_expression NE_OP relational_expression
                      {$$=base_of(create_binaryexpression(NE_OP,$1,$3));}
                    ;

relational_expression: shift_expression
                        {$$=$1;}
                      |relational_expression '<' shift_expression
                        {$$=base_of(create_binaryexpression('<',$1,$3));}
                      |relational_expression '>' shift_expression
                        {$$=base_of(create_binaryexpression('>',$1,$3));}
                      |relational_expression LE_OP shift_expression
                        {$$=base_of(create_binaryexpression(LE_OP,$1,$3));}
                      |relational_expression GE_OP shift_expression
                        {$$=base_of(create_binaryexpression(GE_OP,$1,$3));}
                      ;

shift_expression: additive_expression
                   {$$=$1;}
                 |shift_expression LEFT_SHIFT additive_expression
                   {$$=base_of(create_binaryexpression(LEFT_SHIFT,$1,$3));}
                 |shift_expression RIGHT_SHIFT additive_expression
                   {$$=base_of(create_binaryexpression(RIGHT_SHIFT,$1,$3));}
                 ;

additive_expression: multiplicative_expression
                      {$$=$1;}
                    |additive_expression '+' multiplicative_expression
                      {$$=base_of(create_binaryexpression('+',$1,$3));}
                    |additive_expression '-' multiplicative_expression
                      {$$=base_of(create_binaryexpression('-',$1,$3));}
                    ;

multiplicative_expression: cast_expression
                            {$$=$1;}
                          |multiplicative_expression '*' cast_expression
                            {$$=base_of(create_binaryexpression('*',$1,$3));}
                          |multiplicative_expression '/' cast_expression
                            {$$=base_of(create_binaryexpression('/',$1,$3));}
                          |multiplicative_expression '%' cast_expression
                            {$$=base_of(create_binaryexpression('%',$1,$3));}
                          ;

compound_statement: left_brace '}'
                    {$$=base_of(create_compoundstmt($1->coord,NULL,NULL));}
                   |left_brace statement_list '}'
                    {$$=base_of(create_compoundstmt($1->coord,NULL,$2));}
                   |left_brace declaration_list '}'
                    {$$=base_of(create_compoundstmt($1->coord,$2,NULL));}
                   |left_brace declaration_list statement_list '}'
                    {$$=base_of(create_compoundstmt($1->coord,$2,$3));}
                   ;

left_brace: '{' {$$=base_of(create_atom('{', tval, tcoord));}
        ;

statement_list: statement
                 {$$=$1;}
               |statement_list statement
                 {$$=append_astnode($1,$2);}
               ;

statement: labeled_statement
            {$$=$1;}
          |compound_statement
            {$$=$1;}
          |expression_statement
            {$$=$1;}
          |selection_statement
            {$$=$1;}
          |iteration_statement
            {$$=$1;}
          |jump_statement
            {$$=$1;}
          ;

labeled_statement: identifier ':' statement
                    {$$=base_of(create_labelstmt(IDLABEL,$1->coord,$1,$3));}
                  |case_keyword constant_expression ':' statement
                    {$$=base_of(create_labelstmt(CASELABEL,$1->coord,$2,$4));}
                  |default_keyword ':' statement
                    {$$=base_of(create_labelstmt(DEFAULTLABEL,$1->coord,NULL,$3));}
                  ;

default_keyword: DEFAULT
               {$$=base_of(create_atom(DEFAULT,tval,tcoord));}
              ;

case_keyword: CASE
            {$$=base_of(create_atom(CASE,tval,tcoord));}
           ;

expression_statement: semicolon 
                       {$$=base_of(create_exprstmt($1->coord,NULL));}
                     |expression semicolon
                       {$$=base_of(create_exprstmt($1->coord,$1));}
                     ;

semicolon: ';' {$$=base_of(create_atom(';',tval,tcoord));}
          ;

if_keyword: IF {$$=base_of(create_atom(IF,tval,tcoord));}
           ;
else_keyword: ELSE {$$=base_of(create_atom(ELSE,tval,tcoord));}
             ;
switch_keyword: SWITCH {$$=base_of(create_atom(SWITCH,tval,tcoord));}
               ;

selection_statement: if_keyword left_paren expression ')' statement %prec IFX
                      {$$=base_of(create_selstmt(IFSTMT,$1->coord,$3,$5,NULL));}
                    |if_keyword left_paren expression ')' statement else_keyword statement
                      {$$=base_of(create_selstmt(IFELSESTMT,$1->coord,$3,$5,$7));}
                    |switch_keyword left_paren expression ')' statement
                      {$$=base_of(create_selstmt(SWITCHSTMT,$1->coord,$3,$5,NULL));}
                    ;

iteration_statement: while_keyword left_paren expression ')' statement
                      {$$=base_of(create_iterationstmt(WHILESTMT,$1->coord,$3,$5,NULL,NULL));}
                    |do_keyword statement while_keyword left_paren expression ')' semicolon
                      {$$=base_of(create_iterationstmt(DOSTMT,$1->coord,$5,$2,NULL,NULL));}
                    |for_keyword left_paren expression_statement expression_statement ')' statement
                      {$$=base_of(create_iterationstmt(FORSTMT,$1->coord,NULL,$6,$3,$4));}
                    |for_keyword left_paren expression_statement expression_statement expression ')' statement
                      {$$=base_of(create_iterationstmt(FORSTMT,$1->coord,$5,$7,$3,$4));}
                    ;

while_keyword: WHILE {$$=base_of(create_atom(WHILE,tval,tcoord));}
              ;

do_keyword: DO {$$=base_of(create_atom(DO,tval,tcoord));}
           ;

for_keyword: FOR {$$=base_of(create_atom(FOR,tval,tcoord));}
            ;

goto_keyword: GOTO {$$=base_of(create_atom(GOTO,tval,tcoord));}
             ;

continue_keyword: CONTINUE {$$=base_of(create_atom(CONTINUE,tval,tcoord));}
                 ;

break_keyword: BREAK {$$=base_of(create_atom(BREAK,tval,tcoord));}
              ;

return_keyword: RETURN {$$=base_of(create_atom(RETURN,tval,tcoord));}
               ;

jump_statement: goto_keyword identifier semicolon
                 {$$=base_of(create_jumpstmt(GOTOSTMT,$1->coord,$2));}
               |continue_keyword semicolon
                 {$$=base_of(create_jumpstmt(CONTINUESTMT,$1->coord,NULL));}
               |break_keyword semicolon
                 {$$=base_of(create_jumpstmt(BREAKSTMT,$1->coord,NULL));}
               |return_keyword semicolon
                 {$$=base_of(create_jumpstmt(RETURNSTMT,$1->coord,NULL));}
               |return_keyword expression semicolon
                 {$$=base_of(create_jumpstmt(RETURNSTMT,$1->coord,$2));}
               ;

%%

static void yyerror(char *s)
{
  fatal(&tcoord,"syntax error while building abstract syntax tree");
}
