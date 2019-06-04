#ifndef _Syntactic_H

#define _Syntactic_H


#include "Lexical.h"
LexNode* NextNode(LexNode *n) ;
LexNode* PrevNode(LexNode *n) ;
void match (int type) ;

typedef struct idNode{
    char idname[20];
    int type;
    Data Value;
    struct idNode *next;
}IdNode ;

LexNode *Cnode ;
LexNode *EndNode ;
LexNode *ConditionNode ;
bool IsBreak ;
bool IsContinue ;
IdNode *IdTable ;

void Parse_main();
void Parse_S();
int Parse_E() ;
int Parse_TE();
int Parse_E1(int value);
int Parse_TE1(int value);
int Parse_F();
int Syntactic(LexNode *head);
void AddId(int type);
void AssignId(char* idname,Data value);
Data LookupId();
int Parse_T() ;
void  Parse_L(int type) ;
void Parse_D();
char Parse_G();
LexNode* FindMatchBraces();
bool Parse_B();
bool Parse_TB();
bool Parse_B1(bool value);
bool Parse_TB1(bool value);
bool Parse_FB();


#endif