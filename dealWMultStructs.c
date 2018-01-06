#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mainHeader.h"

void readPtrData(personalData **multipleRecords, char *lineInput, int index){
    multipleRecords[index] = getPersonPtr(lineInput);
}

void printPtrData(personalData **multipleRecords){ //, int len
    int i = 0;
    while(multipleRecords[i]->remarks!=NULL){
        printf("%s: Age - %i, Weight - %0.1lf, Remarks - %s\n", multipleRecords[i]->name, multipleRecords[i]->age, multipleRecords[i]->weight, multipleRecords[i]->remarks);
        i++;
    }
}

void freeAllPointers(personalData **multipleRecords, int index){
    int i;
    for(i = 0; i<index; i++){
        free(multipleRecords[i]->remarks);
        free(multipleRecords[i]);
    }
}
