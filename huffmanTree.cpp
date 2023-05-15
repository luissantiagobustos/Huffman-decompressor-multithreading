#include "huffmanTree.h"

huffmanTree::huffmanTree(){
  totalSymbols = 0;
  root = new rootNode;
}

void huffmanTree::readFile(){
  string str;
  getline(cin,str);
  int numberRows = stoi(str); //it gives us how many char we are working with
  
  // gets first line and parse frq and symbol, just we just have frequence of one digit thats why we use str[0] 
  for(int i = 0; i < numberRows; ++i){
    getline(cin,str);
    char symbol = str[0];
    int freq = str[2] - '0';
    node* temp = new node(symbol,freq);
    totalSymbols += freq;
    priorityQueue.push_back(temp);
  }

  for(int i = 0; i < numberRows; ++i){
    getline(cin,str);
    int j = 0;
    vector<char> sym;
    vector<int> pos;
    while(str[j] != ' '){
      sym.push_back(str[j]);
      j++;
    }
    while(j < str.length()){
      if(str[j] != ' '){
        bool status = false;
        int t1;
        int t2;
        int result;
        t1 = str[j] - '0';
        j++;
        if(j < str.length()){
          // Checks if position has 2 digits Note that every position has a maximun of two digits, so we can hardcode it.
          if(str[j] != ' '){
            status = true;
            t2 = str[j] - '0';
            t1 = t1 * 10;
            j++;
          }
        }
        result = t1;
          if(status){
            result += t2;
          }
        pos.push_back(result);
      }
      j++;
    }
    root->symbols.push_back(sym);
    root->positions.push_back(pos);
  }
  root->message = new char[totalSymbols];

  }




void huffmanTree::printVector(){
  // function to check how our vector is behaving
  for(int i = 0; i < priorityQueue.size(); ++i){
    cout << "SYMBOL = " << priorityQueue[i]->symbol <<  " FREQ = ";
    cout << priorityQueue[i]->freq << endl;
  }
  cout << endl;
}

void huffmanTree::sortVector(){
  // using quick sort since it is really efficient
  quickSort(0, priorityQueue.size()-1);
}

void huffmanTree::swap(node* a, node* b){
  char tempSymbol = a->symbol;
  int tempFreq = a->freq;

  a->symbol = b->symbol;
  a->freq = b->freq;
  b->symbol = tempSymbol;
  b->freq = tempFreq;
}

// partition logic gotten from geeksforgeeks website
int huffmanTree::partition(int start, int end){
    
    int pivotFreq = priorityQueue[start]->freq;
    char pivotSmybol = priorityQueue[start]->symbol;
  
 
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if(priorityQueue[i]->freq < pivotFreq || ((priorityQueue[i]->freq == pivotFreq) && (priorityQueue[i]->symbol <= pivotSmybol)))
            count++;
    }
 
    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(priorityQueue[pivotIndex], priorityQueue[start]);
 
    // Sorting left and right parts of the pivot element
    int i = start, j = end;
 
    while (i < pivotIndex && j > pivotIndex) {
 
        while (priorityQueue[i]->freq < pivotFreq || ((priorityQueue[i]->freq == pivotFreq) && (priorityQueue[i]->symbol <= pivotSmybol))) {
            i++;
        }
 
        while (priorityQueue[j]->freq > pivotFreq || ((priorityQueue[j]->freq == pivotFreq) && (priorityQueue[j]->symbol > pivotSmybol))) {
            j--;
        }
 
        if (i < pivotIndex && j > pivotIndex) {
            swap(priorityQueue[i++], priorityQueue[j--]);
        }
    }
    return pivotIndex;
}

void huffmanTree::quickSort(int start, int end){
  if(start >= end)  //base case
    return;
  int p = partition(start,end);
  //sorting left  part
  quickSort(start, p - 1);
  //sorting right part
  quickSort(p + 1, end);
}

node* huffmanTree::popFront(){
  node* temp = new node(priorityQueue[0]->symbol, priorityQueue[0]->freq, priorityQueue[0]->left, priorityQueue[0]->right);
  priorityQueue.erase(priorityQueue.begin());
  return temp;
}

void huffmanTree::insertNode(node* temp){
  priorityQueue.push_back(temp);
  int end = priorityQueue.size() - 1;
  while(end > 0 && ((temp->freq < priorityQueue[end - 1]->freq) || ((temp->freq == priorityQueue[end - 1]->freq) && (temp->symbol <= priorityQueue[end - 1]->symbol)))){
    priorityQueue[end] = priorityQueue[end - 1];
    end--;
  }
  priorityQueue[end] = temp;
}

void huffmanTree::callTree(){
  if(isEmpty()){
    cout << "array is empty please insert inputfile" << endl;
    return;
  }
  while(priorityQueue.size() > 1){
    node* temp1 = popFront();
    node* temp2 = popFront();
    node* newNode = new node('\n', temp1->freq + temp2->freq, temp1, temp2);
    insertNode(newNode);
  }
  root->curr = popFront();
  int array[totalSymbols-1];  //max height of a huffman tree is the number of symbols - 1
  printTree(root->curr,0,array);
}

bool huffmanTree::isEmpty(){
  if(priorityQueue.size() == 0) return true;
  return false;
}

void huffmanTree::printTree(node* curr, int count, int arr[]){
  if(curr->left != nullptr){
    arr[count] = 0;
    printTree(curr->left,count + 1, arr);
  }
  if(curr->right != nullptr){
    arr[count] = 1;
    printTree(curr->right, count + 1, arr);
  }
  if(curr->left == nullptr && curr->right == nullptr){
    int* newArray = new int[count];
    for(int i = 0; i < count; ++i)
      newArray[i] = arr[i];
    curr->arr = newArray;
    curr->sizeArray = count;
    root->printingTree[curr->symbol] = curr;
  }
}

void huffmanTree::printTreeFinal(){
  for(int i = 0 ; i < root->symbolsOrder.size(); ++i){
    char symb = root->symbolsOrder.at(i);
    cout << "Symbol: " << symb << ", Frequency: ";
    cout << root->printingTree[symb]->freq << ", Code: ";
    for(int j = 0; j <  root->printingTree[symb]->sizeArray; ++j){
      cout << root->printingTree[symb]->arr[j];
    }
    cout << endl;
  }
}

void huffmanTree::readCompressedFile(string fileName){
  ifstream input;
  input.open(fileName);
  string str;

  while(getline(input,str)){
    int j = 0;
    vector<char> sym;
    vector<int> pos;
    while(str[j] != ' '){
      sym.push_back(str[j]);
      j++;
    }
    while(j < str.length()){
      if(str[j] != ' '){
        bool status = false;
        int t1;
        int t2;
        int result;
        t1 = str[j] - '0';
        j++;
        if(j < str.length()){
          // Checks if position has 2 digits Note that every position has a maximun of two digits, so we can hardcode it.
          if(str[j] != ' '){
            status = true;
            t2 = str[j] - '0';
            t1 = t1 * 10;
            j++;
          }
        }
        result = t1;
          if(status){
            result += t2;
          }
        pos.push_back(result);
      }
      j++;
    }
    root->symbols.push_back(sym);
    root->positions.push_back(pos);
  }
  root->message = new char[totalSymbols];
  input.close();
}

void huffmanTree::printCompressedFile(){
  for(int i = 0; i < root->symbols.size(); i++){
    for(int j = 0; j < root->symbols[i].size(); j++){
      cout << root->symbols[i][j];
    }
    cout << " ";
    for(int j = 0; j < root->positions[i].size(); j++){
      cout << root->positions[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

char getSymbolFromTree(node* root, const vector<char>& symbols, int count){
  if(root->left == nullptr && root->right == nullptr){
    return root->symbol;
  }
  else if(symbols[count] == '0'){
    return getSymbolFromTree(root->left, symbols, count + 1);
  }
  else{
    return getSymbolFromTree(root->right, symbols, count + 1);
  }
}

void* getSymbol(void* root_void_ptr){
  rootNode* root_ptr = (rootNode*) root_void_ptr;
  // continuation of sempahore to close it and give accesss to another thread to continue its syncronized computation. critical section
  int k = root_ptr->id;
  char symbol = getSymbolFromTree(root_ptr->curr, root_ptr->symbols[k], 0);
  sem_post(&root_ptr->semaphore);
  cout << "Symbol: " << symbol << ", Frequency: ";
  cout << root_ptr->printingTree[symbol]->freq << ", Code: ";
  for(int j = 0; j <  root_ptr->printingTree[symbol]->sizeArray; ++j){
    cout << root_ptr->printingTree[symbol]->arr[j];
   }
  cout << endl;
  for(int i = 0; i < root_ptr->positions[k].size(); ++i){
    int index = root_ptr->positions[k].at(i);
    root_ptr->message[index] = symbol;
  }
  return NULL;
}

void huffmanTree::getMessageThreads(){
  const int NTHREADS = root->symbols.size();
  pthread_t tid[NTHREADS];


  sem_init(&root->semaphore, 0,1);
  
  for(int i = 0; i < NTHREADS; ++i){
// makes sure this CRITICAL SECTION is only access by one thread at the time so we avoid memory problems. Notice how k is the local variable for the getSymbol() function which each thread individually executes to retrieve the symbols and positions data. This syncronization is the most optimal and we do not need any sleeping functions.
    sem_wait(&root->semaphore);
    root->id = i;
    if(pthread_create(&tid[i],NULL,getSymbol,(void*)root)){
      cout << "Error creating the thread" << endl;
      return;
    }
  }
  for(int i = 0; i < NTHREADS; ++i)
    pthread_join(tid[i], NULL);

  sem_destroy(&root->semaphore);
}

void huffmanTree::printMessage(){
  cout << "Original message: ";
  for(int i = 0; i < totalSymbols; ++i){
    cout << root->message[i];
  }
}

huffmanTree::~huffmanTree(){
  /// empty destructor
}
