#ifndef MAINHEADER_H_INCLUDED
#define MAINHEADER_H_INCLUDED

typedef struct{
    char name[20];
    char *remarks;
    int age;
    float weight;
}personalData;

personalData* getPersonPtr(char * line);
int checkToken(char *token, int *controller);
int isName(char *token);
int isAge(char *token);
int isWeight(char *token);
void calculateToken(char *token, int type, personalData *singlePerson);
int deriveAge(char *token);
float deriveWeight(char *token);
char *deriveRemarks(char *token);
void readPtrData(personalData **multipleRecords, char *lineInput, int index);
void freeAllPointers(personalData **multipleRecords, int index);
void printPtrData(personalData **multipleRecords, int len);
void printData(personalData **multipleRecords, int len);
void weightSort(personalData **multipleRecords, int len);
void remarksSort(personalData **multipleRecords, int len);
void sortRecords(personalData **multipleRecords);
//int cmpfunc(const void **a, const void **b);

#endif // MAINHEADER_H_INCLUDED
