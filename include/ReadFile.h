#ifndef ReadFil

#define ReadFil

#include "common.h"

char *src;      //将文件内容读入src所指向的数组中
char *text, 
    *text_old;
char *token;
int readsize;   //数组大小
FILE *fp;        //文件描述字，调用open()时返回，需要在read()中使用

//读取文件，文件内容保存到src所指向的字符串中
void ReadFile();
//排除掉所有注释，文件内容保存到text所指向的字符串中；
void ClearAnnoation();
//取下一个字符
void next();

//回退一个字符
void back();


#endif