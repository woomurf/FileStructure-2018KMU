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
  Node* firsthalf();
  Node* secondhalf();
  int getCenter();
  int getIndexSubtree();

};




class BTree{
  Node* root;
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
  bool left = true;   // bsNode�� x����� ���ʿ� �ִ� �������, �����ʿ� �ִ� ������� ����� ����
  Node* getBsNode(Node* x, Node* parent);
};
