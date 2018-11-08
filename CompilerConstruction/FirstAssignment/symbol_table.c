#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol_table.h"

void AddDeclaration(char* name)
{

    SymbolTable* temp = (SymbolTable*) malloc(sizeof (SymbolTable));
    temp->node.name = name;
    if (head == NULL)
    {
        temp->node.offset = 0;
        head = temp;
    }else{
        if(FindVariable(name) == 0)
            multiple_dec_error(name);

        temp->node.offset = head->node.offset + 4;
        temp->next = head;
        head = temp;
    }
}

int FindVariable(char* name){
    SymbolTable *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->node.name, name) == 0)
            return 0;

        temp = temp->next;
    }
    return 1;
}

int GetNodeValue(char* name){
    SymbolTable *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->node.name, name) == 0)
            return temp->node.value;

        temp = temp->next;
    }
}

int GetNodeReg(char* name){
    SymbolTable* temp = head;
    while(temp != NULL)
    {
        if (strcmp(temp->node.name, name) == 0)
            return temp->node.regnum;

        temp = temp->next;
    }
}

int GetOffset(char* name){
    SymbolTable* temp = head;
    while(temp != NULL)
    {
        if (strcmp(temp->node.name, name) == 0)
            return temp->node.offset;

        temp = temp->next;
    }
}

void SetValue(char* name, int value){
    SymbolTable* temp = head;
    while(temp != NULL)
    {
        if (strcmp(temp->node.name, name) == 0)
        {
            temp->node.value = value;
            return;
        }

        temp = temp->next;
    }
}

void SetReg(char* name, int rn){
    SymbolTable* temp = head;
    while(temp != NULL)
    {
        if (strcmp(temp->node.name, name) == 0)
        {
            temp->node.regnum = rn;
            return;
        }

        temp = temp->next;
    }
}
