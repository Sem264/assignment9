#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element{
    int value;
    struct Element *next;
};

struct List{
    int initializedL;
    Element *head;
};

void init(List& l){
    l.initializedL = 1;
    l.head = NULL;
}

void insertHead(List& l, int x){
    if(l.initializedL == 1){
        Element *newEl = new Element;
        newEl->value = x;
        newEl->next = l.head;
        l.head = newEl;
        newEl = NULL;
    }
}

bool deleteHead(List& l, int &oldHead){
    if(l.head!=NULL && l.initializedL == 1){
        oldHead = l.head->value;
        Element *oldHeadPtr = l.head;
        l.head = l.head->next;
        delete oldHeadPtr;
        oldHeadPtr = NULL;
        return true;
    }
    return false;
}

void insertTail(List& l, int x){
    if(l.initializedL == 1){
        Element *newEl = new Element;
        newEl->next = NULL;
        newEl->value = x;
        Element *elementInspected = l.head;
        if(l.head!=NULL){
            while(elementInspected->next!=NULL){
                elementInspected = elementInspected->next;
            }
            elementInspected->next = newEl;
        }else{
            l.head = newEl;
        }
        newEl = NULL;
    }
}

bool deleteTail(List& l, int &oldTail){
    if(l.initializedL != 1)
        return false;
    if(l.head == NULL && l.initializedL == 1)
        return false;
    if(l.head->next == NULL && l.initializedL == 1){
        oldTail = l.head->value;
        delete l.head;
        l.head = NULL;
        return true;
    }
    Element *beforeInspectedElem = l.head;
    Element *elementInspected = l.head->next;
    while(elementInspected->next!=NULL){
        beforeInspectedElem = elementInspected;
        elementInspected = elementInspected->next;
    }
    oldTail = elementInspected->value;
    delete elementInspected;
    elementInspected = NULL;
    beforeInspectedElem->next = NULL;
    beforeInspectedElem = NULL;
    return true;
}

int findPosOfValue(List& l, int value){
    if(l.head!=NULL && l.initializedL == 1){
        Element *elementInspected = l.head;
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
    }
	return -1;
}

bool deleteValue(List& l, int value){
    if(l.head!=NULL && l.initializedL == 1){
        if(l.head->value == value){
            l.head = l.head->next;
            return true;
        }
        Element *elementInspected = l.head;
        Element *beforeInspectedElem = NULL;
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
    if(l.head != NULL && l.initializedL == 1){
        Element *elementInspected = l.head;
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
    if(l.head!=NULL && l.initializedL == 1){
        Element *elementInspected = l.head;
        while(elementInspected->next!=NULL){
            cout << elementInspected->value << ",";
            elementInspected = elementInspected->next;
        }
        cout << elementInspected->value << "," << endl;
    }else if(l.head == NULL){
	     cout << "" << endl;
    }
}

void clearList(List& l){
    if(l.head!=NULL && l.initializedL == 1){
        Element *elementInspected = l.head;
        l.head = NULL;
        Element *nextInspected = NULL;
        while(elementInspected->next!=NULL){
            nextInspected = elementInspected->next;
            delete elementInspected;
            elementInspected = nextInspected;
        }
        delete elementInspected;
        nextInspected = NULL;
        elementInspected = NULL;
    }
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
