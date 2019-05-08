#include "Lexical.h"

char NameTable[][25] = {
"ID", "Int", "Char",
"If", "Else", "While", "Continue", "Break", "True", "False", "Main", "Show",
"const_int", "const_char", 
"digit",  "letter",  "Relational_Operator",
"Plus", "Less", "Multi", "Except",
"Braces_l", "Braces_r", "Parent_l", "Parent_r", "Semi", "Comma",
"GT", "LT", "GE", "LE", "NE", "AS", "EQ", "AND", "OR", "NOT",
};

 int Classification(){ //第一步分类，分为数字，字母，关系运算符，各种符号
    if (*token > '0' && *token < '9') {
        return digit;
    } else if ( ( *token >= 'a' && *token <= 'z') || (*token >= 'A' && *token <= 'Z') || *token == '_' ) {
        return letter;
    } else if ( *token == '>' || *token == '<' || *token == '=' || *token == '|' || *token == '!' || *token == '&') {
        return Relational_Operator;
    } else if ( token[0] == '\'' && token[2] == '\'' ) {
        return const_char;
    }
    switch (*token) {
        case '+' : { return Plus;  }
        case '-' : { return Less;   }
        case '*' : { return Multi;   }
        case '/' : { return Except;   }
        case '{' : { return Braces_l;   }
        case '}' : { return Braces_r;   }
        case '(' : { return Parent_l;   }
        case ')' : { return Parent_r;   }
        case ';' : { return Semi;     }
        case ',' : { return Comma;  }
        default  : { next(); return -2;  }
    }
}

LexNode* Lexical() {
    LexLink = (LexNode*)malloc(sizeof(LexNode)); //建立并初始化空头指针，Head指向该指针，
    LexLink -> next = NULL;
    Head = LexLink;
    Head -> front = NULL;
    Head -> type = -1;
    while (*token != '\0') {
        while (*token == ' ' || *token == '\n') {
            next();
            continue;                          
        }
        if (*token == '\0' ) { break;}
        Rawtype = Classification();
        switch (Rawtype) {
            case -2:     {printf("can not analyse this symbol :%c \n" , *token); return Head;}
            case const_char:    {CharAnalyse(); break;}
            case digit:   {DigitAnalyse(); break;}
            case letter:   {LetterAnalyse(); break;}
            case Relational_Operator:   {Relational_OperatorAnalyse(); break;}
            case Plus: case Less: case Multi: case Except: case Braces_l: case Braces_r: case Parent_l: case Parent_r: case Semi: case Comma: 
                        {SymbolAnalyse(); break;}
        }
    }
    return Head;
}

void CharAnalyse() {
    next();
    LexLink -> next = (LexNode *)malloc( sizeof (LexNode) ) ;
    TempPointer = LexLink;
    LexLink = LexLink -> next;
    LexLink -> front = TempPointer;
    LexLink -> type = const_char;
    LexLink -> Value.char_val = *token;
    LexLink -> next = NULL;
    next();
    next();
}

void DigitAnalyse() {
    char *tempnum = (char*)malloc(sizeof(char)*20) ;
    int i = 0;
    int num;
    while (Rawtype == digit) { 
        tempnum[i++] = *token;
        next();
        Rawtype = Classification();
    }
    tempnum[i] = '\0';
    num = atoi(tempnum);
    LexLink -> next = (LexNode *)malloc( sizeof (LexNode) ) ;
    TempPointer = LexLink;
    LexLink = LexLink -> next;
    LexLink -> front = TempPointer;
    LexLink -> type = const_int;
    LexLink -> Value.int_val = num;
    LexLink -> next = NULL;
    free(tempnum);
}

void Relational_OperatorAnalyse(){
    int index = 0;
    int temptype;
    if(token[index] == '>') {
        if(token[ index+1 ] == '=') {
            temptype = GE;
            next();
        } else {
            temptype = GT;
        }
    } else if ( token[index] == '<') {
        if(token[ index+1 ] == '=') {
            temptype = LE;
            next();
        } else { 
            temptype = LT;
        }
    } else if ( token[index] == '=') {
        if(token[ index+1 ] == '=' ) {
            temptype = EQ;
            next();
        } else {
            temptype = AS;
        }
    } else if( token[index] == '!' ) {
        if (token[ index+1 ] == '=') {
            temptype = NE;
            next();
        } else {
            temptype = NOT;
        }
    } else if( token[index] == '&' && token[index+1] == '&' ) {
        temptype = AND;
        next();
    } else if (token[index] == '|' && token[index+1] == '|' ) {
        temptype = OR;
        next();
    } 
    LexLink -> next = (LexNode*)malloc( sizeof(LexNode) );
    TempPointer = LexLink;
    LexLink = LexLink -> next;
    LexLink -> front = TempPointer;
    LexLink -> type = temptype;
    LexLink -> next = NULL;
    next();
}

void LetterAnalyse() {
    char *tempstr = (char*)malloc(sizeof(char) * 100);
    int temptype;
    int index = 0 ;
    while (Rawtype == letter ) {
        tempstr[index++] = *token;
        next();
        Rawtype = Classification();
    }
    tempstr[index] = '\0';
    if (strcmp(tempstr, "if") == 0) {
        temptype = If;
    } else if ( strcmp(tempstr, "else") == 0 ) {
        temptype = Else;
    } else if ( strcmp(tempstr, "while") == 0 ) {
        temptype = While;
    } else if ( strcmp(tempstr, "continue") == 0 ) {
        temptype = Continue;
    } else if ( strcmp(tempstr, "break") == 0 ) {
        temptype = Break;
    } else if ( strcmp(tempstr, "int") == 0 ) {
        temptype = Int;
    } else if ( strcmp(tempstr, "char") == 0 ) {
        temptype = Char;
    } else if ( strcmp(tempstr, "true") == 0 ) {
        temptype = True;
    } else if ( strcmp(tempstr, "false") == 0 ) {
        temptype = False;
    } else if ( strcmp(tempstr, "main" ) == 0 ) {
        temptype = Main;
    } else if ( strcmp(tempstr, "show" ) == 0 ) {
        temptype = Show;
    } else {
        temptype = ID; 
    }
    
    LexLink -> next = (LexNode*)malloc( sizeof(LexNode) ) ;
    TempPointer = LexLink;
    LexLink = LexLink -> next;
    LexLink -> front = TempPointer;
    LexLink -> type = temptype;
    LexLink -> next = NULL;
    if ( temptype == ID ) {
        LexLink -> Value.name = (char*) malloc( sizeof(char) * 20);
        strcpy(LexLink -> Value.name, tempstr) ;
    }
    free(tempstr);
}

void SymbolAnalyse() {
    LexLink -> next = (LexNode*)malloc(sizeof(LexNode));
    TempPointer = LexLink;
    LexLink = LexLink -> next;
    LexLink -> front = TempPointer;
    LexLink -> type = Rawtype;
    LexLink -> next = NULL;
    next();
}

void PrintAllNode() {
    LexNode * head = Head;
    while( head != NULL) {
        switch ( head->type ){
        case -1 : { break; }
        case ID : { printf("ID : %s\n", head -> Value.name); break; } 
        case const_char : { printf("const_char : %c\n", head -> Value.char_val); break; }
        case const_int : { printf("const_int : %d\n", head -> Value.int_val); break; }  
        default: { printf("%s\n",NameTable[ (int)head->type ] );  }
        }
        head = head -> next;
    }
}