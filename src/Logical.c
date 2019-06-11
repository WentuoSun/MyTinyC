#include "Syntax.h"

//逻辑表达式计算模块
bool Parse_B(){
    #ifdef SyntaxAnalysisDetail 
    printf("B -> TB B1\n");
    #endif
    bool bvalue_1 = Parse_TB();
    bool bvalue_2 = Parse_B1(bvalue_1);
    return bvalue_2;
}
bool Parse_TB(){
    #ifdef SyntaxAnalysisDetail 
    printf("TB -> FB TB1\n");
    #endif
    bool bavlue_1 = Parse_FB();
    bool bvalue_2 = Parse_TB1(bavlue_1);
    return bvalue_2;
}
bool Parse_B1(bool value) {
    if (Cnode->type == OR) {
        #ifdef SyntaxAnalysisDetail 
        printf("B1 -> || TB B1\n");
        #endif
        match(OR);
        bool bvalue_1 = Parse_TB();
        bool bvalue_2 = Parse_B1(bvalue_1);
        return value || bvalue_2;
    } else {
        #ifdef SyntaxAnalysisDetail 
        printf("B1 -> null\n");
        #endif
        return value;
    }
}
bool Parse_TB1(bool value) {
    if (Cnode->type == AND) {
        #ifdef SyntaxAnalysisDetail 
        printf("TB1 -> && FB TB1\n");
        #endif
        match(AND);
        bool bvalue_1 = Parse_FB();
        bool bvalue_2 = Parse_TB1(bvalue_1);
        return value && bvalue_2;
    } else {
        #ifdef SyntaxAnalysisDetail 
        printf("TB1 -> null\n");
        #endif
        #ifdef SyntaxAnalysisDetail 
        printf("null\n");
        #endif
        return value;
    }
}
bool Parse_FB() {
    if(Cnode->type == NOT) {
        #ifdef SyntaxAnalysisDetail 
        printf("FB -> !B\n");
        #endif
        match(NOT);
        bool bvalue = Parse_B();
        return !bvalue;
    } else if(Cnode ->type == True) {
        #ifdef SyntaxAnalysisDetail 
        printf("FB -> ture\n");
        #endif
        match(True);
        return true;
    } else if(Cnode ->type == False) {
        #ifdef SyntaxAnalysisDetail 
        printf("FB -> false\n");
        #endif
        match(False);
        return false;
    } else {
        int value_1 = Parse_E();
        if(Cnode ->type == GT) {
            #ifdef SyntaxAnalysisDetail 
            printf("FB -> E > E\n");
            #endif
            match(GT);
            int value_2 = Parse_E();
            return value_1>value_2?true:false;
        } else if(Cnode->type == LT) {
            #ifdef SyntaxAnalysisDetail 
            printf("FB -> E < E\n");
            #endif
            match(LT);
            int value_2 = Parse_E();
            return value_1<value_2?true:false;
        } else if(Cnode->type == GE) {
            #ifdef SyntaxAnalysisDetail 
            printf("Fb -> E >= E\n");
            #endif
            match(GE);
            int value_2 = Parse_E();
            return value_1>=value_2?true:false;
        } else if(Cnode->type == LE) {
            #ifdef SyntaxAnalysisDetail 
            printf("FB -> E <= E\n");
            #endif
            match(LE);
            int value_2 = Parse_E();
            return value_1<=value_2?true:false;
        } else if(Cnode->type == NE) {
            #ifdef SyntaxAnalysisDetail 
            printf("FB -> E != E\n");
            #endif
            match(NE);
            int value_2 = Parse_E();
            return value_1!=value_2?true:false;
        } else if(Cnode->type == EQ) {
            #ifdef SyntaxAnalysisDetail 
            printf("FB -> E == E\n");
            #endif
            match(EQ);
            int value_2 = Parse_E();
            return value_1==value_2?true:false;
        } else {
            #ifdef SyntaxAnalysisDetail 
            printf("FB -> E\n");
            #endif
            return value_1==0?false:true;
        }
    }
}
