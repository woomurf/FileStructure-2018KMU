#include "Btree.h"
#include <iostream>
#include <vector>
#include <stack>
using namespace std;


void BTree::insertBT(int key){
  Node* p = root;
  Node* x;
  Node* y;
  bool overflowCheck = false;

  // p 노드 안에서 키값들을 비교 한 후, 내려간다.
  do {
    int i = 1;

    // key가 node의 key보다 작을 경우를 찾는다. p0이거나, kn과 kn+1 사이에 있는 경우를 찾을 수 있음.
    while(i <= p->nokey && key > p->key[i]){
      i += 1;
    }

    if(i <= p->nokey && key == p->key[i]){
      // key가 node에 있는 key값과 같은 경우
      return;
    }
    else{
      stack.push(p);
    }
  } while(p = p->subtree[i-1]); // 아래로 내려간다. p 가 null일 때까지.

  p = stack.pop();  // p가 null일 때까지 내려갔으므로 pop을 하여 leaf 노드로 간다.

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
        p->subtree[i-1] = x;
        p->subtree[i] = y;
      }
    }
    else{
      // overflow가 난 경우
      Node* tempNode = new Node(p->nodeSize+1);

      tempNode->key = p->key;
      tempNode->subtree = p->subtree;
      tempNode->insertKey(key);

      key = tempNode->getCenter();

      x = tempNode->fristhalf(); // 작은 부분
      y = tempNode->secondhalf(); // 큰 부분

      overflowCheck = true;

    }

    if(!stack.empty()){
      p = stack.pop();
    }
    else{
      // tree의 레벨이 하나 증가한다.
      Node* T = new Node(mSize);
      T->key[1] = key;
      T->subtree[0] = p;
      T->subtree[1] = y;
      finished = true;

    }
  } while(!finished);



}

void Node::insertKey(int insert_key){
  int i = 1;

  // key가 node의 key보다 작을 경우를 찾는다. p0이거나, kn과 kn+1 사이에 있는 경우를 찾을 수 있음.
  while(i <= nokey && insert_key > key[i]){
    i += 1;
  }

  for(; i < nodeSize; i++){
    subtree[i+1] = subtree[i];
  }



}
