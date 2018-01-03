#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mainHeader.h"

/*char* getName(char *token){
    char *name = malloc(strlen(token)*sizeof(char)+1);
    strncpy(name,token,strlen(token));
    name[strlen(token)]='\0';
    return name;
}*/

int calculateAge(char *token){
    int i = 0;
    int length = strlen(token)-1;
    int result = 0;
    while(token[i]!='\0'){
        result+=(token[i++]-'0')*(int)(pow(10,length--)+0.5);
    }
    return result;
}

float calculateWeight(char *token){
    int i = 0;
    int lengthInTen = 0;
    while(token[i++]!='.'){
        lengthInTen++;
    }
    lengthInTen--;
    i = 0;
    float result = 0;
    while(token[i]!='\0'){
        if(token[i]=='.'){
            i++;
        }else{
            result+=(token[i++]-'0')*pow(10,lengthInTen--);
        }
    }
    return result;
}
