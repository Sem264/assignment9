#ifndef MAINHEADER_H_INCLUDED
#define MAINHEADER_H_INCLUDED

typedef struct{
    char name[20];
    int age;
    float weight;
    char *remarks;
}personalData;

personalData getPersonDesc(char *line);
int readData(personalData *data, int len);
int getOldestPersen(personalData data[]);
int getSlimmestPersen(personalData data[], int len);
char* checkInput(char *lineInput);
void printInfo(personalData ar[], int idx, char *msgOk, char * msgbad);
int checkName(char *token);
int checkAge(char *token);
int checkWeight(char *token);
char* getName(char *token);
int calculateAge(char *token);
void checkValidity(char *token, personalData *singleRecord);
float calculateWeight(char *token);
void freeAllRemarks(personalData *data, int length);
void printInfo(personalData ar[], int idx, char *msgOk, char * msgBad);
int getOldestPerson(personalData data[], int length);
int getSlimmestPerson(personalData data[], int length);
void setUpSingleRecord(personalData *singleRecord);


#endif // MAINHEADER_H_INCLUDED
