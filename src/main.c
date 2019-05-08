
#include "Lexical.h"

int main(){
    ReadFile();
    ClearComment();
    LexNode *head = Lexical();
    PrintAllNode(head);
    //printf("%d", head->next->Value.int_val);
}
 