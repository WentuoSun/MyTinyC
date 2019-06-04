#include "Syntactic.h"

LexNode *Cnode = NULL;
LexNode *EndNode = NULL;
LexNode *ConditionNode = NULL;
bool IsBreak = false;
bool IsContinue = false;
IdNode *IdTable = NULL;
LexNode* NextNode(LexNode *n){
    if (n->next != NULL){
        return n->next;
    } else {
        printf("End of the LexNode\n");
        return NULL;
    }
}
LexNode* PrevNode(LexNode *n){
    if (n->Prev != NULL) {
        return n->Prev;
    } else {
        printf("Previous of this node is NULL\n");
        return NULL;
    }
}
void match (int type) {
    if(Cnode->type != type) {
        printf("expacted: %d, got: %d\n",type, Cnode->type);
    }
    Cnode = NextNode(Cnode);
}


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
        match(Int);
        return Int;
    } else if(Cnode->type == Char) {
        match(Char);
        return Char;
    } else{
        printf("UnKnown type !\n");
        return 0;
    }
}
void  Parse_L(int type) {
    if (Cnode->type == Comma){
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
        return ;
    }

}
void Parse_A(){
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
        char value = LookupId().char_val;
        match(ID);
        return value;
    } else if (Cnode->type == const_char) {
        char value = Cnode->Value.char_val;
        match(const_char);
        return value ;
    } else {
        return '\0';
    }
}
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
bool Parse_B(){
    bool bvalue_1 = Parse_TB();
    bool bvalue_2 = Parse_B1(bvalue_1);
    return bvalue_2;
}
bool Parse_TB(){
    bool bavlue_1 = Parse_FB();
    bool bvalue_2 = Parse_TB1(bavlue_1);
    return bvalue_2;
}
bool Parse_B1(bool value) {
    if (Cnode->type == OR) {
        match(OR);
        bool bvalue_1 = Parse_TB();
        bool bvalue_2 = Parse_B1(bvalue_1);
        return value || bvalue_2;
    } else {
        return value;
    }
}
bool Parse_TB1(bool value) {
    if (Cnode->type == AND) {
        match(AND);
        bool bvalue_1 = Parse_FB();
        bool bvalue_2 = Parse_TB1(bvalue_1);
        return value && bvalue_2;
    } else {
        return value;
    }
}
bool Parse_FB() {
    if(Cnode->type == NOT) {
        match(NOT);
        bool bvalue = Parse_B();
        return !bvalue;
    } else if(Cnode ->type == True) {
        match(True);
        return true;
    } else if(Cnode ->type == False) {
        match(False);
        return false;
    } else {
        int value_1 = Parse_E();
        if(Cnode ->type == GT) {
            match(GT);
            int value_2 = Parse_E();
            return value_1>value_2?true:false;
        } else if(Cnode->type == LT) {
            match(LT);
            int value_2 = Parse_E();
            return value_1<value_2?true:false;
        } else if(Cnode->type == GE) {
            match(GE);
            int value_2 = Parse_E();
            return value_1>=value_2?true:false;
        } else if(Cnode->type == LE) {
            match(LE);
            int value_2 = Parse_E();
            return value_1<=value_2?true:false;
        } else if(Cnode->type == NE) {
            match(NE);
            int value_2 = Parse_E();
            return value_1!=value_2?true:false;
        } else if(Cnode->type == EQ) {
            match(EQ);
            int value_2 = Parse_E();
            return value_1==value_2?true:false;
        } else {
            return value_1==0?false:true;
        }
    }
}
void Parse_S(){
    if(Cnode->type == Show) {
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
        Parse_D();
        Parse_S();
    } else if (Cnode->type ==ID) {
        Parse_A();
        Parse_S();
    } else if (Cnode->type == If) {
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
