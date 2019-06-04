#include "Lexical.h"




//枚举类型对应名称，输出所有节点时用
char NameTable[][25] = {
"ID", "Int", "Char",
"If", "Else", "While", "Continue", "Break", "True", "False", "Main", "Show",
"const_int", "const_char", 
"digit",  "letter",  "Relational_Operator",
"Plus", "Less", "Multi", "Except",
"Braces_l", "Braces_r", "Parent_l", "Parent_r", "Semi", "Comma",
"GT", "LT", "GE", "LE", "NE", "AS", "EQ", "AND", "OR", "NOT",
};
 
//预分析，将*token分为数字，字母，关系运算符，各种符号以及字符常量
 int Classification(){ 
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
        case '+' : { return Plus;   }
        case '-' : { return Less;   }
        case '*' : { return Multi;  }
        case '/' : { return Except;     }
        case '{' : { return Braces_l;   }
        case '}' : { return Braces_r;   }
        case '(' : { return Parent_l;   }
        case ')' : { return Parent_r;   }
        case ';' : { return Semi;   }
        case ',' : { return Comma;  }
        default  : { next(); return -2; }
    }
}

 //创建新节点，保存字符常量的值
void CharAnalyse() { 
    next();
    LexLink -> next = (LexNode *)malloc( sizeof (LexNode) ) ;
    TempPointer = LexLink;
    LexLink = LexLink -> next;
    LexLink -> Prev = TempPointer;
    LexLink -> type = const_char;
    LexLink -> Value.char_val = *token;
    LexLink -> next = NULL;
    next();
    next();
}

//将一串数字转为整数，其值保存在新结点中
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
    LexLink -> Prev = TempPointer;
    LexLink -> type = const_int;
    LexLink -> Value.int_val = num;
    LexLink -> next = NULL;
    free(tempnum);
}

//将 > < = ! | & 的组合进一步分析为关系表达式，新节点只保存其类型
void Relational_OperatorAnalyse(){ 
    int temptype;
    if(token[0] == '>') {
        if(token[ 1 ] == '=') { //双字符表达式必须进行两次next(),使token指针指向下一个需要分析的字符
            temptype = GE;
            next();             //在判断中执行一次next()， 程序结束时执行一次next() 下同
        } else {
            temptype = GT;
        }
    } else if ( token[0] == '<') {
        if(token[ 1 ] == '=') {
            temptype = LE;
            next();
        } else { 
            temptype = LT;
        }
    } else if ( token[0] == '=') {
        if(token[ 1 ] == '=' ) {
            temptype = EQ;
            next();
        } else {
            temptype = AS;
        }
    } else if( token[0] == '!' ) {
        if (token[ 1 ] == '=') {
            temptype = NE;
            next();
        } else {
            temptype = NOT;
        }
    } else if( token[0] == '&' && token[1] == '&' ) {
        temptype = AND;
        next();
    } else if (token[0] == '|' && token[1] == '|' ) {
        temptype = OR;
        next();
    } 
    LexLink -> next = (LexNode*)malloc( sizeof(LexNode) );
    TempPointer = LexLink;
    LexLink = LexLink -> next;
    LexLink -> Prev = TempPointer;
    LexLink -> type = temptype;
    LexLink -> next = NULL;
    next();
}

//将一串字母分析为C语言关键字或者id，若为id，则在新节点中保存其命名
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
    LexLink -> Prev = TempPointer;
    LexLink -> type = temptype;
    LexLink -> next = NULL;
    if ( temptype == ID ) {
        LexLink -> Value.name = (char*) malloc( sizeof(char) * 20);
        strcpy(LexLink -> Value.name, tempstr) ;
    }
    free(tempstr);
}

//将， ； + 等符号保存到创建的新结点中，只保存其类型
void SymbolAnalyse() {
    LexLink -> next = (LexNode*)malloc(sizeof(LexNode));
    TempPointer = LexLink;
    LexLink = LexLink -> next;
    LexLink -> Prev = TempPointer;
    LexLink -> type  = Rawtype;
    LexLink -> next  = NULL;
    next();
}

//输出head所指链表的所有元素
void PrintAllNode(LexNode* head) {
    while( head != NULL) {
        switch ( head->type ){
        case -1 :           { break; }
        case ID :           { printf("ID : %s\n", head -> Value.name); break; } 
        case const_char :   { printf("const_char : %c\n", head -> Value.char_val); break; }
        case const_int :    { printf("const_int : %d\n", head -> Value.int_val); break; }  
        default:            { printf("%s\n",NameTable[ (int)head->type ] );  }
        }
        head = head -> next;
    }
}

//词法分析主函数
LexNode* Lexical() {
    LexLink = (LexNode*)malloc(sizeof(LexNode)); //建立并初始化空头指针，Head指向该指针，
    LexLink -> next = NULL;
    Head = LexLink;
    Head -> Prev = NULL;
    Head -> type = -1;
    while (*token != '\0') {
        while (*token == ' ' || *token == '\n') { //跳过空格和换行符
            next();
            continue;                          
        }
        if (*token == '\0' ) { break;}  //若跳过空格后到达文件底部，则退出循环
        Rawtype = Classification();     //预分析
        switch (Rawtype) {  //根据预分析后Rawtype的值进行下一步分析
            case -2:                    {printf("can not analyse this symbol :%c \n" , *token); return Head;} //无法识别的符号，输出错误信息
            case const_char:            {CharAnalyse(); break;}     //字符常量分析
            case digit:                 {DigitAnalyse(); break;}          //数字分析
            case letter:                {LetterAnalyse(); break;}        //字母分析
            case Relational_Operator:   {Relational_OperatorAnalyse(); break;}      //关系表达式分析
            case Plus: case Less: case Multi: case Except: case Braces_l: case Braces_r: case Parent_l: case Parent_r: case Semi: case Comma: 
                                        {SymbolAnalyse(); break;}           //符号分析
        }
    }
    return Head;
}