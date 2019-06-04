#include "Syntax.h"

//算数表达式计算模块
int Parse_E() {
    #ifdef SyntaxAnalysis 
    printf("E -> TE E1\n");
    #endif
    int value_1 = Parse_TE();
    int value_2 = Parse_E1(value_1);
    return value_2;
}
int Parse_TE() {
    #ifdef SyntaxAnalysis 
    printf("TE -> F TE1\n");
    #endif
    int value_1 = Parse_F();
    int value_2 = Parse_TE1(value_1);
    return value_2;
}
int Parse_E1(int value){
    if(Cnode->type == Plus){
        #ifdef SyntaxAnalysis 
        printf("E1 -> +TE E1\n");
        #endif
        match(Plus);
        int value_1 = Parse_TE(Cnode);
        int tmpval = value + value_1;
        return Parse_E1(tmpval);
    } else if (Cnode->type == Less) {
        #ifdef SyntaxAnalysis 
        printf("E1 -> - TE E1\n");
        #endif
        match(Less);
        int value_2 = Parse_TE(Cnode);
        int tmpval = value - value_2;
        return Parse_E1(tmpval);
    } else {
        #ifdef SyntaxAnalysis 
        printf("E1 -> ε\n");
        #endif
        return value;
    }
}
int Parse_TE1(int value) {
    if(Cnode->type == Multi){
        #ifdef SyntaxAnalysis 
        printf("TE1 -> *TE TE1\n");
        #endif
        match( Multi);
        int value_1 = Parse_TE(Cnode);
        int tmpval = value * value_1;
        return Parse_TE1(tmpval);
    } else if (Cnode->type == Except) {
        #ifdef SyntaxAnalysis 
        printf("TE1 -> / TE TE1\n");
        #endif
        match(Except);
        int value_2 = Parse_TE(Cnode);
        int tmpval = (int)(value / value_2);
        return Parse_TE1(tmpval);
    } else {
        #ifdef SyntaxAnalysis 
        printf("TE1 -> ε\n");
        #endif
        return value ;
    }
}
bool IsLogical(LexNode *s){
    while(s->type != Parent_r){
        if(s->type >= GT && s->type <= NOT && s->type != AS) {
            return true;
        }
        s = s->next;
    }
    return false;
}
int Parse_F() {
    if(Cnode->type == ID) {
        #ifdef SyntaxAnalysis 
        printf("F -> id\n");
        #endif
        int value = LookupId().int_val;
        match(ID);
        return value ;
    } else if (Cnode->type == const_int){
        #ifdef SyntaxAnalysis 
        printf("F -> num\n");
        #endif
        int tmpval = Cnode->Value.int_val;
        match(const_int);
        return tmpval;
    } else if (Cnode-> type == Parent_l) {
        match( Parent_l);
        LexNode *start = Cnode;
        bool tmpbool = IsLogical(start);
        if(tmpbool) {
            #ifdef SyntaxAnalysis 
            printf("F -> (B)\n");
            #endif
            int bvalue = Parse_B();
            match(Parent_r);
            return bvalue?1:0;
        }else {
            #ifdef SyntaxAnalysis 
            printf("F -> (E)\n");
            #endif
            int value = Parse_E(Cnode);
            match(Parent_r);
            return value ;
        }
    } else {
        #ifdef SyntaxAnalysis 
        printf("F -> ε\n");
        #endif
        return 0;
    }
}
