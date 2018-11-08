#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "symbol_table.h"

const int TRUE = 1;
static int REG_NUM = 1;

ASTNode* CreateNumNode(int num)
{
        ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
        node->type = ASTNODE_NUM;
        node->num = num;
        node->left = NULL;
        node->right = NULL;
        return node;
}

ASTNode* CreateIdentNode(char* name)
{
    if (FindVariable(name) == TRUE)
        no_dec_error(name);

    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_IDENT;
    node->name = name;
    node->num = GetNodeValue(name);
    node->left = NULL;
    node->right = NULL;
    return node;
}

ASTNode* CreateStatementListNode(ASTNode* st, ASTNode* stList)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_STMTLIST;
    node->left = st;
    node->right = stList;
    return node;
}

ASTNode* AddNode(ASTNode* left, ASTNode* right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ARITH_OP;
    node->op = ADD_OP;
    node->num = left->num + right->num;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* SubNode(ASTNode* left, ASTNode* right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ARITH_OP;
    node->op = SUB_OP;
    node->num = left->num - right->num;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* MultNode(ASTNode* left, ASTNode* right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ARITH_OP;
    node->op = MULT_OP;
    node->num = left->num * right->num;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* DivNode(ASTNode* left, ASTNode* right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ARITH_OP;
    node->op = DIV_OP;
    if(right->num == 0)
        node->num = 0;
    else
        node->num = (int)(left->num / right->num);
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* AssignmentNode(ASTNode* ident, ASTNode* expr)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ASSIGN;
    node->num = expr->num;
    node->left = ident;
    node->right = expr;
    SetValue(ident->name, expr->num);
    node->rn = GetNodeReg(ident->name);
    return node;
}

ASTNode* CompNode(int op, ASTNode* expr1, ASTNode* expr2)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));

    switch(op)//Defined in the parser
    {
        case 1: // >
            node->type = ASTNODE_COMPARE;
            node->op = GREAT_COMP;
            node->left = expr1;
            node->right = expr2;
            break;
        case 2:// <
            node->type = ASTNODE_COMPARE;
            node->op = LESS_COMP;
            node->left = expr1;
            node->right = expr2;
            break;
        case 3: // >=
            node->type = ASTNODE_COMPARE;
            node->op = GREAT_EQ_COMP;
            node->left = expr1;
            node->right = expr2;
            break;
        case 4:// <=
            node->type = ASTNODE_COMPARE;
            node->op = LESS_EQ_COMP;
            node->left = expr1;
            node->right = expr2;
            break;
        case 5:// ==
            node->type = ASTNODE_COMPARE;
            node->op = EQUAL_COMP;
            node->left = expr1;
            node->right = expr2;
            break;
        case 6:// !=
            node->type = ASTNODE_COMPARE;
            node->op = NOT_EQ_COMP;
            node->left = expr1;
            node->right = expr2;
            break;
        default:
            printf("Error: unexpected action occured in comparison");
            exit(0);
    }
    return node;
}

ASTNode* AndNode(ASTNode* expr1, ASTNode* expr2)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_LOGIC_OP;
    node->op = AND_OP;
    //node->num = (expr1->num) && (expr2->num);
    node->left = expr1;
    node->right = expr2;
    return node;
}

ASTNode* OrNode(ASTNode* expr1, ASTNode* expr2)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_LOGIC_OP;
    node->op = OR_OP;
    //node->num = (expr1->num) || (expr2->num);
    node->left = expr1;
    node->right = expr2;
    return node;
}

ASTNode* IfNode(ASTNode* condition, ASTNode* stList)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_IF;
    node->left = condition;
    node->right = stList;
    return node;
}

ASTNode* IfElseNode(ASTNode* condition, ASTNode* stList1, ASTNode* stList2)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    ASTNode* stmt = (ASTNode*)malloc(sizeof(ASTNode));

    node->type = ASTNODE_IF;
    node->left = condition;
    node->right = stmt;
    node->right->type = ASTNODE_STMTLIST;

    stmt->left = stList1;
    stmt->left->type = ASTNODE_IFELSE;

    stmt->right = stList2;

    return node;
}

ASTNode* WhileNode(ASTNode* condition, ASTNode* stList)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_WHILE;
    node->left = condition;
    node->right = stList;
    return node;
}

// Commented out in this assignment
/*void GenerateILOC(ASTNode* node);
{

}*/
