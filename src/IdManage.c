#include "Syntax.h"

void AddId(int type) {
    IdNode *tmp = IdTable;
    while(tmp->next != NULL) {
        tmp = tmp->next;
    } 
    tmp->next = (IdNode*)malloc(sizeof(IdNode));
    tmp = tmp->next;
    strcpy(tmp->idname, Cnode->Value.name);
    tmp->type = type;
    tmp->next = NULL;
    return ;
}

void AssignId(char* idname,Data value) {
    IdNode *tmp = IdTable;
    while(tmp != NULL){
        if(strcmp(tmp->idname, idname)== 0) {
            if (tmp->type == Int) {
                tmp->Value.int_val = value.int_val;
                return ;
            }else {
                tmp->Value.char_val = value.char_val;
                return ;
            }
        }
        tmp = tmp->next;
    }
    printf("can not find this id %s \n",Cnode->Value.name);
}
Data LookupId() {
    IdNode *Tpointer = IdTable;
    while(Tpointer != NULL) {
        if ( strcmp(Tpointer->idname, Cnode->Value.name ) == 0){
            return Tpointer->Value;
        }
        Tpointer = Tpointer->next;
    }
    return (Data)0;
}
int IdType(char * idname) {
    IdNode *tmp = IdTable;
    while(tmp != NULL){
        if (strcmp(idname, tmp->idname) == 0){
            return tmp->type;
        }
        tmp = tmp->next;
    }
    return -2;
}
int Parse_T() {
    if (Cnode->type == Int) {
        #ifdef SyntaxAnalysisDetail 
        printf("T -> int\n");
        #endif
        match(Int);
        return Int;
    } else if(Cnode->type == Char) {
        #ifdef SyntaxAnalysisDetail 
        printf("T -> char\n");
        #endif
        match(Char);
        return Char;
    } else{
        printf("UnKnown type !\n");
        return 0;
    }
}
void  Parse_L(int type) {
    if (Cnode->type == Comma){
        #ifdef SyntaxAnalysisDetail 
        printf("L -> ,id [= E] L \n");
        #endif
        match(Comma);
        AddId(type);
        match(ID);
        if (Cnode->type == AS) {
            LexNode *idnode = PrevNode(Cnode);
            match(AS);
            int value = Parse_E();
            AssignId(idnode->Value.name,(Data)value);
        }
    } else {
        #ifdef SyntaxAnalysisDetail 
        printf("L -> null\n");
        #endif
        return ;
    }

}
void Parse_A() {
    #ifdef SyntaxAnalysisDetail 
    printf("A -> id = E \n");
    #endif
    LexNode *idnode = Cnode;
    match(ID);
    match(AS);
    int idtype = IdType(idnode->Value.name);
    if (idtype == Int){
        int value = Parse_E();
        AssignId(idnode->Value.name, (Data)value);
    } else if (idtype == Char) {
        char value = Parse_G();
        AssignId(idnode->Value.name, (Data)value);
    }
    match(Semi);
    return ;
}
void Parse_D() {
    #ifdef SyntaxAnalysisDetail 
    printf("D -> T id [ = E ] L\n");
    #endif
    int TypeofId = Parse_T();
    AddId(TypeofId);
    match(ID);
    if (Cnode->type == AS) {
        LexNode *idnode = PrevNode(Cnode);
        match(AS);
        if(TypeofId == Int){
            int value = Parse_E();
            AssignId(idnode->Value.name,(Data)value);
        } else {
            char value = Parse_G();
            AssignId(idnode->Value.name,(Data)value);
        }
    }
    Parse_L(TypeofId);
    match(Semi);
}
char Parse_G(){
    if (Cnode->type == ID){
        #ifdef SyntaxAnalysisDetail 
        printf("G -> id\n");
        #endif
        char value = LookupId().char_val;
        match(ID);
        return value;
    } else if (Cnode->type == const_char) {
        #ifdef SyntaxAnalysisDetail 
        printf("G -> char\n");
        #endif
        char value = Cnode->Value.char_val;
        match(const_char);
        return value ;
    } else {
        return '\0';
    }
}