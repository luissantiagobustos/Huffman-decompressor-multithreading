#include "huffmanTree.h"

int main() {
  huffmanTree obj; 
  obj.readFile();
  
  //inputFile methods
  obj.sortVector();
  obj.callTree();

  //compressedFile methods
  obj.getMessageThreads();
  obj.printMessage();
}
