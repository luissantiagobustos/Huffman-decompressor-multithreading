#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h> 
#include <thread>
#include <map>
#include <stdlib.h>
#include <semaphore.h>

using namespace std;

struct node{
  node(char s, int f, node* l = nullptr, node* r = nullptr){
    symbol = s;
    freq = f;
    left = l;
    right = r;
  }
  char symbol;
  int freq;
  node* left;
  node* right;
  int* arr;
  int sizeArray;
};
// node where will be passed to the threads to retrieve information of each symbol to store in the massage array
struct rootNode{
  node* curr;
// vectors to store each n character for each n thread
  vector<vector<char>> symbols;
  vector<vector<int>> positions;
  vector<char> symbolsOrder;
  map<char,node*> printingTree;
  int id;
  char* message;
  sem_t semaphore;
};

class huffmanTree{
private:
  vector<node*> priorityQueue;
  int totalSymbols;
  map<char,node*> printingTree;
public:
  rootNode* root;
  huffmanTree();
  void readFile();
  void printVector();
  void sortVector();
  void quickSort(int,int);
  int partition(int,int);
  void swap(node*,node*);
  node* popFront();
  void insertNode(node*);
  bool isEmpty();
  void callTree();
  void printTree(node*,int,int[]);
  void readCompressedFile(string);
  void printCompressedFile();
  void getMessageThreads();
  void printMessage();
  void printTreeFinal();
  ~huffmanTree();
};
