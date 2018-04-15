#include<iostream>
#include<string.h>
#include <string>
#include <sstream>

using namespace std;

	class Queue{
	public:
	    int sizeQ;
	    int topOfQueue;
	    int *data;
	};

	void init(Queue& q, int size){
        q.data = new int[size];
        q.sizeQ = size;
        q.topOfQueue = 0;
	}

	bool enqueue(Queue& q, int value){
	    if(q.topOfQueue==q.sizeQ)
            return false;
        q.data[q.topOfQueue++] = value;
        return true;
	}

	bool dequeue(Queue& q, int &value){
	    if(q.topOfQueue==0)
            return false;
        value = q.data[0];
        for(int i = 0; i<q.topOfQueue-1; i++){
            q.data[i] = q.data[i+1];
        }
        q.topOfQueue--;
        return true;
	}

	bool isEmpty(Queue& q){
	    if(q.topOfQueue==0)
            return true;
        return false;
	}

	bool isFull(Queue& q){
	    if(q.topOfQueue==q.sizeQ)
            return true;
        return false;
	}

	void show(Queue& q){
	    for(int i = 0; i<q.topOfQueue; i++){
            cout << q.data[i] << ",";
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
	Queue *queue=NULL;
	int currentQ=0;
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
		if(isCommand(command,"EM"))
		{
			showBool(isEmpty(queue[currentQ]));
			continue;
		}
		if(isCommand(command,"FU"))
		{
			showBool(isFull(queue[currentQ]));
			continue;
		}
		if(isCommand(command,"SH"))
		{
			show(queue[currentQ]);
			continue;
		}
		if(isCommand(command,"DE"))
		{
			int ret;
			bool retBool=dequeue(queue[currentQ],ret);
			if(!retBool)
				cout << "false" << endl;
			else
				cout << ret << endl;
			continue;
		}

		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"GO"))
		{
			queue=new Queue[value];
			continue;
		}
		if(isCommand(command,"CH"))
		{
			currentQ=value;
			continue;
		}

		if(isCommand(command,"IN"))
		{
			init(queue[currentQ],value);
			continue;
		};

		if(isCommand(command,"EN"))
		{
			bool retBool=enqueue(queue[currentQ],value);
			showBool(retBool);
			continue;
		}
		cout << "wrong argument in test: " << command << endl;
	}
}
