#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

typedef struct Element{
    int value;
    struct Element *next;
}ElementLL;

struct List{
    ElementLL *head;
};

void init(List& l){
    l.head = NULL;
}

void insertHead(List& l, int x){
    ElementLL *newEl = new ElementLL;
    newEl->value = x;
    newEl->next = l.head;
    l.head = newEl;
}

bool deleteHead(List& l, int &oldHead){
    if(l.head!=NULL){
        oldHead = l.head->value;
        ElementLL *oldHeadPtr = l.head;
        l.head = l.head->next;
        delete oldHeadPtr;
        return true;
    }
    return false;
}

void insertTail(List& l, int x){
    ElementLL *newEl = new ElementLL;
    newEl->next = NULL;
    newEl->value = x;
    ElementLL *elementInspected = l.head;
    if(l.head!=NULL){
        while(elementInspected->next!=NULL){
            elementInspected = elementInspected->next;
        }
        elementInspected->next = newEl;
    }else{
        l.head = newEl;
    }
}

bool deleteTail(List& l, int &oldTail){
    if(l.head == NULL)
        return false;
    if(l.head->next == NULL){
        oldTail = l.head->value;
        delete l.head;
        l.head = NULL;
        return true;
    }
    ElementLL *beforeInspectedElem = NULL;
    ElementLL *elementInspected = l.head;
    while(elementInspected->next!=NULL){
        beforeInspectedElem = elementInspected;
        elementInspected = elementInspected->next;
    }
    oldTail = elementInspected->value;
    delete elementInspected;
    elementInspected = NULL;
    beforeInspectedElem->next = NULL;
    return true;
}

int findPosOfValue(List& l, int value){
    ElementLL *elementInspected = l.head;
    int i = 0;
    while(elementInspected->next!=NULL){
        if(elementInspected->value == value){
            return i;
        }
        elementInspected = elementInspected->next;
        i++;
    }
    if(elementInspected->value == value){
        return i;
    }
	return -1;
}

bool deleteValue(List& l, int value){
    if(l.head!=NULL){
        if(l.head->value == value){
            l.head = l.head->next;
            return true;
        }
        ElementLL *elementInspected = l.head;
        ElementLL *beforeInspectedElem = NULL;
        while(elementInspected->next!=NULL){
            if(elementInspected->value == value){
                beforeInspectedElem->next = elementInspected->next;
                delete elementInspected;
                return true;
            }
            beforeInspectedElem = elementInspected;
            elementInspected = elementInspected->next;
        }
        if(elementInspected->value == value){
            beforeInspectedElem->next = NULL;
            delete elementInspected;
            return true;
        }
        beforeInspectedElem = elementInspected;
        elementInspected = elementInspected->next;
    }
    return false;
}

bool atPosition(List& l, int pos, int &value){
    if(l.head != NULL){
        ElementLL *elementInspected = l.head;
        int i = 0;
        while(elementInspected->next!=NULL){
            if(i == pos){
                value = elementInspected->value;
                return true;
            }
            elementInspected = elementInspected->next;
            i++;
        }
        if(i == pos){
            value = elementInspected->value;
            return true;
        }
    }
	return false;
}

void showListFromHead(List& l){
    if(l.head!=NULL){
        ElementLL *elementInspected = l.head;
        while(elementInspected->next!=NULL){
            cout << elementInspected->value << ",";
            elementInspected = elementInspected->next;
        }
        cout << elementInspected->value <<endl;
    }
}

void clearList(List& l){
    ElementLL *elementInspected = l.head;
    l.head = NULL;
    ElementLL *nextInspected = NULL;
    while(elementInspected->next!=NULL){
        nextInspected = elementInspected->next;
        delete elementInspected;
        elementInspected = nextInspected;
    }
    nextInspected = NULL;
    delete elementInspected;
    elementInspected = NULL;
}

void showBool(bool val){
	if(val)
		cout << "true" << endl;
	else
		cout << "false" << endl;
}


bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	List *list=NULL;
	int currentL=0;
	int value;
	cout << "START" << endl;
	while(true){
		getline(cin,line);
		std::stringstream stream(line);
		stream >> command;
		if(line=="" || command[0]=='#')
		{
			// ignore empty line and comment
			continue;
		}

		// copy line on output with exclamation mark
		cout << "!" << line << endl;;

		// change to uppercase
		command[0]=toupper(command[0]);
		command[1]=toupper(command[1]);

		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}


		// zero-argument command
		if(isCommand(command,"DH"))
		{
			int retValue;
			bool retBool=deleteHead(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if(isCommand(command,"DT"))
		{
			int retValue;
			bool retBool=deleteTail(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"SH"))
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(isCommand(command,"CL"))
		{
			clearList(list[currentL]);
			continue;
		}

		if(isCommand(command,"IN"))
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"FP"))
		{
			int ret;
			ret=findPosOfValue(list[currentL],value);
			cout << ret << endl;
			continue;
		}

		if(isCommand(command,"DV"))
		{
			showBool(deleteValue(list[currentL],value));
			continue;
		}


		if(isCommand(command,"AT"))
		{
			int retValue;
			bool retBool=atPosition(list[currentL],value,retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IH"))
		{
			insertHead(list[currentL],value);
			continue;
		}

		if(isCommand(command,"IT"))
		{
			insertTail(list[currentL],value);
			continue;
		}

		if(isCommand(command,"GO"))
		{
			list=new List[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}
