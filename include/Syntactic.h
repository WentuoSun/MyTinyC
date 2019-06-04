#ifndef _Syntactic_H

#define _Syntactic_H


#include "Lexical.h"
//LexNode* NextNode() ;
//LexNode* PrevNode() ;
LexNode *Cnode = NULL;
void Parse_main();
void Parse_S();
int Parse_E() ;
int Parse_TE();
int Parse_E1(int value);
int Parse_TE1(int value);
int Parse_F();
int Syntactic(LexNode *head);
#endif