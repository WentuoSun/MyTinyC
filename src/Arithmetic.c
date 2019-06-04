#include "Syntactic.h"

//算数表达式计算模块
int Parse_E() {
    int value_1 = Parse_TE();
    int value_2 = Parse_E1(value_1);
    return value_2;
}
int Parse_TE() {
    int value_1 = Parse_F();
    int value_2 = Parse_TE1(value_1);
    return value_2;
}
int Parse_E1(int value){
    if(Cnode->type == Plus){
        match(Plus);
        int value_1 = Parse_TE(Cnode);
        int tmpval = value + value_1;
        return Parse_E1(tmpval);
    } else if (Cnode->type == Less) {
        match(Less);
        int value_2 = Parse_TE(Cnode);
        int tmpval = value - value_2;
        return Parse_E1(tmpval);
    } else {
        return value;
    }
}
int Parse_TE1(int value) {
    if(Cnode->type == Multi){
        match( Multi);
        int value_1 = Parse_TE(Cnode);
        int tmpval = value * value_1;
        return Parse_TE1(tmpval);
    } else if (Cnode->type == Except) {
        match(Except);
        int value_2 = Parse_TE(Cnode);
        int tmpval = (int)(value / value_2);
        return Parse_TE1(tmpval);
    } else {
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
        int value = LookupId().int_val;
        match(ID);
        return value ;
    } else if (Cnode->type == const_int){
        int tmpval = Cnode->Value.int_val;
        match(const_int);
        return tmpval;
    } else if (Cnode-> type == Parent_l) {
        match( Parent_l);
        LexNode *start = Cnode;
        bool tmpbool = IsLogical(start);
        if(tmpbool) {
            int bvalue = Parse_B();
            match(Parent_r);
            return bvalue?1:0;
        }else {
            int value = Parse_E(Cnode);
            match(Parent_r);
            return value ;
        }
    } else {
        return 0;
    }
}
void Parse_main(){
    match(Main);
    match(Parent_l);
    match(Parent_r);
    match(Braces_l);
    Parse_S();
    match(Braces_r);
}