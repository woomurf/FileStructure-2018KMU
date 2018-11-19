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

  std::vector<int> key;
  std::vector<Node*> subtree;

  Node(int size){
    nodeSize = size;
    nokey = 0;
    key.push_back(0); // BT insert 알고리즘을 위해 key vector의 첫 부분을 쓰지않고 index number를 1 부터 사용한다.
  }

  void insertKey(int key);
  Node* firsthalf();
  Node* secondhalf();

};

class BTree{
  Node* root;
  stack<Node*> parents;
  int mSize = 0;

public:
  BTree(int size){
    root = new Node(size);
    mSize = size;
  }

  void insertBT(int key);
  void deleteBT(int key);
  void inorderBT();
}
