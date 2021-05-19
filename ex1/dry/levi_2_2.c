/*
 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* foo(char* str, int* num) {
 char* str2;
 int i;
 num = strlen(str);
 str2 = malloc(*num);
 for (i = 0; i < *num; i++)
 str2[i] = str[*num - i];
 if (*num % 2 == 0) {
 printf("%s", str);
 }
 if (*num % 2 != 0)
 {
 printf("%s", str2);
 }
 return str2;
}
 * חסר כוכבית ב num
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* foo(char* str, int* x) {
    char* str2;
    int i;
    *x = strlen(str);
    str2 = (char *)malloc(sizeof(char)*(*x+1));
    for (i = 0; i < *x+1; i++)
        str2[i] = str[*x - i-1];
    if (*x % 2 == 0) {
        printf("%s", str);
    }
    if (*x % 2 != 0)
    {
        printf("%s", str2);
    }
    return str2;
}

int main(){
    char s[]="sapirhatusiki";
    char* str= s;
    int a=5;
    int* x= &a;
    foo(str,x);
    return 0;
}
