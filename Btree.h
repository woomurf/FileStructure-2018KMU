#include <vector>
#include <stack>
using namespace std;

class Node{

public:
  int nodeSize;
  int nokey;
  int indexSubtree = 1;

  vector<int> key;
  vector<Node*> subtree;

  Node(int size){
    nodeSize = size;
    nokey = 0;
    key.resize(size,0);
    subtree.resize(size,0);
  }

  void insertKey(int key);
  void deleteKey(int key);
  Node* secondhalf();
  int getCenter();
  int getIndexSubtree();
  int getKeyNumber();
  void deleteIntermediate(int intermediate);

};




class BTree{
  int mSize = 0;

  void inorderBTInner(Node* root);

public:
  Node* root;

  BTree(int size){
    root = new Node(size);
    mSize = size;
  }

  void insertBT(int key);
  void deleteBT(int key);
  void inorderBT();
  bool left = true;   // bsNode가 x 노드의 왼쪽에 있는지 오른쪽에 있는지 판별하는 변수
  Node* getBsNode(Node* x, Node* parent);
  
};
