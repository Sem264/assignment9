#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mainHeader.h"

int checkName(char *token){
    int i = 0;
    if(!(token[i]>='A' && token[i]<='Z')){
        return 0;
    }
    while(token[i]!='\0'){
        if((int)token[i]==32 && ((token[i+1]>='A' && token[i+1]<='Z') || (token[i+1]>='a' && token[i+1]<='z'))){
            return 0;
        }
        i++;
    }
    return 1;
}

int checkAge(char *token){
    int i = 0;
    while(token[i]!='\0'){
        if(token[i]>='0' && token[i]<='9'){
            i++;
        }else{
            return 0;
        }
    }
    return 2;
}

int checkWeight(char *token){
    int i = 0;
    int dotC = 0;
    while(token[i]!='\0'){
        if(token[i]>='0' && token[i]<='9'){
            i++;
        }else if(dotC==0 && token[i]=='.'){
            i++;
            dotC++;
        }else{
            return 0;
        }
    }
    return 3;
}
