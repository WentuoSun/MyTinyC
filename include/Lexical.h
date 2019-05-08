#ifndef Lexica

#define Lexica

#include "ReadFile.h"


enum { //id 和关键字
    ID = 0,
    Int,
    Char, 
    If, 
    Else,
    While,
    Continue,
    Break,
    True,
    False,
    Main,
    Show,
    const_int,
    const_char,
    digit,      //数字，具体值为多少后期计算
    letter,     //字母，具体是id，关键字，后期确定
    Relational_Operator,      // > < = ! & | 关系运算符，具体是什么后期判断
    Plus,       // +
    Less,       // -
    Multi,      // *
    Except,     // /    
    Braces_l,   // {
    Braces_r,   // }
    Parent_l,   // (
    Parent_r,   // )
    Semi,       // ;
    Comma,      // ,    
    GT,         // >
    LT,         // < 
    GE,         // >=
    LE,         // <=   
    NE,         // !=
    AS,         // = 
    EQ,         // == 
    AND,        // &&
    OR,         // ||
    NOT,        // !
};



typedef union data
{
    int int_val;
    char char_val;
    char *name;
}Data;

typedef struct Node{
    int type;
    Data Value;
    struct Node *front, *next;
}LexNode;

LexNode *LexLink, *Head, *TempPointer;
int Rawtype;

int Classification();

LexNode* Lexical();

void CharAnalyse();
void DigitAnalyse();
void Relational_OperatorAnalyse();
void LetterAnalyse();
void SymbolAnalyse();
void PrintAllNode();

#endif