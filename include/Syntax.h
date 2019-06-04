//语法分析头文件
#ifndef _Syntactic_H

#define _Syntactic_H


#include "Lexical.h"


//id存储节点
typedef struct idNode{
    char idname[20];
    int type;
    Data Value;
    struct idNode *next;
}IdNode ;

extern char NameTable[][25];
//全局变量
LexNode *Cnode ;
LexNode *EndNode ;
LexNode *ConditionNode ;
bool IsBreak ;
bool IsContinue ;
IdNode *IdTable ;

//语法分析函数声明
LexNode* NextNode(LexNode *n) ;
LexNode* PrevNode(LexNode *n) ;
void match (int type) ;
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
int IdType(char * idname);
void Parse_A();


#endif