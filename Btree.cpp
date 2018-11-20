#include "Btree.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;


void BTree::insertBT(int key){
  Node* p = root;
  Node* x = new Node(mSize);
  Node* y = NULL;
  stack<Node*> parents;
  bool overflowCheck = false;

  if(p->nokey == 0){
    p->insertKey(key);
    return;
  }
  // p 노드 안에서 키값들을 비교 한 후, 내려간다.
  int i;
  do {
    i = 1;

    // key가 node의 key보다 작을 경우를 찾는다. p0이거나, kn과 kn+1 사이 에 있는 경우를 찾을 수 있음.
    while(i <= p->nokey && key > p->key[i]){
      i += 1;
    }

    if(i <= p->nokey && key == p->key[i]){
      // key가 node에 있는 key값과 같은 경우
      return;
    }
    else{
      parents.push(p);
    }
  } while((p = p->subtree[i-1])!=NULL); // 아래로 내려간다. p 가 null일 때까지.


  p = parents.top();  // p가 null일 때까지 내려갔으므로 pop을 하여 leaf 노드로 간다.
  parents.pop();

  bool finished = false;

  do {
    if(p->nokey < mSize-1){
      // key의 갯수가 m-1보다 작아야 한개를 더 넣어도 overflow되지 않는다.
      // 적당한 곳에 넣는다.
      //v.insert(v.begin() + i, valueToInsert);
      p->insertKey(key);
      finished = true;

      if(overflowCheck){

        // 적당한 곳위치 => i를 찾아온다면..
		  int j = p->getIndexSubtree();
		  p->subtree[j] = y;
      }
    }
    else{
      // overflow가 난 경우
      Node* tempNode = new Node(p->nodeSize+1);

      tempNode->key = p->key;

	  for (int i = 0; i < p->nodeSize; i++) {	  // 값만 받아온다. tempNode->subtree = p->subtree 라고 하면 subtree를 그대로 가져와서 size가 작다.
		  tempNode->subtree[i] = p->subtree[i];
	  }

	  tempNode->nokey = p->nokey;
      tempNode->insertKey(key);

      key = tempNode->getCenter();
	  int j = tempNode->getIndexSubtree();

	  if (overflowCheck) {
		  Node* y_old = y;
		  tempNode->subtree[j] = y_old;
	  }

	  //p를 초기화 하여 tempNode의 절반(작은 부분)을 넣어준다.
	  //p를 초기화하여 쓰는 이유는 p의 parent Node가 p를 가르키고 있기 때문인데, 새로운 노드를 만들어서 넣으면 parent가 새로운 노드를 가르키게 하는 작업이 성가시다.
	  p->key.clear();
	  p->key.resize(p->nodeSize);
	  p->subtree.clear();
	  p->subtree.resize(p->nodeSize);
	  p->nokey = 0;

	  int sub;
	  for (sub = 1; sub < tempNode->nodeSize / 2; sub++) {
		  p->key[sub] = tempNode->key[sub];
		  p->subtree[sub - 1] = tempNode->subtree[sub - 1];
		  p->nokey++;
	  } 
	  p->subtree[sub-1] = tempNode->subtree[sub-1];

	  
		y = new Node(mSize);
		y = tempNode->secondhalf(); // 큰 부분
	  
 


      overflowCheck = true;

    }

    if(!parents.empty()){
      p = parents.top();
      parents.pop();
    }
    else if(!finished){
      // tree의 레벨이 하나 증가한다.
      Node* T = new Node(mSize);
      T->key[1] = key;
	  T->nokey = 1;
      T->subtree[0] = p;
      T->subtree[1] = y;
	  root = T;
      finished = true;

    }
  } while(!finished);


}

void BTree::inorderBT(){
  inorderBTInner(root);
  cout << endl;
}

void BTree::inorderBTInner(Node* root){

  if(root == NULL){
    return;
  }
  else{
	  int i;
    for ( i = 0; i < root->nokey; i++) {
      inorderBTInner(root->subtree[i]);
      if(i != mSize){
        cout << root->key[i+1] << ' ';
      }
    }
	if (i < mSize) {
		inorderBTInner(root->subtree[i]);
	}
  }
}
