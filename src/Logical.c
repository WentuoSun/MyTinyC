#include "Syntax.h"

//逻辑表达式计算模块
bool Parse_B(){
    #ifdef SyntaxAnalysis 
    printf("B -> TB B1\n");
    #endif
    bool bvalue_1 = Parse_TB();
    bool bvalue_2 = Parse_B1(bvalue_1);
    return bvalue_2;
}
bool Parse_TB(){
    #ifdef SyntaxAnalysis 
    printf("TB -> FB TB1\n");
    #endif
    bool bavlue_1 = Parse_FB();
    bool bvalue_2 = Parse_TB1(bavlue_1);
    return bvalue_2;
}
bool Parse_B1(bool value) {
    if (Cnode->type == OR) {
        #ifdef SyntaxAnalysis 
        printf("B1 -> || TB B1\n");
        #endif
        match(OR);
        bool bvalue_1 = Parse_TB();
        bool bvalue_2 = Parse_B1(bvalue_1);
        return value || bvalue_2;
    } else {
        #ifdef SyntaxAnalysis 
        printf("B1 -> ε\n");
        #endif
        return value;
    }
}
bool Parse_TB1(bool value) {
    if (Cnode->type == AND) {
        #ifdef SyntaxAnalysis 
        printf("TB1 -> && FB TB1\n");
        #endif
        match(AND);
        bool bvalue_1 = Parse_FB();
        bool bvalue_2 = Parse_TB1(bvalue_1);
        return value && bvalue_2;
    } else {
        #ifdef SyntaxAnalysis 
        printf("TB1 -> ε\n");
        #endif
        #ifdef SyntaxAnalysis 
        printf("ε\n");
        #endif
        return value;
    }
}
bool Parse_FB() {
    if(Cnode->type == NOT) {
        #ifdef SyntaxAnalysis 
        printf("FB -> !B\n");
        #endif
        match(NOT);
        bool bvalue = Parse_B();
        return !bvalue;
    } else if(Cnode ->type == True) {
        #ifdef SyntaxAnalysis 
        printf("FB -> ture\n");
        #endif
        match(True);
        return true;
    } else if(Cnode ->type == False) {
        #ifdef SyntaxAnalysis 
        printf("FB -> false\n");
        #endif
        match(False);
        return false;
    } else {
        int value_1 = Parse_E();
        if(Cnode ->type == GT) {
            #ifdef SyntaxAnalysis 
            printf("FB -> E > E\n");
            #endif
            match(GT);
            int value_2 = Parse_E();
            return value_1>value_2?true:false;
        } else if(Cnode->type == LT) {
            #ifdef SyntaxAnalysis 
            printf("FB -> E < E\n");
            #endif
            match(LT);
            int value_2 = Parse_E();
            return value_1<value_2?true:false;
        } else if(Cnode->type == GE) {
            #ifdef SyntaxAnalysis 
            printf("Fb -> E >= E\n");
            #endif
            match(GE);
            int value_2 = Parse_E();
            return value_1>=value_2?true:false;
        } else if(Cnode->type == LE) {
            #ifdef SyntaxAnalysis 
            printf("FB -> E <= E\n");
            #endif
            match(LE);
            int value_2 = Parse_E();
            return value_1<=value_2?true:false;
        } else if(Cnode->type == NE) {
            #ifdef SyntaxAnalysis 
            printf("FB -> E != E\n");
            #endif
            match(NE);
            int value_2 = Parse_E();
            return value_1!=value_2?true:false;
        } else if(Cnode->type == EQ) {
            #ifdef SyntaxAnalysis 
            printf("FB -> E == E\n");
            #endif
            match(EQ);
            int value_2 = Parse_E();
            return value_1==value_2?true:false;
        } else {
            #ifdef SyntaxAnalysis 
            printf("FB -> E\n");
            #endif
            return value_1==0?false:true;
        }
    }
}
