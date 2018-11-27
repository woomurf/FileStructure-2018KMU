#include "Btree.h"
#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
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
	  //p를 초기화하여 쓰는 이유는 p의 parent Node가 p를 가르키고 있기 때문인데,
	  //새로운 노드를 만들어서 넣으면 parent가 새로운 노드를 가르키게 하는 작업이 성가시다.
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

void BTree::deleteBT(int key) {
	Node* x = root;
	stack<Node*> parent;
	Node* y = x;
	Node* bsNode = NULL;
	Node* old_x = NULL;
	int underflowLine = ceil(mSize / 2 + mSize % 2) - 1;

	int i;
	do {
		i = 1;
		while (i <= x->nokey && key > x->key[i]) {
			i++;
		}

		if (i <= x->nokey && key == x->key[i]) {// 삭제할 키를 발견함
			break;
		}
		parent.push(x);
	} while ((x = x->subtree[i - 1]) != NULL);

	if (x == NULL) { return; } // 삭제할 키 발견 못함 트리 내부에 없음.

	if (x->subtree[0] != NULL) { // internal node

		Node* internalNode = x;
		parent.push(x);

		
    int leftKey = x->subtree[i-1]->getKeyNumber();
    int rightKey = x->subtree[i]->getKeyNumber();

    if(rightKey > leftKey){
      x = x->subtree[i]; // x노드의 오른쪽 서브트리
  		do {
  			parent.push(x);
  		} while ((x = x->subtree[0]) != NULL);  // 왼쪽 끝으로 내려간다    ----> 오른쪽 서브트리에서 가장 작은 값을 찾는다.
    }
	else {
		x = x->subtree[i - 1];
		do {
			parent.push(x);
		} while ((x = x->subtree[x->nokey]) != NULL);
	}


		if (x == NULL) {
			x = parent.top();
			parent.pop();

			int temp = internalNode->key[i];
			if (rightKey > leftKey) {

				internalNode->key[i] = x->key[1];
				x->key[1] = temp;  // 후행키와 키값을 교환한다.
			}
			else {
				internalNode->key[i] = x->key[x->nokey];
				x->key[x->nokey] = temp;  // 후행키와 키값을 교환한다.
			}
			
		}
	}

	bool finished = false;
	x->deleteKey(key);

	if(!parent.empty()){
		y = parent.top();
		parent.pop();
	}

	do {
		if (x == y || !(x->nokey < underflowLine)) {
			finished = true;

		}
		else {

			bsNode = getBsNode(x, y);


			int m = 0;
			if (left) {
				while (m <= y->nokey && !(y->subtree[m] == bsNode && y->subtree[m+1] == x)) {
					m++;
				}
			}
			else {
				while (m <= y->nokey && !(y->subtree[m] == x && y->subtree[m+1] == bsNode)) {
					m++;
				}
			}
			m++;
			int intermediate_y = y->key[m];


			/*
			키 재분배
			*/

			if (bsNode->nokey - 1 >= underflowLine) { // bsNode가 키를 나눠줘도 여유있는 경우 -> 키 재분배
				Node* tempNode = new Node(ceil(mSize*1.5) + 1);
      

				// tempNode에 bsNode, x Node, y 값 복사넣기
				if (left) {  // bsNode 가 x노드의 왼쪽에 있는 노드라면
					int i;
					for (i = 1; i < bsNode->nokey + 1; i++) { // copy bsNode
						tempNode->key[i] = bsNode->key[i];
						tempNode->subtree[i - 1] = bsNode->subtree[i - 1];
					}
					tempNode->subtree[i - 1] = bsNode->subtree[i - 1];

					tempNode->key[i] = intermediate_y;  // copy key_y
					i++;
					int j;
					for (j = 0; j < x->nokey; j++) {  // copy x node
						tempNode->key[i] = x->key[j+1];
						tempNode->subtree[i - 1] = x->subtree[j];
						i++;
					}
					tempNode->subtree[i - 1] = x->subtree[j];
				}
				else {
					int i;
					for (i = 1; i < x->nokey; i++) {  // copy x node
						tempNode->key[i] = x->key[i];
						tempNode->subtree[i - 1] = x->subtree[i - 1];
					}
					tempNode->subtree[i - 1] = x->subtree[i - 1];

					tempNode->key[i] = intermediate_y;  // copy key_y
					i++;

					int j;
					for (j = 0; j < bsNode->nokey; j++) { // copy bsNode
						tempNode->key[i] = bsNode->key[j+1];
						tempNode->subtree[i - 1] = bsNode->subtree[j];
						i++;
					}
					tempNode->subtree[i - 1] = bsNode->subtree[j];
				}

				//tempNode에 있는 값들 재분배하기 -> bsNode에 하나 덜주고 x node에 하나 더준다.
				if (left) {
					bsNode->key.clear();
					bsNode->key.resize(bsNode->nodeSize);
					bsNode->subtree.clear();
					bsNode->subtree.resize(bsNode->nodeSize);
					int old_nokey = bsNode->nokey;
					bsNode->nokey = 0;


					int i;
					for (i = 0; i < old_nokey - 1; i++)
					{
						bsNode->key[i + 1] = tempNode->key[i + 1];
						bsNode->subtree[i] = tempNode->subtree[i];
						bsNode->nokey++;
					}
					bsNode->subtree[i] = tempNode->subtree[i];

					y->key[m] = tempNode->key[i + 1];
					i++;

					x->key.clear();
					x->key.resize(x->nodeSize);
					x->subtree.clear();
					x->subtree.resize(x->nodeSize);
					old_nokey = x->nokey;
					x->nokey = 0;

					int j;
					for (j = 0; j < old_nokey + 1; j++)
					{
						x->key[j + 1] = tempNode->key[i + 1];
						x->subtree[j] = tempNode->subtree[i];
						x->nokey++;
						i++;
					}
					x->subtree[j] = tempNode->subtree[i];

				}
				else {
					x->key.clear();
					x->key.resize(x->nodeSize);
					x->subtree.clear();
					x->subtree.resize(x->nodeSize);
					int old_nokey = x->nokey;
					x->nokey = 0;

					int i;
					for (i = 0; i < old_nokey + 1; i++)
					{
						x->key[i + 1] = tempNode->key[i + 1];
						x->subtree[i] = tempNode->subtree[i];
						x->nokey++;

					}
					x->subtree[i] = tempNode->subtree[i];

					y->key[m] = tempNode->key[i + 1];
					i++;

					bsNode->key.clear();
					bsNode->key.resize(bsNode->nodeSize);
					bsNode->subtree.clear();
					bsNode->subtree.resize(bsNode->nodeSize);
					old_nokey = bsNode->nokey;
					bsNode->nokey = 0;

					int j;
					for (j = 0; j < old_nokey - 1; j++)
					{
						bsNode->key[j + 1] = tempNode->key[i + 1];
						bsNode->subtree[j] = tempNode->subtree[i];
						bsNode->nokey++;
						i++;
					}
					bsNode->subtree[j] = tempNode->subtree[i];


				}

				finished = true;

			}

			/*
			노드 합병
			*/

			else {
        

				if (left) {
					int i = bsNode->nokey;
					i++;

					bsNode->key[i] = intermediate_y;
					bsNode->nokey++;
					i++;

					int j;
					for (j = 0; j < x->nokey; j++)
					{
						bsNode->key[i] = x->key[j + 1];
						bsNode->subtree[i - 1] = x->subtree[j];
						bsNode->nokey++;
						i++;
					}
					bsNode->subtree[i - 1] = x->subtree[j];

					y->deleteIntermediate(m);

				}
				else {
					int i = x->nokey;
					i++;

					x->key[i] = intermediate_y;
					x->nokey++;
					i++;

					int j;
					for (j = 0; j < bsNode->nokey; j++)
					{
						x->key[i] = bsNode->key[j + 1];
						x->subtree[i - 1] = bsNode->subtree[j];
						x->nokey++;
						i++;
					}
					x->subtree[i - 1] = bsNode->subtree[j];

					y->deleteIntermediate(m);
				}

				old_x = x;    // x = y를 그냥 해버리면 x,y 둘다 빈 노드가 될 수 있음.
				x = y;		  // 그 상황이 트리의 레벨이 줄어드는 상황일 때 문제가 발생하여 old_x를 사용한다.
				
				


				if (!parent.empty()) {
					y = parent.top();
					parent.pop();
				}
				else {
					finished = true;
				}
			}
		}


	}while (!finished);

	if (y == NULL || y->nokey == 0) {
		if (left) {
			if (bsNode != NULL) {
				root = bsNode;
			}
			else {
				root = old_x;
			}
		}
		else {
			root = old_x;
		}
		delete y;
	}

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


Node* BTree::getBsNode(Node* x, Node* parent) {
	Node* bsNode = NULL;
	int underflowLine = ceil(mSize / 2 + mSize % 2) - 1;
	bool keyDis = true;

	// x 노드가 parent노드의 어느 subtree인지 알아낸다.

	int i = 0;
	for (i = 0; i < parent->nokey; i++)
	{
		if (parent->subtree[i] == x) {
			break;
		}
	}

	if (i == 0) {

		bsNode = parent->subtree[1];
		left = false;
	}
	else if (i == parent->nokey) {
		 bsNode = parent->subtree[parent->nokey-1];
		 left = true;
	}
	else {

		Node* temp1 = parent->subtree[i - 1];
		Node* temp2 = parent->subtree[i + 1];

		if (temp1->nokey > temp2->nokey) {  // 두 형제 노드 중 키값을 더 많이 가지고 있는 노드 선택
			bsNode = temp1;
			left = true;
		}
		else {
			bsNode = temp2;
			left = false;
		}
	}

	return bsNode;
}
