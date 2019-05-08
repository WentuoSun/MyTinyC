
#include "Lexical.h"

int main(){
    ReadFile();
    ClearAnnoation();
    LexNode *head = Lexical();
    PrintAllNode();
    //printf("%d", head->next->Value.int_val);
}
 