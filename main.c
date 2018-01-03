#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mainHeader.h"

int main()
{
    char lineInput[300];
    personalData *multipleRecords[20];
    int len = sizeof(multipleRecords)/sizeof(personalData *);
    int index = 0;
    while(fgets(lineInput, sizeof(lineInput), stdin)!=NULL){
        if(index>=len){
            break;
        }
        readPtrData(multipleRecords, lineInput, index);
        index++;
    }
   // multipleRecords[--index]->remarks = NULL;
    printPtrData(multipleRecords, index); //was ++index to negate prev --index
    weightSort(multipleRecords, index);
    remarksSort(multipleRecords, index);
    freeAllPointers(multipleRecords, index);
    return 0;
}





