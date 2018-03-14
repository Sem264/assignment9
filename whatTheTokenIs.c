/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

using namespace std;

struct Element{
    int value;
    struct Element *next;
    struct Element *prev;
};

struct lHead{
    struct Element *head;
};

void addElement(lHead & list, int value){
    Element *newEl = new Element();
    newEl->value = value;
    if(l.head!=NULL){
        Element *thisEl = l.head;
        if(l.head->next = l.head){
            if(l.head->value>newEl->value){
                l.head->next = newEl;
                l.head->prev = newEl;
                newEl->next = l.head;
                newEl->prev = l.head;
            }else{
                while(thisEl->next!=l.head){
                    if(thisEl->value < newEl->value){
                        newEl->prev = thisEl->prev;
                        newEl->next = thisEl;
                        thisEl->prev = newEl;
                        thisEl->prev->next = newEl;
                    }
                    thisEl = thisEl->next;
                }
                if(thisEl->value < newEl->value){
                    newEl->prev = thisEl->prev;
                    newEl->next = thisEl;
                    thisEl->prev = newEl;
                    thisEl->prev->next = newEl;
                }
            }
        }
    }
}

void removeCh(lHead &l, int value){
    Element *fEl = l.head;
    if(fEl->value == value && l.head->next == l.head){
        delete l.head;
        l.head = NULL;
    }else{
        while(fEl->value!=value && fEl->next!=l.head){
            int delete = 0;
            if(fEl->value == value){
                fEl->prev->next = fEl->next;
                fEl->next->prev = fEl->prev;
                delete = 1;
            }
            fEl = fEl->next;
            if(delete == 1)
                delete fEl->prev;
        }
        int delete = 0;
        if(fEl->value == value && l.head->next == l.head){
            delete l.head;
            l.head = NULL;
        }
        if(fEl->value == value){
            fEl->prev->next = fEl->next;
            fEl->next->prev = fEl->prev;
            delete = 1;
        }
        if(delete == 1)
            delete fEl;
    }
}

Element * findCh(lHead &l, int pos){
    Element *fEl = l.head;
    int posEl = 0;

    while(posEl!=pos && fEl->next!=l.head){
        int delete = 0;
        if(posEl == pos){
            return fEl;
        }
        fEl = fEl->next;
        posEl++;
    }
    if(posEl==pos){
       return fEl;
    }
}

void reverseList(lHead &l){
    Element *thisEl = l.head->prev;
    while(thisEl!=l.head){
        Element *wasNext = thisEl->next;
        Element *wasPrev = thisEl->prev;
        thisEl->next = wasPrev;
        thisEl->prev = wasNext;
    }
    Element *wasNext = thisEl->next;
    Element *wasPrev = thisEl->prev;
    thisEl->next = wasPrev;
    thisEl->prev = wasNext;
}

void copyList(lHead &l){
    lHead lCpy = new lHead;
    lCpy.head->NULL;
    Element *lCpyEl = lCpy.head;
    Element *lCpyHead = lCpy.head;
    Element *thisEl = l.head;
    while(thisEl->next!=l.head){
        lCpyEl = new Element();
        lCpyEl->prev = lCpyHead;
        lCpyEl->next = lCpy.head;
        lCpy.head->next = lCpyEl;
        lCpyEl->value = thisEl->value;
        lCpy.head->prev = lCpyEl;
        lCpyHead = lCpyHead;
        thisEl = thisEl->next;
    }
}


int main()
{
    return 0;
}
