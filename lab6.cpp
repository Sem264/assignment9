#include<iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <math.h>

using namespace std;


struct Heap{
	int *arr;
	int size;
	int pos;
	int border;
};

void init(Heap& h, int size){
    h.arr = new int[size];
    h.size = size;
    h.pos = 0;
    h.border = size;
}

void heapify(Heap &h){
    int indexChild = h.pos*2+1;
    if(indexChild<h.border){
        if(h.arr[indexChild]<h.arr[indexChild+1] && (indexChild+1)<h.border){
            indexChild++;
        }
        if(h.arr[indexChild]>h.arr[h.pos]){
            int temp = h.arr[h.pos];
            h.arr[h.pos] = h.arr[indexChild];
            h.arr[indexChild] = temp;
            h.pos = indexChild;
            heapify(h);
        }
    }
}

void heapAdjustment(Heap &h){
    for(int i = (h.border-1)/2;i>=0;i--){
        h.pos = i;
        heapify(h);
    }
}

void loadAndMakeHeap(Heap &h, int howMany){
    char *charsEntered = new char[howMany*5];
    h.border = howMany;
    int counter;
    double number;
    int ii;
    int j = 0;
    if(fgets(charsEntered, howMany*5, stdin)!=NULL){
        for(int i = 0; i<howMany*5; i++){
            counter = 0;
            number = 0;
            ii = 0;
            while(charsEntered[i]!=' ' && charsEntered[i+1]!='\0' && (int)charsEntered[i]!=0 && i<howMany*5){
                counter++;
                i++;
            }
            if(counter==0)
                break;
            ii = i-1;
            int powerTen = 0;
            while(counter>0){
                number+= (charsEntered[ii--]-48)*(pow(10,powerTen++));
                counter--;
            }
            h.arr[j++] = (int)number;
        }
        heapAdjustment(h);
    }
}


void add(Heap &h, int value){
    if(h.border<h.size){
        h.arr[h.border] = value;
        h.border = h.border+1;
        heapAdjustment(h);
    }
}


void makeSorted(Heap& h){
    heapAdjustment(h);
    int size = h.border;
    for(int i = h.border-1; i>=0;i--){
        int temp = h.arr[i];
        h.arr[i] = h.arr[0];
        h.arr[0] = temp;
        h.pos = 0;
        h.border = i;
        heapify(h);
    }
    h.border = size;
}

void show(Heap& h){
  for(int i=0;i<h.border;i++)
  {
	  cout << h.arr[i] << ",";
  }
  cout << endl;
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
	Heap *heap;
	int currentH=0;
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
			show(heap[currentH]);
			continue;
		}

		if(isCommand(command,"MS")) //*
		{
			makeSorted(heap[currentH]);
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"IN")) //*
		{
			init(heap[currentH],value);
			continue;
		}

		if(isCommand(command,"LD"))
		{
			loadAndMakeHeap(heap[currentH],value);
			continue;
		}

		if(isCommand(command,"AD"))
		{
			add(heap[currentH],value);
			continue;
		}

		if(isCommand(command,"CH"))
		{
			currentH=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			heap=new Heap[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}
