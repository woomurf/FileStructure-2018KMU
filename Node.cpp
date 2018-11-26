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

  int i = 1;
  for (i = 1; i < nodeSize/2; i++) {
    p->key[i] = key[i];
    p->subtree[i-1] = subtree[i-1];
	p->nokey++;
  }
  p->subtree[i - 1] = subtree[i - 1];

  return p;

}

Node* Node::secondhalf(){
  Node* p = new Node(nodeSize-1);


  // nodeSize/2 의 index를 가진 녀석은 center값이라 위로 올라갈 예정
  int j = 1;
  int i = 0;
  for (i = nodeSize/2+1; i < nodeSize; i++) {
	p->key[j] = key[i];
    p->subtree[j-1] = subtree[i-1];
	p->nokey++;
	j++;

  }
  p->subtree[j - 1] = subtree[i - 1];

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

void Node::deleteKey(int delete_key) {

	int i = 1;
	while (i <= nokey && delete_key > key[i] ) {    
		i++;
	}

	vector<int>::iterator it = key.begin();
	for (size_t j = 0; j < i; j++)
	{
		it++;
	}

	if (delete_key == key[i]) {
		key.erase(it);   // 해당 원소 삭제
	}
	nokey--;

	// 이 함수는 단말 노드에서만 사용되므로 포인터를 옮길 걱정이 없다.

}