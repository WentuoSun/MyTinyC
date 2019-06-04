
#include "Syntax.h"
int main(){
    ReadFile();
    ClearComment();
    LexNode *head1 = Lexical();
    #ifdef LexicalAnalysis
    PrintAllNode(head1);
    #endif
    #ifdef SyntaxAnalysis
    Syntactic(head1);
    #endif
    return 0;
}
 