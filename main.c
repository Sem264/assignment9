#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mainHeader.h"

int main()
{
    personalData data[10];
    int len = sizeof(data)/sizeof(personalData);
    len = readData(data, len);
    int idx;
    char *msgBad="No available data";
    idx=getOldestPerson(data,len);
    printInfo(data, idx, "Oldest person", msgBad);
    idx=getSlimmestPerson(data, len);
    printInfo(data, idx, "Slimmest person", msgBad);
    puts("End of work!");
    freeAllRemarks(data, len);
    return 0;
}

int readData(personalData *data, int len){
    int i = 0;
    char lineInput[300];
    while(i<len){
        if(fgets(lineInput, sizeof(lineInput), stdin)!=NULL){
            personalData singleRecord;
            setUpSingleRecord(&singleRecord);
            singleRecord = getPersonDesc(lineInput);
            data[i++] = singleRecord;
        }else{
            break;
        }
    }
    return i;
}


personalData getPersonDesc(char * line){
    int i = 0;
    int position = 0;
    personalData singleRecord;
    while(line[i]!='\0'){
        if(line[i]==';'){
            char token[30];
            int k = 0;
            while(k<sizeof(token)){
                token[k++]=0;
            }
            k = 0;
            while(position<i){
                token[k++] = line[position++];
            }
            position++;
            checkValidity(token, &singleRecord);
        }
        i++;
    }
    return singleRecord;
}

void checkValidity(char *token, personalData *singleRecord){
    int i = 0;
    if((i = checkAge(token))){
        int age = calculateAge(token);
        singleRecord->age = age;
    }else if((i = checkName(token))){
        strncpy(singleRecord->name,token,strlen(token));
        singleRecord->name[strlen(token)]='\0';
    }else if((i = checkWeight(token))){
        float weight = calculateWeight(token);
        singleRecord->weight = weight;
    }else{
        char *remarks = malloc(strlen(token)+1);
        strncpy(remarks,token,strlen(token));
        remarks[strlen(token)]='\0';
        singleRecord->remarks = remarks;
    }
}


void freeAllRemarks(personalData *data, int length){
    int i;
    while(i<length){
        free(data[i++].remarks);
    }
}


void printInfo(personalData ar[], int idx, char *msgOk, char * msgBad){
    if(idx<0){
        printf("%s", msgBad);
    }else{
        printf("%s: %s; %i; %lf; %s;\n", msgOk, ar[idx].name, ar[idx].age, ar[idx].weight, ar[idx].remarks);
    }
}

int getOldestPerson(personalData *data, int length){
    int i;
    int index = 0;
    if(data[index].age == 0){
        return -1;
    }
    int age = data[0].age;
    for(i = 1; i<length; i++){
        if(data[i].age>age){
            age = data[i].age;
            index = i;
        }
    }
    return index;
}

int getSlimmestPerson(personalData *data, int length){
    int i;
    int index = 0;
    if(data[index].weight == 0){
        return -1;
    }
    int weight = data[0].weight;
    for(i = 1; i<length; i++){
        if(data[i].weight<weight){
            weight = data[i].weight;
            index = i;
        }
    }
    return index;
}

void setUpSingleRecord(personalData *singleRecord){
    singleRecord->name[0] = '\0';
    singleRecord->age = 0;
    singleRecord->weight = 0.0;
    singleRecord->remarks = NULL;
}
