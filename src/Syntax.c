#include "Syntax.h"
//语法分析主文件

//全局变量初始化
LexNode *Cnode = NULL;
LexNode *EndNode = NULL;
LexNode *ConditionNode = NULL;
bool IsBreak = false;
bool IsContinue = false;
IdNode *IdTable = NULL;

//基本函数实现

//返回下一个词法节点
LexNode* NextNode(LexNode *n){
    if (n->next != NULL){
        return n->next;
    } else {
        printf("End of the LexNode\n");
        return NULL;
    }
}
//返回上一个词法节点
LexNode* PrevNode(LexNode *n){
    if (n->Prev != NULL) {
        return n->Prev;
    } else {
        printf("Previous of this node is NULL\n");
        return NULL;
    }
}
//匹配函数
void match (int type) {
    if(Cnode->type != type) {
        printf("expacted: %s, got: %s\n",NameTable[type], NameTable[Cnode->type]);
    }
    Cnode = NextNode(Cnode);
}

//返回与当前左大括号相匹配的右大括号
LexNode* FindMatchBraces(){
    LexNode *tmp  = Cnode;
    int counter = 1;
    while (tmp != NULL && counter != 0) {
        if(tmp->type == Braces_l)
            counter ++;
        if(tmp->type == Braces_r)
            counter --;
        tmp = tmp ->next;
    }
    return tmp->Prev;
}
//基本语法分析函数
void Parse_main(){
    #ifdef SyntaxAnalysis 
    printf("\nFUNC -> main() {S} \n");
    #endif
    match(Main);
    match(Parent_l);
    match(Parent_r);
    match(Braces_l);
    Parse_S();
    match(Braces_r);
}
void Parse_S(){
    if(Cnode->type == Show) {
        #ifdef SyntaxAnalysis 
        printf("S -> Show(E);S\n");
        #endif    
        match( Show);
        match(Parent_l);
        if (Cnode->type == const_int) {
            int value = Parse_E();
            printf("\n%d\n",value);
        }else if (Cnode->type == const_char ) {
            printf("\n%c\n", Cnode->Value.char_val);
            match(const_char);
        } else {
            if (IdType(Cnode->Value.name) == Int){
                int value = Parse_E();
                printf("\n%d\n",value);
            }else if(IdType(Cnode->Value.name) == Char) {
                char value = Parse_G();
                printf("\n%c\n", value);
                }
        }
        match(Parent_r);
        match(Semi);
        Parse_S();
    }else if (Cnode->type == Int || Cnode->type == Char) {
        #ifdef SyntaxAnalysis 
        printf("S -> D S \n");
        #endif
        Parse_D();
        Parse_S();
    } else if (Cnode->type ==ID) {
        #ifdef SyntaxAnalysis 
        printf("S -> A S\n");
        #endif
        Parse_A();
        Parse_S();
    } else if (Cnode->type == If) {
        #ifdef SyntaxAnalysis 
        printf("S -> if(B) {S} [else {S}] S\n");
        #endif
        match(If);
        match(Parent_l);
        bool bvalue = Parse_B();
        match(Parent_r);
        match(Braces_l);
        LexNode *MatchBraces = FindMatchBraces();
        if (bvalue) {
            Parse_S();
        } else {
            Cnode = MatchBraces;
        }
        if(IsBreak) {
            Cnode = EndNode;
            return ;
        } else if(IsContinue){
            Cnode = ConditionNode;
            IsContinue = false;
            return;
        }
        match(Braces_r);
        if (Cnode->type == Else) {
                match(Else);
                match(Braces_l);
                MatchBraces = FindMatchBraces();
                if(!bvalue) {
                    Parse_S();
                } else {
                    Cnode = MatchBraces;
                    match(Braces_r);
                }
                if(IsBreak) {
                    Cnode = EndNode;
                    return ;
                } else if(IsContinue){
                    Cnode = ConditionNode;
                    return;
                }        
        }
        Parse_S();
    } else if (Cnode->type == While ){
        #ifdef SyntaxAnalysis 
        printf("S -> while(B) {S} S\n");
        #endif
        match(While);
        match(Parent_l);
        ConditionNode = Cnode;
        bool bvalue = Parse_B();
        match(Parent_r);
        match(Braces_l);
        EndNode = FindMatchBraces();
        while(bvalue){
            Parse_S();
            Cnode = ConditionNode;
            bvalue = Parse_B();
            match(Parent_r);
            match(Braces_l);
        }
        Cnode = EndNode;
        match(Braces_r);
        Parse_S();
    } else if(Cnode->type == Continue) {
        match(Continue);
        match(Semi);
        IsContinue =true;
        return ;
    } else if(Cnode->type == Break) {
        match(Break);
        match(Semi);
        IsBreak = true;
    }
    else {
        return ;
    }
}

int Syntactic(LexNode *head) {
    Cnode = head->next; 
    IdTable = (IdNode*)malloc(sizeof(IdNode));
    IdTable->next = NULL;
    Parse_main(Cnode);
    return 0;
}
