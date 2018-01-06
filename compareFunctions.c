#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mainHeader.h"

int cmpfunc(const void *a, const void *b) {
    return((**((personalData**)a)).weight - (**((personalData**)b)).weight);
}

void weightSort(personalData **multipleRecords, int len){
    qsort(multipleRecords, len, sizeof(*multipleRecords), cmpfunc);
    printf("SORTED BY WEIGHT:\n");
    printPtrData(multipleRecords); //, len
}

int cmpfunc2(const void *a, const void *b) {
    return(strcmp((**((personalData**)a)).remarks, (**((personalData**)b)).remarks));
}

void remarksSort(personalData **multipleRecords, int len){
    qsort(multipleRecords, len, sizeof(*multipleRecords), cmpfunc2);
    printf("SORTED BY REMARKS:\n");
    printPtrData(multipleRecords); //, len
}
