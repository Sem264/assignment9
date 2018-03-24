#include<iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void showArray(int array[], int size){
    for(int i= 0; i<size;i++){
        cout<<array[i]<<",";
    }
    cout<<""<<endl;
}

/*void insertSort(int array[], int size){
    int valueComp, currentIdx, substituteIdx, countPos;
    for(currentIdx = 1; currentIdx<size; currentIdx++){
        valueComp = array[currentIdx];
        countPos = currentIdx;
        for(substituteIdx = 0;substituteIdx<currentIdx;substituteIdx++){
            if(array[substituteIdx]>=valueComp){
                while(countPos!=substituteIdx){
                    array[countPos] = array[countPos-1];
                    countPos--;
                }
                array[substituteIdx] = valueComp;
                break;
            }
        }
        showArray(array, size);
    }
}*/

void insertSort(int array[], int size){
    int valueComp, currentIdx, substituteIdx, countPos;
    for(currentIdx = size-2; currentIdx>=0; currentIdx--){
        valueComp = array[currentIdx];
        for(substituteIdx = size-1;((currentIdx<substituteIdx) && (array[substituteIdx]>=valueComp));substituteIdx--){}
        countPos = currentIdx;
        while(countPos!=substituteIdx){
            array[countPos] = array[countPos+1];
            countPos++;
        }
        array[substituteIdx] = valueComp;
        showArray(array, size);
    }
}

/*void bubbleSort(int array[], int size){
    for(int i = size-1; i>=0; i--){
        for(int j = 0; j<i; j++){
            if(array[j]>array[j+1]){
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
        showArray(array, size);
    }
}*/

void bubbleSort(int array[], int size){
    for(int i = size-1; i>0; i--){
        for(int j = size-1; j>0; j--){
            if(array[j-1]>array[j]){
                int temp = array[j];
                array[j] = array[j-1];
                array[j-1] = temp;
            }
        }
        showArray(array, size);
    }
}


void mergeSortIter(int array[], int size){
    if(size>1){
        for(int sizeTemp = 1;sizeTemp<=size;sizeTemp*=2){
            for(int j = 0; j<=size-sizeTemp; j+=(2*sizeTemp)){
                int sizeLeft = sizeTemp, sizeRight = sizeTemp;
                int pointerLeft = j;
                int pointerRight = j+sizeTemp;
                int *arrayTemp = new int[2*sizeTemp];
                for(int k = 0; k<(2*sizeTemp); k++){
                    if(sizeLeft==0 && sizeRight>0){
                        arrayTemp[k] = array[pointerRight++];
                        sizeRight--;
                    }
                    else if(sizeRight==0 && sizeLeft>0){
                        arrayTemp[k] = array[pointerLeft++];
                        sizeRight--;
                    }
                    else if(array[pointerLeft]<=array[pointerRight] && sizeLeft>0){
                        arrayTemp[k] = array[pointerLeft++];
                        sizeLeft--;
                    }
                    else if(array[pointerRight]<array[pointerLeft] && sizeRight>0){
                        arrayTemp[k] = array[pointerRight++];
                        sizeRight--;
                    }

                }
                int counterTemp = 0;
                showArray(arrayTemp,2*sizeTemp);
                for(int g = j; g<j+(2*sizeTemp); g++){
                    array[g] = arrayTemp[counterTemp++];
                }
                showArray(array,size);
                delete [] arrayTemp;
                //showArray(array,size);
            }
//            showArray(array,size);
        }
    }
}

int * loadArray(int size){
	// TODO !!!
	int *arr = new int[size];
	char *arrChar = new char[size*5];
	int countOneInt;
    int arrIndex = 0;
	while((fgets(arrChar,size*5,stdin)!=NULL) && arr!=NULL){
        for(int i = 0; (i<size*5); i++){
            int outLoop = 0;
            countOneInt = 0;
            int digitN[10];
            while(arrChar[i]!=' '){
                if((arrChar[i]==0 || arrChar[i]==10) && (arrChar[i+1]==0 || i == (size*5-1))){
                    outLoop = 1;
                    break;
                }
                digitN[(sizeof(digitN)/sizeof(int))-(++countOneInt)] = arrChar[i]-48;
                i++;
            }
            if(countOneInt!=0){
                int number = 0;
                int powerTen = 0;
                for(countOneInt; countOneInt>=1; countOneInt--){
                    number+=digitN[sizeof(digitN)/sizeof(int)-countOneInt]*pow(10,powerTen++);
                }
                arr[arrIndex] = number;
                arrIndex++;
            }
            if(outLoop == 1)
                break;
        }
	}
	if(arrChar!=NULL && arr!=NULL){
        delete [] arrChar;
        return arr;
	}
	return NULL;
}

bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}

int main(){
	string line;
	string command;
	int size=0;
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

		// read next argument, one int size
		stream >> size;

		// one-argument command
		if(isCommand(command,"HA")){
			cout << "END OF EXECUTION" << endl;
			break;
		}

		if(isCommand(command,"IS")) //*
		{
			int *arr=loadArray(size);
			showArray(arr,size);
			insertSort(arr,size);
			continue;
		}

		if(isCommand(command,"BS")) //*
		{
			int *arr=loadArray(size);
			showArray(arr,size);
			bubbleSort(arr,size);
			continue;
		}

		if(isCommand(command,"MI")) //*
		{
			int *arr=loadArray(size);
			showArray(arr,size);
			mergeSortIter(arr,size);
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
	}
	return 0;
}
