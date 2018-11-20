#include <vector>
#include <stack>
using namespace std;

class Node{

public:
  bool fullflag = false;
  int nodeSize;
  int nokey;
  bool overflow = false;
  bool underflow = false;

  vector<int> key;
  vector<Node*> subtree;

  Node(int size){
    nodeSize = size;
    nokey = 0;
    key.reserve(size);
    subtree.reserve(size);
  }

  void insertKey(int key);
  Node* firsthalf();
  Node* secondhalf();
  int getCenter();

};




class BTree{
  Node* root;
  stack<Node*> parents;
  int mSize = 0;

  void inorderBTInner(Node* root);

public:
  BTree(int size){
    root = new Node(size);
    mSize = size;
  }

  void insertBT(int key);
  void deleteBT(int key);
  void inorderBT();
};
