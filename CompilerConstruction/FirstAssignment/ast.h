#ifndef AST_H
#define AST_H

typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM, ASTNODE_IF, ASTNODE_IFELSE, ASTNODE_WHILE, ASTNODE_STMTLIST} ASTNodeType;

typedef enum{ADD_OP, SUB_OP, MULT_OP, DIV_OP, GREAT_COMP, LESS_COMP, EQUAL_COMP, NOT_EQ_COMP, GREAT_EQ_COMP, LESS_EQ_COMP, AND_OP, OR_OP} ASTOp;

typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type;
 	ASTOp op; // The actual operation (add, mult, etc)
	int num;  //Need to store the actual value for number nodes
	char *name; //Need to store the actual variable name for ident nodes
	ASTNode* left; // Left child
	ASTNode* right; // Right child

	ASTNode* next; // a pointer used to link statement nodes together in a statement list

	int rn;
};

ASTNode* CreateNumNode(int num);
ASTNode* CreateIdentNode(char* name);
ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList);
ASTNode* AddNode(ASTNode* left, ASTNode* right);
ASTNode* SubNode(ASTNode* left, ASTNode* right);
ASTNode* MultNode(ASTNode* left, ASTNode* right);
ASTNode* DivNode(ASTNode* left, ASTNode* right);
ASTNode* AssignmentNode(ASTNode* ident, ASTNode* expr);
ASTNode* CompNode(int op, ASTNode* expr1, ASTNode* expr2);
ASTNode* AndNode(ASTNode* expr1, ASTNode* expr2);
ASTNode* OrNode(ASTNode* expr1, ASTNode* expr2);
ASTNode* IfNode(ASTNode* condition, ASTNode* stList);
ASTNode* IfElseNode(ASTNode* condition, ASTNode* stList1, ASTNode* stList2);
ASTNode* WhileNode(ASTNode* consition, ASTNode* stList);

//void GenerateILOC(ASTNode* node);
#endif
