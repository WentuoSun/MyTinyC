
#include "Lexical.h"
//#include "Syntactic.h"
extern int Syntactic(LexNode *head);
int main(){
    ReadFile();
    ClearComment();
    LexNode *head1 = Lexical();
    PrintAllNode(head1);
    Syntactic(head1);
    return 0;
}
 