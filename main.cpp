#include <iostream>
#include <string>
#include <sstream>

using namespace std;


// Two-way unordered cycled list without sentinel
struct Element{
    int value;
    Element *next;
    Element *previous;
};

struct List2W{
    Element *head;
    int active;
};

void init(List2W& l){
    l.head = NULL;
    l.active = 1;
}

void insertHead(List2W& l, int x){
    if(l.active==1){
        Element *newEl = new Element();
        newEl->value = x;
        if(l.head==NULL){
            newEl->next = newEl;
            newEl->previous = newEl;
            l.head = newEl;
        }else{
            newEl->next = l.head;
            newEl->previous = l.head->previous;
            l.head->previous->next = newEl;
            l.head->previous = newEl;
            l.head = newEl;
        }
    }
}

bool deleteHead(List2W& l, int &value){
    if(l.head == NULL || l.active!=1)
        return false;
    Element *deleteH = l.head;
    value = deleteH->value;
    if(l.head->next == l.head){
        delete deleteH;
        l.head = NULL;
        return true;
    }
    l.head = deleteH->next;
    l.head->previous = deleteH->previous;
    deleteH->previous->next = l.head;
    delete deleteH;
    return true;
}

void insertTail(List2W& l, int x){
    if(l.active==1){
        Element *newEl = new Element();
        newEl->value = x;
        if(l.head==NULL){
            newEl->next = newEl;
            newEl->previous = newEl;
            l.head = newEl;
        }else{
            newEl->next = l.head;
            newEl->previous = l.head->previous;
            l.head->previous->next = newEl;
            l.head->previous = newEl;
        }
    }
}

bool deleteTail(List2W& l, int &value){
    if(l.head==NULL || l.active!=1)
        return false;
    if(l.head->next == l.head){
        value = l.head->value;
        delete l.head;
        l.head = NULL;
        return true;
    }
    Element *deleteT = l.head->previous;
    value = deleteT->value;
    l.head->previous->previous->next = l.head;
    l.head->previous = l.head->previous->previous;
    delete deleteT;
    return true;
}

int findValue(List2W& l, int value){
    if(l.head!=NULL && l.active!=0){
        Element *searchedVal = l.head;
        int i = 0;
        while(searchedVal!=l.head->previous){
            if(searchedVal->value == value)
                return i;
            i++;
            searchedVal = searchedVal->next;
        }
        if(searchedVal->value == value)
                return i;
    }
	return -1;
}

void removeAllValue(List2W& l, int value){
    if(l.head!=NULL && l.active==1){
        Element *removedEl = l.head;
        while(removedEl->next!=l.head){
            Element *removeIt = NULL;
            if(removedEl->value == value){
                if(removedEl->next->next == removedEl){
                    l.head = l.head->next;
                    l.head->previous = l.head;
                    l.head->next = l.head;
                    removeIt =  removedEl;
                }else{
                    removedEl->previous->next = removedEl->next;
                    removedEl->next->previous = removedEl->previous;
                    if(removedEl == l.head){
                        l.head = removedEl->next;
                    }
                    removeIt =  removedEl;
                }
            }
            removedEl = removedEl->next;
            if(removeIt!=NULL){
                delete removeIt;
            }
        }
        if(removedEl->value == value && l.head->next == l.head){
            delete l.head;
            l.head = NULL;
        }else if(removedEl->value == value){
            removedEl->previous->next = l.head;
            l.head->previous = removedEl->previous;
            delete removedEl;
        }
    }
}

void showListFromHead(List2W& l){
    if(l.head!=NULL && l.active==1){
        Element *elementToShow = l.head;
        while(elementToShow->next!=l.head){
            cout<<elementToShow->value<<",";
            elementToShow = elementToShow->next;
        }
        cout<<elementToShow->value<<","<<endl;
    }else
        cout<<""<<endl;
}

void showListFromTail(List2W& l){
    if(l.head!=NULL && l.active==1){
        Element *elementToShow = l.head->previous;
        while(elementToShow->previous!=l.head->previous){
            cout<<elementToShow->value<<",";
            elementToShow = elementToShow->previous;
        }
        cout<<elementToShow->value<<","<<endl;
    }else
        cout<<""<<endl;
}

void clearList(List2W& l){
    if(l.head!=NULL && l.active==1){
        if(l.head->next == l.head){
            delete l.head;
            l.head = NULL;
        }else{
            Element *clearEl = l.head;
            Element *iteratorList = l.head;
            while(iteratorList->next!=l.head){
                iteratorList = iteratorList->next;
                delete clearEl;
                clearEl = iteratorList;
            }
            delete clearEl;
            l.head = NULL;
        }
    }
}

void addList(List2W& l1,List2W& l2){
    if(l1.active == 1 && l2.active == 1 && l1.head!=l2.head){
        if(l1.head!=NULL && l2.head!=NULL){
            l1.head->previous->next = l2.head;
            Element *prevL1 = l1.head->previous;
            l1.head->previous = l2.head->previous;
            l2.head->previous->next = l1.head;
            l2.head->previous = prevL1;
            l2.head = NULL;
        }else if(l1.head==NULL && l2.head!=NULL){
            l1.head = l2.head;
            l2.head = NULL;
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
