#ifndef _Lexical_H_

#define _Lexical_H_

#include "ReadFile.h"


enum { //id 和关键字
    ID = 0, Int, Char, 
    If,  Else, While, Continue, Break, True, False, Main, Show,
    const_int, const_char,
    digit,      //数字，具体值为多少后期计算 
    letter,     //字母，具体是id，关键字，后期确定  //15
    Relational_Operator,      // > < = ! & | 关系运算符，具体是什么后期判断
    Plus,       // +
    Less,       // -
    Multi,      // *
    Except,     // /    20
    Braces_l,   // {
    Braces_r,   // }
    Parent_l,   // (
    Parent_r,   // )
    Semi,       // ;   25
    Comma,      // ,    
    GT,         // >
    LT,         // < 
    GE,         // >=
    LE,         // <=   30
    NE,         // !=
    AS,         // = 
    EQ,         // == 
    AND,        // &&
    OR,         // ||
    NOT,        // !
};


//共用体，为节点存储int，char值 或为id存储名字
typedef union data
{
    int int_val;
    char char_val;
    char *name;
}Data;

//词法分析输出链表节点定义
typedef struct Node{
    int type;   
    Data Value;
    struct Node *Prev, *next; //设置双向链表，为语法分析可能的回溯创造条件
}LexNode;

//链表指针
LexNode *LexLink, *Head, *TempPointer;

//预分析，返回Rawtype
int Classification();
//预分析给出的原始类别 包括数字，字母， 关系表达式，字符常量，各种符号。
int Rawtype;

//根据Rawtype的值进行不同分析 ，具体功能见对应.c文件
void CharAnalyse();    
void DigitAnalyse();    
void Relational_OperatorAnalyse();  
void LetterAnalyse();   
void SymbolAnalyse();   

//输出head所指链表的所有元素
void PrintAllNode(LexNode *head);    

//词法分析主函数
LexNode* Lexical();

#endif