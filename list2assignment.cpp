#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

struct Element{
    int value;
    Element *next;
};

struct List{
    Element *head;
    int activated;
};

void init(List& l){
    l.head = NULL;
    l.activated = 1;
}

void insertHead(List& l, int x){
    if(l.activated == 1){
        Element *newEl = new Element;
        newEl->value = x;
        newEl->next = l.head;
        l.head = newEl;
    }
}

bool deleteHead(List& l, int &oldHead){
    if(l.activated == 1 && l.head!=NULL){
        Element *delEl = l.head;
        oldHead = l.head->value;
        l.head = l.head->next;
        delete delEl;
        return true;
    }
	return false;
}

void insertTail(List& l, int x){
    if(l.activated == 1 && l.head!=NULL){
        Element *newEl = new Element;
        newEl->value = x;
        newEl->next = NULL;
        Element *testElem = l.head;
        while(testElem->next != NULL){
            testElem = testElem->next;
        }
        testElem->next = newEl;
    }
}

bool deleteTail(List& l, int &oldTail){
    if(l.activated == 1 && l.head!=NULL){
        Element *testElem = l.head;
        if(l.head->next == NULL){
            delete l.head;
            l.head = NULL;
            return true;
        }
        while(testElem->next->next != NULL){
            testElem = testElem->next;
        }
        oldTail = testElem->next->value;
        delete testElem->next;
        testElem->next = NULL;
        return true;
    }
	return false;
}

int findPosOfValue(List& l, int value){
    if(l.activated == 1 && l.head!=NULL){
        Element *testElem = l.head;
        int i = 0;
        while(testElem->next != NULL){
            if(testElem->value == value){
                return i;
            }
            testElem = testElem->next;
            i++;
        }
        if(testElem->value == value){
            return i;
        }
    }
	return -1;
}

bool deleteValue(List& l, int value){
    if(l.head!=NULL && l.activated == 1){
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
    if(l.head != NULL && l.activated == 1){
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
    if(l.head!=NULL && l.activated == 1){
        Element *elementInspected = l.head;
        while(elementInspected->next!=NULL){
            cout << elementInspected->value << ",";
            elementInspected = elementInspected->next;
        }
        cout << elementInspected->value << ",\n";
    }
}

void clearList(List& l){
    if(l.head!=NULL && l.activated == 1){
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
