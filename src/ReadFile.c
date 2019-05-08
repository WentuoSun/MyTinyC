#include "ReadFile.h"

void ReadFile() {
    int i;
    readsize = sizeof(char) *1024; 
    src = (char *)malloc(readsize);
    //打开*agv 对应的文件，找不到返回错误信息
    if ( ( fp = fopen("tmp.txt", "r") ) == NULL ) {
        printf("Can not open \n") ;
        return;
    }
    //将文件中长度为readsize-1的字符保存到src中
    if ( (i = fread(src, sizeof(char), readsize, fp) )<= 0) {
        printf("read() return %d", i);
        return ;
    }
    src[i] = '\0';     //为文件末尾添加EOF
    fclose(fp);
    printf("\nthe original code is \n%s", src);
}
void ClearAnnoation(){
    int i,j;
    int tmpi;
    i = j = tmpi = 0;
    text = text_old = (char*)malloc(readsize);
    while(src[i] != '\0'){
        if( src[i] == '/') {
            tmpi = i;
            tmpi ++;
            if (src[tmpi] == '/') {
                i++;
                while ( src[i] != '\n') { i++; }
                i++;
            } else if ( src[tmpi] == '*') {
                i++;
                while ( src[i] != '*' || src[i+1] != '/') { i++; }
                i += 2;
            }
        }
        text[j++] = src[i++]; 
    }
    free(src);//释放存储空间
}
//测试
int main(){
    ReadFile();
    ClearAnnoation();
    printf("\n after clear the annoation is \n%s", text);

}