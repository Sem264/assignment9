#include<iostream>
#include<string.h>
#include <sstream>
#include <stdio.h>

using namespace std;

#define INFINITY 10000000

struct Graph{
    int size;
    double** matrix;
};



void insertEdge(Graph &g, int u, int v, double weight){
    for(int i = 1; i<=g.size; i++){
        if(g.matrix[i][0]==u){
            for(int j = 1; j<=g.size; j++){
                if(g.matrix[0][j]==v){
                    g.matrix[i][j] = weight;
                }
            }
        }
    }
}

void loadGraph(Graph &g, int n, int m){
    g.size = n;
    g.matrix = new double*[n+1];
    g.matrix[0] = new double[n+1];
    for(int j = 1; j<=n; j++)
        g.matrix[0][j] = j-1;
    for(int i = 1; i<=n;i++){
        g.matrix[i] = new double[n+1];
        g.matrix[i][0] = i-1;
        for(int j = 1; j<=n; j++){
            if(i==j)
                g.matrix[i][j] = 0;
            else
                g.matrix[i][j] = 9999999.9;
        }
    }
    string line;
    int k = 0;
    while(k<m){
        getline(cin,line);
        std::stringstream stream(line);
        int u,v;
        double w;
		stream >> u >> v >> w;
		insertEdge(g, u, v, w);
        k++;
    }
}

bool findEdge(Graph &g, int u, int v, double &weight){
    for(int i = 1; i<=g.size; i++){
        if(g.matrix[i][0]==u){
            for(int j = 1; j<=g.size; j++){
                if(g.matrix[0][j]==v){
                    if(g.matrix[i][j]!=9999999.9){
                        weight = g.matrix[i][j];
                        return true;
                    }else
                        return false;
                }
            }
        }
    }
    return false;
}

void showAsMatrix(Graph &g){
    for(int i = 1; i<=g.size; i++){
        for(int j = 1; j<=g.size; j++){
            if(g.matrix[i][j]==9999999.9)
                cout<<"-,";
            else
                cout<<g.matrix[i][j]<<",";
        }
        cout<<""<<endl;
    }
}

void showAsArrayOfLists(Graph &g){
    for(int i = 1; i<=g.size; i++){
        cout<<g.matrix[i][0]<<":";
        for(int j = 1; j<=g.size; j++){
            if(g.matrix[i][j]!=9999999.9 && g.matrix[i][j]!=0){
                cout<<g.matrix[0][j]<<"("<<g.matrix[i][j]<<"),";
            }
        }
        cout<<""<<endl;
    }
}


bool isCommand(const string command,const char *mnemonic){
	return command==mnemonic;
}


int main(){
	string line;
	string command;
	Graph *graph;
	int currentT=0;
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
		// zero-argument command
		if(isCommand(command,"SM"))
		{
			showAsMatrix(graph[currentT]);
			continue;
		}

		if(isCommand(command,"SA"))
		{
			showAsArrayOfLists(graph[currentT]);
			continue;
		}


		// read next argument, one int value
		stream >> value;

		if(isCommand(command,"LG"))
		{
			int m;
			stream >> m;
			loadGraph(graph[currentT],value,m);
			continue;
		}

		if(isCommand(command,"IE"))
		{
			int v;
			double w;
			stream >> v >> w;
			insertEdge(graph[currentT],value,v,w);
			continue;
		}

		if(isCommand(command,"FE"))
		{
			int v;
			stream >> v;
			double w;
			bool ret=findEdge(graph[currentT],value,v,w);

			if(ret)
				cout << w << endl;
			else
				cout << "false" << endl;
			continue;
		}


		if(isCommand(command,"CH"))
		{
			currentT=value;
			continue;
		}

		if(isCommand(command,"GO"))
		{
			graph=new Graph[value];
			continue;
		}

		cout << "wrong argument in test: " << command << endl;
		return 1;
	}
}
