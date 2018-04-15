#include<iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// BST

using namespace std;


struct Element{
	int key;
	int value;
};

struct Node{
	Element elem;
	Node *parent;
	Node *left;
	Node *right;
	// TODO
};

// Binary search tree
struct BST{
    Node *root;
};

void init(BST & tree){
    tree.root = NULL;
}

bool insertElem(BST & tree, Element elem){
    Node *tracker = tree.root;
    if(tracker == NULL){
        Node *newNode = new Node;
        tree.root = newNode;
        newNode->left = NULL;
        newNode->parent = NULL;
        newNode->right = NULL;
        newNode->elem.key = elem.key;
        newNode->elem.value = elem.value;
        return true;
    }
    while(tracker!=NULL){
        if(tracker->elem.key<elem.key && tracker->right!=NULL){
            tracker = tracker->right;
        }else if(tracker->elem.key>elem.key && tracker->left!=NULL){
            tracker = tracker->left;
        }else if(tracker->left==NULL && tracker->elem.key>elem.key){
            Node *newNode = new Node;
            tracker->left = newNode;
            newNode->left = NULL;
            newNode->parent = tracker;
            newNode->right = NULL;
            newNode->elem.key = elem.key;
            newNode->elem.value = elem.value;
            return true;
        }else if(tracker->right==NULL && tracker->elem.key<elem.key){
            Node *newNode = new Node;
            tracker->right = newNode;
            newNode->left = NULL;
            newNode->parent = tracker;
            newNode->right = NULL;
            newNode->elem.key = elem.key;
            newNode->elem.value = elem.value;
            return true;
        }else if(tracker->elem.key==elem.key)
            return false;
    }
	return false;
}


void showInorder(BST & tree){
    Node *tracker = tree.root;
    Node *previous = tree.root;
    while(tracker!=NULL){
        if((tracker->left == previous || tracker->left==NULL) && tracker->right!=NULL && tracker->right!=previous){
            cout<<tracker->elem.key<<"("<<tracker->elem.value<<"),";
            tracker = tracker->right;
        }else if(tracker->left==previous && tracker->right==NULL){
            cout<<tracker->elem.key<<"("<<tracker->elem.value<<"),";
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->right == previous){
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left == NULL && tracker->right==NULL){
            cout<<tracker->elem.key<<"("<<tracker->elem.value<<"),";
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left!=previous && tracker->left!=NULL){
            tracker = tracker->left;
        }
    }
    cout<<""<<endl;
}

void showPreorder(BST & tree){
    Node *tracker = tree.root;
    Node *previous = tree.root;
    while(tracker!=NULL){
        if(tracker->left!=NULL && tracker->left!=previous && tracker->right!=previous){
            cout<<tracker->elem.key<<"("<<tracker->elem.value<<"),";
            tracker = tracker->left;
        }else if(tracker->left == NULL && tracker->right!=NULL && tracker->right!=previous){
            cout<<tracker->elem.key<<"("<<tracker->elem.value<<"),";
            tracker = tracker->right;
        }else if(tracker->right == previous){
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left == previous){
            if(tracker->right!=NULL){
                tracker = tracker->right;
            }else if(tracker->right==NULL){
                previous = tracker;
                tracker = tracker->parent;
            }
        }else if(tracker->left==NULL && tracker->right==NULL){
            cout<<tracker->elem.key<<"("<<tracker->elem.value<<"),";
            previous = tracker;
            tracker = tracker->parent;
        }
    }
    cout<<""<<endl;
}

void showPostorder(BST & tree){
    Node *tracker = tree.root;
    Node *previous = tree.root;
    while(tracker!=NULL){
        if(tracker->left!=NULL && tracker->left!=previous && tracker->right!=previous){
            tracker = tracker->left;
        }else if(tracker->left==NULL && tracker->right==NULL){
            cout<<tracker->elem.key<<"("<<tracker->elem.value<<"),";
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->right==previous){
            cout<<tracker->elem.key<<"("<<tracker->elem.value<<"),";
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left==NULL || tracker->left==previous){
            if(tracker->right!=NULL && tracker->right!=previous)
                tracker = tracker->right;
            else if(tracker->right==NULL){
                cout<<tracker->elem.key<<"("<<tracker->elem.value<<"),";
                previous = tracker;
                tracker = tracker->parent;
            }
        }
    }
    cout<<""<<endl;
}

/*Node *findNode(Node *node,int key){
	return NULL;
}*/



bool findKey(BST & tree,int key, Element &elem){
	Node *trackPos = tree.root;
    while(trackPos!=NULL){
        if(trackPos->elem.key>key){
            trackPos = trackPos->left;
        }else if(trackPos->elem.key<key){
            trackPos = trackPos->right;
        }else if(trackPos->elem.key==key){
            elem.key = key;
            elem.value = trackPos->elem.value;
            return true;
        }
    }
	return false;
}

/*Node *minimalNode(Node *node){
	return NULL;
}*/

bool removeKey(BST & tree, int key, Element &elem){
    Node *tracker = tree.root;
    while(tracker!=NULL){
        if(tracker->elem.key > key)
            tracker = tracker->left;
        else if(tracker->elem.key < key)
            tracker = tracker->right;
        else if(tracker->elem.key == key){
            elem.key = key;
            elem.value = tracker->elem.value;
            if(tracker->left==NULL && tracker->right==NULL){
                if(tracker->parent==NULL)
                    tree.root = NULL;
                else if(tracker == tracker->parent->left)
                    tracker->parent->left = NULL;
                else if(tracker == tracker->parent->right)
                    tracker->parent->right = NULL;
                return true;
            }else if(tracker->left!=NULL && tracker->right==NULL){
                tracker->left->parent = tracker->parent;
                if(tracker->parent==NULL)
                    tree.root = tracker->left;
                else if(tracker == tracker->parent->left)
                    tracker->parent->left = tracker->left;
                else if(tracker == tracker->parent->right)
                    tracker->parent->right = tracker->left;
                return true;
            }else if(tracker->left==NULL && tracker->right!=NULL){
                tracker->right->parent = tracker->parent;
                if(tracker->parent==NULL)
                    tree.root = tracker->right;
                else if(tracker == tracker->parent->left)
                    tracker->parent->left = tracker->right;
                else if(tracker == tracker->parent->right)
                    tracker->parent->right = tracker->right;
                return true;
            }else if(tracker->left!=NULL && tracker->right!=NULL){
                Node *successor = tracker;
                Node *nodeStart = tracker;
                Node *previous = tracker->left;
                while(tracker!=NULL){
                    if((tracker->left == previous || tracker->left==NULL) && tracker->right!=NULL && tracker->right!=previous){
                        tracker = tracker->right;
                        //successor = tracker;
                        //break;
                    }else if(tracker->left==previous && tracker->right==NULL){
                        previous = tracker;
                        tracker = tracker->parent;
                        successor = tracker;
                        break;
                    }else if(tracker->right == previous){
                        previous = tracker;
                        tracker = tracker->parent;
                    }else if(tracker->left == NULL && tracker->right==NULL){
                        if(tracker==nodeStart){
                            previous = tracker;
                            tracker = tracker->parent;
                        }
                        successor = tracker;
                        break;
                    }else if(tracker->left!=previous && tracker->left!=NULL){
                        tracker = tracker->left;
                    }
                }
                tracker = nodeStart;
                tracker->elem.key = successor->elem.key;
                tracker->elem.value = successor->elem.value;
                if(successor->left==NULL && successor->right==NULL){
                    if(successor->parent == NULL)
                        tree.root = NULL;
                    else if(successor==successor->parent->left)
                        successor->parent->left = NULL;
                    else if(successor==successor->parent->right)
                        successor->parent->right = NULL;
                }else if(successor->right!=NULL && successor->left==NULL){
                    successor->right->parent = successor->parent;
                    if(successor->parent ==NULL)
                        tree.root = successor->right;
                    else if(successor==successor->parent->left)
                        successor->parent->left = successor->right;
                    else if(successor==successor->parent->right)
                        successor->parent->right = successor->right;
                }else if(successor->right==NULL && successor->left!=NULL){
                    successor->left->parent = successor->parent;
                    if(successor->parent == NULL)
                        tree.root = successor->left;
                    if(successor==successor->parent->left)
                        successor->parent->left = successor->left;
                    else if(successor==successor->parent->right)
                        successor->parent->right = successor->left;
                }
                return true;
            }
        }
    }
	return false;
}

int numberOfNodes(BST & tree){
    Node *tracker = tree.root;
    Node *previous = tree.root;
    int counter = 0;
    while(tracker!=NULL){
        if(tracker->left!=NULL && tracker->left!=previous && tracker->right!=previous){
            tracker = tracker->left;
        }else if(tracker->left==NULL && tracker->right==NULL){
            counter++;
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->right==previous){
            counter++;
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left==NULL || tracker->left==previous){
            if(tracker->right!=NULL && tracker->right!=previous)
                tracker = tracker->right;
            else if(tracker->right==NULL){
                counter++;
                previous = tracker;
                tracker = tracker->parent;
            }
        }
    }
	return counter;
}

/*void clear(Node *node){

}*/

void clear(BST & tree){
    int totalNodes = numberOfNodes(tree);
    Node **nodesAddressArray = (Node **)malloc(totalNodes*sizeof(Node*));
    Node *tracker = tree.root;
    Node *previous = tree.root;
    int counter = 0;
    while(tracker!=NULL){
        if(tracker->left!=NULL && tracker->left!=previous && tracker->right!=previous){
            tracker = tracker->left;
        }else if(tracker->left==NULL && tracker->right==NULL){
            nodesAddressArray[counter++] = tracker;
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->right==previous){
            nodesAddressArray[counter++] = tracker;
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left==NULL || tracker->left==previous){
            if(tracker->right!=NULL && tracker->right!=previous)
                tracker = tracker->right;
            else if(tracker->right==NULL){
                nodesAddressArray[counter++] = tracker;
                previous = tracker;
                tracker = tracker->parent;
            }
        }
    }
    counter = 0;
    while(counter<totalNodes)
        free(nodesAddressArray[counter++]);
    tree.root = NULL;
}

int calculateApproxHeight(Node *tracker){
    if(tracker==NULL)
        return 0;
    int approxHeightLeft = calculateApproxHeight(tracker->left);
    int approxHeightRight = calculateApproxHeight(tracker->right);
    if(approxHeightLeft>approxHeightRight)
        return (approxHeightLeft+1);
    else
        return (approxHeightRight+1);
}

int height(BST & tree){
    Node *tracker = tree.root;
    if(tracker==NULL)
        return 0;
    int approxHeightLeft = calculateApproxHeight(tracker->left);
    int approxHeightRight = calculateApproxHeight(tracker->right);
    if(approxHeightLeft>approxHeightRight)
        return (approxHeightLeft+1);
    else
        return (approxHeightRight+1);
}

int functionA(BST & tree){
    if(tree.root!=NULL)
        return tree.root->elem.value;
	return -1;
}

int functionB(BST & tree, int key){
    Node *trackPos = tree.root;
    while(trackPos!=NULL){
        if(trackPos->elem.key>key){
            trackPos = trackPos->left;
        }else if(trackPos->elem.key<key){
            trackPos = trackPos->right;
        }else if(trackPos->elem.key==key){
            return trackPos->elem.value;
        }
    }
	return -1;
}

bool functionC(BST & tree, int key, Element &elem){
    if(findKey(tree,key,elem))
        return true;
	return false;
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
	BST *tree;
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

		if(isCommand(command,"SI"))
		{
			showInorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"SP"))
		{
			showPreorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"SQ"))
		{
			showPostorder(tree[currentT]);
			continue;
		}

		if(isCommand(command,"CL"))
		{
			clear(tree[currentT]);
			continue;
		}

		if(isCommand(command,"IN"))
		{
			init(tree[currentT]);
			continue;
		}

		if(isCommand(command,"NN"))
		{
			cout << numberOfNodes(tree[currentT]) << endl;
			continue;
		}

		if(isCommand(command,"HE"))
		{
			cout << height(tree[currentT]) << endl;
			continue;
		}

		if(isCommand(command,"FA"))
		{
			cout << functionA(tree[currentT]) << endl;
			continue;
		}

		// read next argument, one int value
		stream >> value;


		if(isCommand(command,"IE"))
		{
			int variable2;
			stream >> variable2;
			Element elem;
			elem.key=value;
			elem.value=variable2;
			showBool(insertElem(tree[currentT],elem));
			continue;
		}

		if(isCommand(command,"FK"))
		{
			Element elem;
			bool ret=findKey(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		if(isCommand(command,"RK"))
		{
			Element elem;
			bool ret=removeKey(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
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
			tree=new BST[value];
			continue;
		}

		if(isCommand(command,"FB"))
		{
			cout << functionB(tree[currentT],value) << endl;
			continue;
		}

		if(isCommand(command,"FC"))
		{
			Element elem;
			bool ret=functionC(tree[currentT], value, elem);
			if(ret)
				cout << elem.key << '(' << elem.value << ')' << endl;
			else
				cout << "false" << endl;
			continue;
		}

		cout << "wrong argument in test: " << command << endl;

	}
	return 0;
}
