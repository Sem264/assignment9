#include<iostream>
#include <string>
#include <sstream>

using namespace std;


// Two-way unordered cycled list without sentinel
struct Element{
    int value;
    Element *next;
    Element *prev;
};

struct List2W{
    Element *head;
    Element *tail;
    int active;
};

void init(List2W& l){
    l.head = NULL;
    l.tail = NULL;
    l.active = 1;
}

void insertHead(List2W& l, int x){
    if(l.head==NULL && l.active == 1){
        Element *newEl = new Element();
        newEl->value = x;
        newEl->next = newEl;
        newEl->prev = newEl;
        l.head = newEl;
        l.tail = newEl;
    }else if(l.head!=NULL && l.active == 1){
        Element *newEl = new Element();
        newEl->value = x;
        newEl->next = l.head;
        newEl->prev = l.tail;
        l.tail->next = newEl;
        l.head->prev = newEl;
        l.head = newEl;
    }
}

bool deleteHead(List2W& l, int &value){
    if(l.head==NULL || (l.head!=NULL && l.active!=1))
        return false;
    if(l.head->next == l.head){
        value = l.head->value;
        delete l.head;
        l.head = NULL;
        l.tail = NULL;
        return true;
    }
    l.head->next->prev = l.tail;
    l.tail->next = l.head->next;
    Element *deleteElem = l.head;
    value = deleteElem->value;
    l.head = l.head->next;
    delete deleteElem;
    return true;
}

void insertTail(List2W& l, int x){
    if(l.head==NULL && l.active == 1){
        Element *newEl = new Element();
        newEl->value = x;
        newEl->next = newEl;
        newEl->prev = newEl;
        l.head = newEl;
        l.tail = newEl;
    }else if(l.head!=NULL && l.active == 1){
        Element *newEl = new Element();
        newEl->value = x;
        newEl->next = l.head;
        newEl->prev = l.tail;
        l.tail->next = newEl;
        l.head->prev = newEl;
        l.tail = newEl;
    }
}

bool deleteTail(List2W& l, int &value){
    if(l.tail==NULL || (l.tail!=NULL && l.active!=1))
        return false;
    if(l.tail->prev == l.tail){
        value = l.tail->value;
        delete l.tail;
        l.head = NULL;
        l.tail = NULL;
        return true;
    }
    Element *deleteElem = l.tail;
    value = deleteElem->value;
    l.tail = l.tail->prev;
    l.tail->next = l.head;
    if(l.tail->prev == deleteElem){
        l.tail->prev = l.tail;
    }else{
        l.tail->next = l.head;
        l.tail->next->prev = l.tail;
    }
    if(l.tail->next == deleteElem){
        l.tail->next = l.tail;
    }
    delete deleteElem;
    return true;
}

int findValue(List2W& l, int value){
    if(l.active==1 && l.head!=NULL){
        Element *elementFromList = l.head;
        int i = 0;
        while(elementFromList->next!=l.head){
            if(elementFromList->value == value)
                return i;
            elementFromList = elementFromList->next;
            i++;
        }
        if(elementFromList->value == value)
                return i;
    }
	return -1;
}

void removeAllValue(List2W& l, int value){
    if(l.head != NULL && l.active == 1){
        Element *elementList = l.head;
        Element *elementBefore = l.tail;
        while(elementList!=l.tail){
            if(elementList->value == value){
                if(elementList == l.head){
                    l.head = elementList->next;
                    l.tail->next = elementList->next;
                    elementList->next->prev = l.tail;
                    Element *deleteElem = elementList;
                    elementList = elementList->next;
                    delete deleteElem;
               }else{
                    elementBefore->next = elementList->next;
                    elementList->next->prev = elementBefore;
                    Element *deleteElem = elementList;
                    elementList = elementList->next;
                    delete deleteElem;
                }
            }else{
                elementBefore = elementList;
                elementList = elementList->next;
            }
        }

        if(elementList->next == elementList && elementList->value == value){
            delete elementList;
            l.head = NULL;
            l.tail = NULL;
        }else if(elementList->value == value){
            Element *deleteElem = l.tail;
            l.tail = elementList->prev;
            if(l.tail->prev == deleteElem){
                l.tail->prev = l.tail;
            }else{
                l.tail->next = l.head;
                l.tail->next->prev = l.tail;
            }
            if(l.tail->next == deleteElem){
                l.tail->next = l.tail;
            }
            delete deleteElem;
        }
    }
}

void showListFromHead(List2W& l){
    if(l.active==1 && l.head!=NULL){
        Element *elementFromList = l.head;
        while(elementFromList->next!=l.head){
            cout<<elementFromList->value<<",";
            elementFromList = elementFromList->next;
        }
        cout<<elementFromList->value<<",";
    }
    cout<<""<<endl;
}

void showListFromTail(List2W& l){
    if(l.active==1 && l.head!=NULL){
        Element *elementFromList = l.tail;
        while(elementFromList->prev!=l.tail){
            cout<<elementFromList->value<<",";
            elementFromList = elementFromList->prev;
        }
        cout<<elementFromList->value<<",";
    }
    cout<<""<<endl;
}

void clearList(List2W& l){
    if(l.active==1 && l.head!=NULL){
        Element *elementFromList = l.head;
        Element *delElem = NULL;
        while(elementFromList->next!=l.head){
            delElem = elementFromList;
            elementFromList = elementFromList->next;
            delete delElem;
        }
        delete delElem;
        l.head = NULL;
        l.tail = NULL;
    }
}

void addList(List2W& l1,List2W& l2){
    if(l1.active == 1 && l2.active == 1 && l1.head!=l2.head){
        if(l2.head != NULL && l1.head != NULL){
            l1.tail->next = l2.head;
            l2.tail->next = l1.head;
            l2.head->prev = l1.tail;
            l1.head->prev = l2.tail;
            l1.tail = l2.tail;
            l2.head = NULL;
            l2.tail = NULL;
        }else if(l1.head == NULL && l2.head != NULL){
            l1.head = l2.head;
            l1.tail = l2.tail;
            l2.head = NULL;
            l2.tail = NULL;
        }
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
	List2W *list;
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
		if(isCommand(command,"DH")) //*
		{
			int retValue;
			bool retBool=deleteHead(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}
		if(isCommand(command,"DT")) //*
		{
			int retValue;
			bool retBool=deleteTail(list[currentL],retValue);
			if(retBool)
				cout << retValue << endl;
			else
				showBool(retBool);
			continue;
		}

		if(isCommand(command,"SH")) //*
		{
			showListFromHead(list[currentL]);
			continue;
		}

		if(isCommand(command,"ST")) //*
		{
			showListFromTail(list[currentL]);
			continue;
		}

		if(isCommand(command,"CL")) //*
		{
			clearList(list[currentL]);
			continue;
		}

		if(isCommand(command,"IN")) //*
		{
			init(list[currentL]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"FV")) //*
		{
			int ret;
			ret=findValue(list[currentL],value);
			cout << ret << endl;
			continue;
		}

		if(isCommand(command,"RV")) //*
		{
			removeAllValue(list[currentL],value);
			continue;
		}


		if(isCommand(command,"AD")) //*
		{
			addList(list[currentL],list[value]);
			continue;
		}

		if(isCommand(command,"CH")) //*
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IH")) //*
		{
			insertHead(list[currentL],value);
			continue;
		}

		if(isCommand(command,"IT")) //*
		{
			insertTail(list[currentL],value);
			continue;
		}

		if(isCommand(command,"GO")) //*
		{
			list=new List2W[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
}
