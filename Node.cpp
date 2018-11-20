#include "Btree.h"
#include <vector>
using namespace std;

void Node::insertKey(int insert_key){
  int i = 1;

  // key가 node의 key보다 작을 경우를 찾는다. p0이거나, kn과 kn+1 사이에 있는 경우를 찾을 수 있음.
  while(i <= nokey && insert_key > key[i]){
    i += 1;
  }

  vector<int>::iterator it = key.begin();

  for (int j = 0; j < i; j++) {
	  it++;
  }

  key.insert(it,insert_key);

  //포인터들이 한자리 씩 밀려난다.
  for (int j = nokey+1; j > i; j--) {
    subtree[j] = subtree[j-1];
  }

  indexSubtree = i;

  nokey++;
}

Node* Node::firsthalf(){
  Node* p = new Node(nodeSize-1);  // tempNode이므로 기존 노드들 보다 크기가 1 크기 때문에 -1을 해준다.

  for (size_t i = 1; i < nodeSize/2; i++) {
    p->key[i] = key[i];
    p->subtree[i] = subtree[i];
	p->nokey++;
  }

  return p;

}

Node* Node::secondhalf(){
  Node* p = new Node(nodeSize-1);

  vector<int>::iterator keyIt = p->key.begin();
  vector<Node*>::iterator stIt = p->subtree.begin();

  keyIt++;

  // nodeSize/2 의 index를 가진 녀석은 center값이라 위로 올라갈 예정
  for (size_t i = nodeSize/2+1; i < nodeSize; i++) {
	p->key.insert(keyIt, key[i]);
    p->subtree.insert(stIt,subtree[i]);
	p->nokey++;
  }

  return p;
}

int Node::getCenter(){
  return key[nodeSize/2];
}

int Node::getIndexSubtree() {
	int i = indexSubtree;
	indexSubtree = 1;
	return i;
}