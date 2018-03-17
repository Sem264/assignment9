#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Element{
	int key;
	int value;
};

struct ElementLL{
	Element elem;
	ElementLL *next, *prev;
};

// Two-way ordered cycled list with sentinel
struct List2W{
	ElementLL *sentinel;
};

void init(List2W& l){
	l.sentinel=new ElementLL();
	l.sentinel->next=l.sentinel;
	l.sentinel->prev=l.sentinel;
}

void insertElem(List2W & l, Element elem){
    if(l.sentinel!=NULL){
        ElementLL *newEl = new ElementLL();
        newEl->elem.value = elem.value;
        newEl->elem.key = elem.key;
        if(l.sentinel->next == l.sentinel){
            l.sentinel->next = newEl;
            l.sentinel->prev = newEl;
            newEl->next = l.sentinel;
            newEl->prev = l.sentinel;
        }else{
            ElementLL *tElem = l.sentinel->next;
            int modified = -1;
            while(tElem!=l.sentinel){
                modified = 0;
                int currentKey = tElem->elem.key;
                if(elem.key<currentKey){
                    newEl->next = tElem;
                    newEl->prev = tElem->prev;
                    tElem->prev->next = newEl;
                    tElem->prev = newEl;
                    modified = 1;
                    break;
                }else if(elem.key==currentKey){
                    ElementLL *sameElem = tElem;
                    while(sameElem!=l.sentinel && sameElem->elem.key==currentKey){
                        sameElem = sameElem->next;
                    }
                    sameElem = sameElem->prev;
                    newEl->prev = sameElem;
                    newEl->next = sameElem->next;
                    sameElem->next->prev = newEl;
                    sameElem->next = newEl;
                    modified = 1;
                    break;
                }
                tElem = tElem->next;
            }
            if(modified == 0){
                newEl->next = l.sentinel;
                newEl->prev = l.sentinel->prev;
                l.sentinel->prev->next = newEl;
                l.sentinel->prev = newEl;
            }

        }
    }
}

bool findKey(List2W & l,int key, Element &elem){
    ElementLL *thisElement = l.sentinel->next;
    while((thisElement!=l.sentinel) && (thisElement->elem.key!=key)){thisElement = thisElement->next;}
    if(thisElement->elem.key == key){
        elem.key = key;
        elem.value = thisElement->elem.value;
        return true;
    }
    return false;
}

void removeAllKeys(List2W& l, int key){
    if(l.sentinel!=NULL){
        ElementLL *thisElement = l.sentinel->next;
        while(thisElement!=l.sentinel){
            if(thisElement->elem.key!=key){
                thisElement = thisElement->next;
                continue;
            }
            ElementLL *deleteElement = thisElement;
            thisElement->prev->next = thisElement->next;
            thisElement->next->prev = thisElement->prev;
            thisElement = thisElement->next;
            delete deleteElement;
        }
        if(l.sentinel->next == l.sentinel){
            l.sentinel->next = l.sentinel;
            l.sentinel->prev = l.sentinel;
        }

    }
}

void showListFromHead(List2W& l){
    if(l.sentinel!=NULL){
        ElementLL *thisElement = l.sentinel->next;
        while(thisElement!=l.sentinel){
            cout<<thisElement->elem.key<<"("<<thisElement->elem.value<<"),";
            thisElement = thisElement->next;
        }
        cout<<""<<endl;
    }
}

void showListFromTail(List2W& l){
    if(l.sentinel!=NULL){
        ElementLL *thisElement = l.sentinel->prev;
        while(thisElement!=l.sentinel){
            cout<<thisElement->elem.key<<"("<<thisElement->elem.value<<"),";
            thisElement = thisElement->prev;
        }
        cout<<""<<endl;
    }
}

void clearList(List2W& l){
    if(l.sentinel!=NULL){
        ElementLL *thisElement = l.sentinel->next;
        while(thisElement!=l.sentinel){
            ElementLL *deleteElement = thisElement;
            thisElement->prev->next = thisElement->next;
            thisElement->next->prev = thisElement->prev;
            thisElement = thisElement->next;
            delete deleteElemenOt;
        }
        l.sentinel->next = l.sentinel;
        l.sentinel->prev = l.sentinel;
    }
}

void addList(List2W& l1,List2W& l2){
    if(l1.sentinel!=l2.sentinel){
        if(l1.sentinel->next == l1.sentinel){
            l1.sentinel->next = l2.sentinel->next;
            l1.sentinel->prev = l2.sentinel->prev;
            l2.sentinel->next->prev = l1.sentinel;
            l2.sentinel->prev->next = l1.sentinel;
            l2.sentinel->next = l2.sentinel;
            l2.sentinel->prev = l2.sentinel;
        }else if(l2.sentinel->next!=l2.sentinel && l1.sentinel->next!=l1.sentinel){
            ElementLL *elemL2 = l2.sentinel->next;
            ElementLL *elemL2Next = elemL2->next;
            while(elemL2!=l2.sentinel){
                int changed = -1;
                ElementLL *elemL1 = l1.sentinel->next;
                ElementLL *elemL1Next = elemL1->next;
                while(elemL1!=l1.sentinel){
                    if(elemL2->elem.key < elemL1->elem.key){
                        elemL2->next->prev = elemL2->prev;
                        elemL2->prev->next = elemL2->next;
                        elemL2->prev = elemL1->prev;
                        elemL2->next = elemL1;
                        elemL1->prev->next = elemL2;
                        elemL1->prev = elemL2;
                        changed = 1;
                        break;
                    }else if(elemL2->elem.key == elemL1->elem.key){
                        int currentKey = elemL1->elem.key;
                        while(elemL1->elem.key == currentKey && elemL1!=l1.sentinel){
                            elemL1 = elemL1Next;
                            elemL1Next = elemL1Next->next;
                        }
                        elemL2->next->prev = elemL2->prev;
                        elemL2->prev->next = elemL2->next;
                        elemL2->prev = elemL1->prev;
                        elemL2->next = elemL1;
                        elemL1->prev->next = elemL2;
                        elemL1->prev = elemL2;
                        changed = 1;
                        break;
                    }
                    elemL1 = elemL1Next;
                    elemL1Next = elemL1Next->next;
                }

                if(changed == -1){
                    elemL2->next->prev = elemL2->prev;
                    elemL2->prev->next = elemL2->next;
                    elemL2->prev = l1.sentinel->prev;
                    elemL2->next = l1.sentinel;
                    l1.sentinel->prev->next = elemL2;
                    l1.sentinel->prev = elemL2;
                }
                elemL2 = elemL2Next;
                elemL2Next = elemL2Next->next;
            }
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

		// zero-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
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

		if(isCommand(command,"FK"))
		{
			Element elem;
			bool ret=findKey(list[currentL], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(isCommand(command,"RK"))
		{
			removeAllKeys(list[currentL],value);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentL=value;
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			insertElem(list[currentL],elem);
			continue;
		}

		if(isCommand(command,"GO"))
		{
			list=new List2W[value];
			continue;
		}

		if(isCommand(command,"AD"))
		{
			addList(list[currentL],list[value]);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}
