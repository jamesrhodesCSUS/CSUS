#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct {
    char * name;
	int value;
	int regnum;
	int offset;
} Node;

typedef struct SymbolTable SymbolTable;
struct SymbolTable{
    Node node;
    SymbolTable* next;
};
SymbolTable * head;

void AddDeclaration(char* name);

int FindVariable(char* name);

int GetNodeValue(char* name);
int GetNodeReg(char* name);
int GetOffset(char* name);
void SetValue(char* ident, int value);
void SetReg(char* ident, int rn);

#endif
