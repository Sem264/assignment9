#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Node{
    char word[32];
    int number;
    Node *parent;
    Node *left;
    Node *right;
};

struct BST{
    Node *root;
};

struct NodeBalanced{
    char word[32];
    int number;
    int heightBelow;
    int balanceFactor;
    NodeBalanced *parent;
    NodeBalanced *left;
    NodeBalanced *right;
};

struct BBST{
    NodeBalanced *root;
};

Node *findMinimum(BST &tree){
    Node *tracker = tree.root;
    while(tracker->left!=NULL)
        tracker = tracker->left;
    return tracker;
}

NodeBalanced *findMinimum(BBST &tree){
    NodeBalanced *tracker = tree.root;
    while(tracker->left!=NULL)
        tracker = tracker->left;
    return tracker;
}

void findPosition(BST &tree, char *wordNew){
    if(tree.root==NULL){
        Node *newNode = new Node;
        strncpy(newNode->word, wordNew, strlen(wordNew));
        newNode->word[strlen(wordNew)] = '\0';
        newNode->left = NULL;
        newNode->parent = NULL;
        newNode->right = NULL;
        tree.root = newNode;
        newNode->number = 1;
    }else if(tree.root!=NULL){
        Node *tracker = tree.root;
        Node *previous = tree.root;
        int added = 0;
        while(tracker!=NULL){
            if((tracker->left == previous || tracker->left==NULL) && tracker->right!=NULL && tracker->right!=previous){
                if(!strcmp(wordNew, tracker->word)){
                    tracker->number++;
                    added = 1;
                    break;
                }
                tracker = tracker->right;
            }else if(tracker->left==previous && tracker->right==NULL){
                if(!strcmp(wordNew, tracker->word)){
                    tracker->number++;
                    added = 1;
                    break;
                }
                previous = tracker;
                tracker = tracker->parent;
            }else if(tracker->right == previous){
                previous = tracker;
                tracker = tracker->parent;
            }else if(tracker->left == NULL && tracker->right==NULL){
                if(!strcmp(wordNew, tracker->word)){
                    tracker->number++;
                    added = 1;
                    break;
                }
                previous = tracker;
                tracker = tracker->parent;
            }else if(tracker->left!=previous && tracker->left!=NULL){
                tracker = tracker->left;
            }
        }
        if(added == 0){
            Node *newNode = new Node;
            strncpy(newNode->word, wordNew, strlen(wordNew));
            newNode->word[strlen(wordNew)] = '\0';
            newNode->left = NULL;
            newNode->right = NULL;
            Node *minNode = findMinimum(tree);
            minNode->left = newNode;
            newNode->parent = minNode;
            newNode->number = 1;
        }
    }
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

void findMaximum10BST(BST &tree){
    int numberNodes = numberOfNodes(tree);
    Node** arrNodes = new Node*[numberNodes];
    Node *tracker = tree.root;
    int counter = 0;
    Node *previous = tree.root;
    while(tracker!=NULL){
        if((tracker->left == previous || tracker->left==NULL) && tracker->right!=NULL && tracker->right!=previous){
            arrNodes[counter++] = tracker;
            tracker = tracker->right;
        }else if(tracker->left==previous && tracker->right==NULL){
            arrNodes[counter++] = tracker;
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->right == previous){
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left == NULL && tracker->right==NULL){
            arrNodes[counter++] = tracker;
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left!=previous && tracker->left!=NULL){
            tracker = tracker->left;
        }
    }
    for(counter = 1; counter<numberNodes; counter++){
        for(int j = 0; j<counter; j++){
            if(arrNodes[j]->number<arrNodes[counter]->number){
                Node *temp = arrNodes[counter];
                for(int k = counter; k>j; k--){
                    arrNodes[k] = arrNodes[k-1];
                }
                arrNodes[j] = temp;
            }
        }
    }
    counter = 0;
    while(counter!=10 && counter!=numberNodes){
        cout<<arrNodes[counter]->word<<" - "<<arrNodes[counter]->number<<endl;
        counter++;
    }
    delete [] arrNodes;
}

/////////BALANCED BINARY SEARCH TREE///////////


NodeBalanced * leftRotate(BBST& treeBalanced, NodeBalanced *tracker){
    NodeBalanced *trackerRightChild = tracker->right;
    tracker->right = trackerRightChild->left;
    if(trackerRightChild->left!=NULL)
        trackerRightChild->left->parent = tracker;
    trackerRightChild->parent = tracker->parent;
    if(tracker->parent==NULL)
       treeBalanced.root = trackerRightChild;
    else if(tracker == tracker->parent->left)
       tracker->parent->left = trackerRightChild;
    else if(tracker == tracker->parent->right)
       tracker->parent->right = trackerRightChild;
    trackerRightChild->left = tracker;
    tracker->parent = trackerRightChild;
    return trackerRightChild;
}

NodeBalanced * rightRotate(BBST& treeBalanced, NodeBalanced *tracker){
    NodeBalanced *trackerLeftChild = tracker->left;
    tracker->left = trackerLeftChild->right;
    if(trackerLeftChild->right!=NULL)
        trackerLeftChild->right->parent = tracker;
    trackerLeftChild->parent = tracker->parent;
    if(tracker->parent==NULL)
       treeBalanced.root = trackerLeftChild;
    else if(tracker == tracker->parent->left)
       tracker->parent->left = trackerLeftChild;
    else if(tracker == tracker->parent->right)
       tracker->parent->right = trackerLeftChild;
    trackerLeftChild->right = tracker;
    tracker->parent = trackerLeftChild;
    return trackerLeftChild;
}

void startRotating(BBST &treeBalanced, NodeBalanced *tracker){
    if(tracker->right!=NULL && tracker->right->balanceFactor==1){
        tracker = leftRotate(treeBalanced, tracker);
        tracker->balanceFactor = 0;
        tracker->left->balanceFactor = 0;
    }else if(tracker->right!=NULL && tracker->right->left!=NULL && tracker->right->balanceFactor==-1 && tracker->right->left->balanceFactor==1){
        rightRotate(treeBalanced, tracker->right);
        tracker = tracker->parent;
        tracker = leftRotate(treeBalanced,tracker);
        tracker->balanceFactor = 0;
        tracker->left->balanceFactor = -1;
        tracker->right->balanceFactor = 0;
    }else if(tracker->right!=NULL && tracker->right->left!=NULL && tracker->right->balanceFactor==-1 && tracker->right->left->balanceFactor==-1){
        rightRotate(treeBalanced, tracker->right);
        tracker = tracker->parent;
        tracker = leftRotate(treeBalanced,tracker);
        tracker->balanceFactor = 0;
        tracker->left->balanceFactor = 0;
        tracker->right->balanceFactor = -1;
    }
}

int numberOfNodes(BBST & tree){
    NodeBalanced *tracker = tree.root;
    NodeBalanced *previous = tree.root;
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

void findMaximum10BBST(BBST &tree){
    int numberNodes = numberOfNodes(tree);
    NodeBalanced** arrNodes = new NodeBalanced*[numberNodes];
    NodeBalanced *tracker = tree.root;
    int counter = 0;
    NodeBalanced *previous = tree.root;
    while(tracker!=NULL){
        if((tracker->left == previous || tracker->left==NULL) && tracker->right!=NULL && tracker->right!=previous){
            arrNodes[counter++] = tracker;
            tracker = tracker->right;
        }else if(tracker->left==previous && tracker->right==NULL){
            arrNodes[counter++] = tracker;
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->right == previous){
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left == NULL && tracker->right==NULL){
            arrNodes[counter++] = tracker;
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left!=previous && tracker->left!=NULL){
            tracker = tracker->left;
        }
    }
    for(counter = 1; counter<numberNodes; counter++){
        for(int j = 0; j<counter; j++){
            if(arrNodes[j]->number<arrNodes[counter]->number){
                NodeBalanced *temp = arrNodes[counter];
                for(int k = counter; k>j; k--){
                    arrNodes[k] = arrNodes[k-1];
                }
                arrNodes[j] = temp;
            }
        }
    }
    counter = 0;
    while(counter!=10 && counter!=numberNodes){
        cout<<arrNodes[counter]->word<<" - "<<arrNodes[counter]->number<<endl;
        counter++;
    }
    delete [] arrNodes;
}

void balanceTree(NodeBalanced *tracker){
    if(tracker==NULL)
        return 0;
    int heightR = balanceTree(treeBalanced, tracker->right);
    int heightL = balanceTree(treeBalanced, tracker->left);
    if(heightR>heightL)
        tracker->heightBelow = heightR;
    else
        tracker->heightBelow = heightL;
    tracker->balanceFactor = heightR-heightL;
    if(tracker->balanceFactor==2 || tracker->balanceFactor==-2){
        startRotating(treeBalanced, tracker);
    }
    return tracker->heightBelow+1;
}

void addNodeBalancedTree(BBST &tree, char *wordNew){
    if(tree.root==NULL){
        NodeBalanced *newNode = new NodeBalanced;
        strncpy(newNode->word, wordNew, strlen(wordNew));
        newNode->word[strlen(wordNew)] = '\0';
        newNode->left = NULL;
        newNode->parent = NULL;
        newNode->right = NULL;
        tree.root = newNode;
        newNode->number = 1;
        newNode->balanceFactor = 0;
    }else if(tree.root!=NULL){
        NodeBalanced *tracker = tree.root;
        NodeBalanced *previous = tree.root;
        int added = 0;
        while(tracker!=NULL){
            if((tracker->left == previous || tracker->left==NULL) && tracker->right!=NULL && tracker->right!=previous){
                if(!strcmp(wordNew, tracker->word)){
                    tracker->number++;
                    added = 1;
                    break;
                }
                tracker = tracker->right;
            }else if(tracker->left==previous && tracker->right==NULL){
                if(!strcmp(wordNew, tracker->word)){
                    tracker->number++;
                    added = 1;
                    break;
                }
                previous = tracker;
                tracker = tracker->parent;
            }else if(tracker->right == previous){
                previous = tracker;
                tracker = tracker->parent;
            }else if(tracker->left == NULL && tracker->right==NULL){
                if(!strcmp(wordNew, tracker->word)){
                    tracker->number++;
                    added = 1;
                    break;
                }
                previous = tracker;
                tracker = tracker->parent;
            }else if(tracker->left!=previous && tracker->left!=NULL){
                tracker = tracker->left;
            }
        }
        if(added == 0){
            NodeBalanced *newNode = new NodeBalanced;
            strncpy(newNode->word, wordNew, strlen(wordNew));
            newNode->word[strlen(wordNew)] = '\0';
            newNode->left = NULL;
            newNode->right = NULL;
            NodeBalanced *minNode = findMinimum(tree);
            minNode->left = newNode;
            newNode->parent = minNode;
            newNode->number = 1;
            balanceTree(minNode);
        }
    }
}

void buildBalancedTree(BBST &treeBalanced, BST &tree){
    Node *tracker = tree.root;
    Node *previous = tree.root;
    while(tracker!=NULL){
        if((tracker->left == previous || tracker->left==NULL) && tracker->right!=NULL && tracker->right!=previous){
            addNodeBalancedTree(treeBalanced, tracker->word);
            tracker = tracker->right;
        }else if(tracker->left==previous && tracker->right==NULL){
            addNodeBalancedTree(treeBalanced, tracker->word);
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->right == previous){
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left == NULL && tracker->right==NULL){
            addNodeBalancedTree(treeBalanced, tracker->word);
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left!=previous && tracker->left!=NULL){
            tracker = tracker->left;
        }
    }
}


//////////////HASHING//////////////////
struct HashTableEntry{
    HashTableEntry* nextEntry;
    char *word;
    int number;
};

struct HashTable{
    HashTableEntry *entries[26];
};

void searchHashTable(HashTable &hashT, int position, char *word, int number){
    HashTableEntry *tracker = hashT.entries[position];
    if(tracker == NULL){
        HashTableEntry *hte1 = new HashTableEntry;
        hte1->nextEntry = NULL;
        hte1->word = word;
        hte1->number = number;
        hashT.entries[position] = hte1;
    }else{
        while(tracker->nextEntry!=NULL)
            tracker = tracker->nextEntry;
        HashTableEntry *hte1 = new HashTableEntry;
        hte1->nextEntry = NULL;
        hte1->word = word;
        hte1->number = number;
        tracker->nextEntry = hte1;
    }
}

void insertWordsIntoHashTable(BST &tree, HashTable &hashT){
    Node *tracker = tree.root;
    Node *previous = tree.root;
    while(tracker!=NULL){
        if((tracker->left == previous || tracker->left==NULL) && tracker->right!=NULL && tracker->right!=previous){
            char letter = tracker->word[0];
            int position = letter % 97;
            searchHashTable(hashT, position, tracker->word, tracker->number);
            tracker = tracker->right;
        }else if(tracker->left==previous && tracker->right==NULL){
            char letter = tracker->word[0];
            int position = letter % 97;
            searchHashTable(hashT, position, tracker->word, tracker->number);
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->right == previous){
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left == NULL && tracker->right==NULL){
            char letter = tracker->word[0];
            int position = letter % 97;
            searchHashTable(hashT, position, tracker->word, tracker->number);
            previous = tracker;
            tracker = tracker->parent;
        }else if(tracker->left!=previous && tracker->left!=NULL){
            tracker = tracker->left;
        }
    }
}

/*void showHashTable(char letter, HashTable &hashT){
    int position = letter % 97;
    HashTableEntry *tracker = hashT.entries[position];
    while(tracker!=NULL){
        cout<<"Word: "<<tracker->word<<" is met: "<<tracker->number<<" times"<<endl;
        tracker = tracker->nextEntry;
    }
}*/

void findMaxHash(HashTable &hashT){
    HashTableEntry arr10Max[10];
    for(int i = 0; i<10; i++){
        arr10Max[i].nextEntry = NULL;
        arr10Max[i].number = 0;
        arr10Max[i].word = NULL;
    }
    for(int i = 0; i<26; i++){
        HashTableEntry *htep = hashT.entries[i];
        while(htep!=NULL){
            int pos = 10;
            for(int k = 9; k>=0;k--){
                if(htep->number>arr10Max[k].number)
                    pos = k;
                else
                    break;
            }
            if(pos!=10){
                for(int j = 9; j>pos; j--){
                    arr10Max[j] = arr10Max[j-1];
                }
                arr10Max[pos].number = htep->number;
                arr10Max[pos].word = htep->word;
            }
            htep = htep->nextEntry;
        }
    }
    for(int q = 0; q<10; q++){
        cout<<arr10Max[q].word<<" is met "<<arr10Max[q].number<<" times"<<endl;
    }
}

int main(void)
{
    BST tree;
    tree.root = NULL;
    char inputArr[256];
    while(fgets(inputArr, sizeof(inputArr), stdin)!=NULL){
        for(int i = 0, prevCounter = 0; inputArr[i]!='\0'; i++){
            if((inputArr[i]>='A' && inputArr[i]<='Z') || (inputArr[i]>='a' && inputArr[i]<='z')){
                if(inputArr[i]>='A' && inputArr[i]<='Z')
                    inputArr[i]+=32;
                if(inputArr[i+1]=='\0'){
                    char wordNew[32];
                    int counter = 0;
                    while(prevCounter!=i){
                        wordNew[counter++] = inputArr[prevCounter++];
                    }
                    wordNew[counter] = '\0';
                    prevCounter++;
                    findPosition(tree, wordNew);
                }
            }else if(prevCounter==i){
                prevCounter++;
            }else{
                char wordNew[32];
                int counter = 0;
                while(prevCounter!=i){
                    wordNew[counter++] = inputArr[prevCounter++];
                }
                wordNew[counter] = '\0';
                prevCounter++;
                findPosition(tree, wordNew);
            }
        }
    }
    findMaximum10BST(tree);
    ////////BALANCED BST////////
    BBST treeBalanced;
    treeBalanced.root = NULL;
    buildBalancedTree(treeBalanced, tree);
    cout<<"Searched with BBST: "<<endl;
    findMaximum10BBST(treeBalanced);
    ////////HASHING/////////
    cout<<"Searched with HashTable: "<<endl;
    HashTable hashT;
    for(int i = 0; i<26; i++)
        hashT.entries[i] = NULL;
    insertWordsIntoHashTable(tree, hashT);
    findMaxHash(hashT);
    return 0;
}
