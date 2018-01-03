#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mainHeader.h"

void readPtrData(personalData **multipleRecords, char *lineInput, int index){
    multipleRecords[index] = getPersonPtr(lineInput);
}

void printPtrData(personalData **multipleRecords, int len){
    int i;
    for(i = 0; i<len; i++){
        //if((i+1)==len){
          //  printf("%s: Age - %i, Weight - %lf, Remarks - 0\n", multipleRecords[i]->name, multipleRecords[i]->age, multipleRecords[i]->weight);
        //}else{
            printf("%s: Age - %i, Weight - %lf, Remarks - %s\n", multipleRecords[i]->name, multipleRecords[i]->age, multipleRecords[i]->weight, multipleRecords[i]->remarks);
        //}
    }
}

void freeAllPointers(personalData **multipleRecords, int index){
    int i;
    for(i = 0; i<index; i++){
        free(multipleRecords[i]->remarks);
        free(multipleRecords[i]);
    }
}
