#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mainHeader.h"

personalData* getPersonPtr(char * line){
    int i = 0;
    int counter = 0;
    int index = 0;
    char token[100];
    personalData *singlePerson = malloc(sizeof(personalData)*1);
    int controller[4] = {0,0,0,0};
    while(line[i]!='\0'){
        if(line[i]==';'){
            while(counter<i){
                token[index++] = line[counter++];
            }
            token[index] = '\0';
            counter++;
            index = 0;
            int type = checkToken(token, controller);
            calculateToken(token, type, singlePerson);
        }
        i++;
    }
    return singlePerson;
}


void calculateToken(char *token, int type, personalData *singlePerson){
    switch (type){
    case 1:
        strncpy(singlePerson->name, token, sizeof(singlePerson->name)-1);
        break;
    case 2:
        singlePerson->age = deriveAge(token);
        break;
    case 3:
        singlePerson->weight = deriveWeight(token);
        break;
    case 4:
        singlePerson->remarks = deriveRemarks(token);
        break;
    case 0:
        singlePerson->remarks = NULL;
    }
}

int deriveAge(char *token){
    int i = 0;
    int length = 0;
    while(token[i++ + 1]!='\0'){
        length++;
    }
    i = 0;
    unsigned int number = 0;
    while(token[i]!='\0' && length>=0){
        number+=0.5+(token[i++]-'0')*(pow(10,(length--)));
    }
    return number;
}

float deriveWeight(char *token){
    int i = 0;
    int length = 0;
    while(token[i++ + 1]!='.'){
        length++;
    }
    i = 0;
    float weight = 0.0;
    while(token[i]!='\0'){
        if(token[i]!='.'){
            weight+=(token[i++]-'0')*(pow(10,(length--)));
        }else{
            i++;
        }
    }
    return weight;
}

char *deriveRemarks(char *token){
    int i = 0;
    while(token[i]!='\0'){
        i++;
    }
    char *remarksPtr = malloc(sizeof(char)*(i+1));
    strncpy(remarksPtr,token,i+1);
    return remarksPtr;
}

