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


	if (delete_key == key[i]) {
		for (; i < nokey; i++) {
			key[i] = key[i+1];
		}
		key[i] = 0;
	}

	nokey--;

	// 이 함수는 단말 노드에서만 사용되므로 포인터를 옮길 걱정이 없다.

}

int Node::getKeyNumber(){
  int total_key = 0;

  total_key += nokey;

  if(subtree[0] == NULL){
    return total_key;
  }

  for (size_t i = 0; i < nokey+1; i++) {
    total_key += subtree[i]->getKeyNumber();
  }

  return total_key;


}

// 노드 합병 시 y 노드의 중간값 삭제를 해주는 함수.
void Node::deleteIntermediate(int intermediate) {
	for (size_t i = intermediate; i < nokey; i++)
	{
		key[i] = key[i + 1];
		subtree[i] = subtree[i + 1];
	}

	subtree[nokey] = NULL;
	key[nokey] = 0;
	nokey--;
}
