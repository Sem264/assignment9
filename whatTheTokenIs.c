#include <stdio.h>
#include <stdlib.h>
#include "mainHeader.h"

int checkToken(char *token, int *controller){
    int ret = 0;
    if((ret = isName(token))){
        controller[0] = 1;
        return ret;
    }else if((ret = isAge(token))){
        controller[1] = 1;
        return ret;
    }else if((ret = isWeight(token))){
        controller[2] = 1;
        return ret;
    }else{
        if(controller[0]==1 && controller[1]==1 && controller[2]==1){
            controller[3] = 1;
            return 4;
        }else{
            return 0;
        }
    }
}

int isName(char *token){
    int i = 0;
    if(token[i]<'A' || token[i]>'Z'){
        return 0;
    }
    i++;
    while(token[i]!='\0'){
        if(token[i]<'a' || token[i]>'z'){
            return 0;
        }
        i++;
    }
    return 1;
}

int isAge(char *token){
    unsigned int i = 0;
    while(token[i]!='\0'){
        if(token[i]<'0' || token[i]>'9'){
            return 0;
        }
        i++;
    }
    return 2;
}

int isWeight(char *token){
    unsigned int i = 0;
    int dotC = 0;
    while(token[i]!='\0'){
        if(token[i]=='.' && dotC==0){
            dotC++;
        }else if(token[i]>='0' && token[i]<='9'){
            i++;
            continue;
        }else{
            return 0;
        }
        i++;
    }
    if(dotC == 0){
        return 0;
    }
    return 3;
}
