%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "symbol_table.h"
	#include "ast.h"

// The parser needs to call the scanner to get the next token
	extern int yylex();

// The error function
	extern int yyerror(const char *);

// The ASTNode root
    extern ASTNode* gASTRoot;
%}

//Put any initialization code here
%initial-action
{
	head = NULL;
}

%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

//Define the types for the grammar attributes ($$, $1, $2, ...)
%union
{
	struct ASTNode* node; // Most $$ values will be ASTNodes
	int num; // Integer numbers
	char* string; // Strings for identifiers
}

//Specify the type for each token. Only needed for IDENT and NUM, because they are the only ones that have actual regexp rules
%token <string> IDENT
%token <num> NUM

//Specify the type for each non-terminal in the grammar. Here are some samples:
%type <node> Statement
%type <node> Assignment
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <node> DeclarationList
%type <node> Declaration
%type <node> StatementList
%type <node> If
%type <node> While
%type <num>  Op
%type <node> LHS
%type <node> BExpr /*Boolean Expression*/
%type <node> BTerm /*Boolean Term*/
%type <node> BFactor /*Boolean Factor*/
%type <node> Compare

%%

// Write the grammar for BabyC, and write an embedded action for each production. Here are some samples for you:

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'{gASTRoot=$6;} // Store the AST root node in gASTRoot
;

DeclarationList:    { }
				  | Declaration DeclarationList { }// Note that a DeclarationList may be empty
;

StatementList:   { $$ = NULL; } //THIS IS EPSILON!
               | Statement StatementList {$$ = CreateStatementListNode($1,$2); printf("Adding a Statement to a Statement list \n");}
;

Declaration: "int" IDENT ';' { AddDeclaration($2); printf("Processing declaration of %s\n", $2);}
;

Statement: Assignment { $$ = $1; }
		 | If { $$ = $1; }
		 | While { $$ = $1; }
;

If:   "if" '(' BExpr ')' '{' StatementList '}' { $$ = IfNode($3, $6); printf("Creating if Statement node\n");}
	| "if" '(' BExpr ')' '{' StatementList '}' "else" '{' StatementList '}' { $$ = IfElseNode($3, $6, $10); printf("Creating if-else Statement node\n");}
;

While: "while" '(' BExpr ')' '{' StatementList '}' { $$ = WhileNode($3, $6); printf("Creating while loop node\n"); }
;

BExpr:  BTerm { $$ = $1; }
	  | BExpr "||" BTerm { $$ = OrNode( $1, $3); printf("Creating OR node\n");}
;

BTerm:  BFactor { $$ = $1; }
	  | BTerm "&&" BFactor { $$ = AndNode( $1, $3); printf("Creating AND node\n");}
;

BFactor: Compare {$$ = $1; };
;

Compare: Expr Op Expr {$$ = CompNode($2, $1, $3); printf("Creating Compare node\n"); }
;

Op:   '>'  { $$ = 1; }
	| '<'  { $$ = 2; }
	| ">=" { $$ = 3; }
	| "<=" { $$ = 4; }
	| "==" { $$ = 5; }
	| "!=" { $$ = 6; }
;

Assignment: LHS '=' Expr ';' {$$ = AssignmentNode( $1, $3); printf("Creating Assignment node\n"); }
;

LHS: IDENT { $$ = CreateIdentNode($1); printf("Creating left-hand IDENT node for %s\n", $1);}
;

Expr:  Term 		 { $$ = $1; }
	 | Expr '+' Term { $$ = AddNode( $1, $3); printf("Creating Addition node\n"); }
	 | Expr '-' Term { $$ = SubNode( $1, $3); printf("Creating Subtraction node\n"); }
;

Term:  Factor 		   { $$ = $1;}
	 | Term '*' Factor { $$ = MultNode($1, $3); printf("Creating Multiplication node\n"); }
	 | Term '/' Factor { $$ = DivNode($1, $3); printf("Creating Division node\n"); }
;

Factor: IDENT 		{$$ = CreateIdentNode($1); printf("Creating IDENT node for %s\n", $1); }
	|   NUM 		{$$ = CreateNumNode($1); printf("Creating NUM node for %d\n", $1); }
	| '('Expr')'	{$$ = $2;; printf("Creating Expression node in parentheses\n"); }
;

%%
