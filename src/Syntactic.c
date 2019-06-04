#include "Syntactic.h"


void NextNode(){
    if (Cnode->next != NULL){
        Cnode = Cnode ->next;
    } else {
        printf("End of the LexNode\n");
    }
}
void PrevNode(){
    if (Cnode->Prev != NULL) {
        Cnode = Cnode ->Prev;
    } else {
        printf("Previous of this node is NULL\n");
    }
}
void match (int type){
    if(Cnode->type != type) {
        printf("expacted: %d, got: %d\n",type, Cnode->type);
    }
    NextNode(Cnode);
}
void Parse_main(){
    match(Main);
    match(Parent_l);
    match(Parent_r);
    match(Braces_l);
    Parse_S();
    match(Braces_r);
}
void Parse_S(){
    if(Cnode->type == Show) {
        match( Show);
        match(Parent_l);
        int value = Parse_E();
        printf("\n%d\n",value);
        match(Parent_r);
        match(Semi);
        Parse_S();
    } else {
        return ;
    }
}

int Syntactic(LexNode *head) {
    Cnode = head->next; 
    Parse_main(Cnode);
    return 0;
}
