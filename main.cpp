#include <iostream>
#include "Btree.h"
#include <vector>
#include <stack>
using namespace std;

int main(int argc, char const *argv[]) {
  BTree T(3);
  BTree T2(4);
  
  int list[] = {30,20,62,110,140,15,65,136,150,120,
	  40,132,19,128,138,100,16,145,70,42,
	  69,43,26,60,130,50,18,7,36,58,
	  22,41,59,57,54,33,75,124,122,123};

  int delist[] = { 40,  132,  19,  128,  138,  100,  16,  145,  70,  42,
	  22, 41,  62,  110,  140,  15,  65, 124, 122, 123,
	  30,  20,  59, 57, 54, 33, 75, 136,  150,  120,
	  69,  43,  26,  60,  130,  50,  18,  7,  36,  58
  };

  for (size_t i = 0; i < 40; i++) {
	  
    T.insertBT(list[i]);
    T.inorderBT();
	
  }

  for (size_t i = 0; i < 10; i++)
  {
	  T.deleteBT(delist[i]);
	  T.inorderBT();
  }
 


  return 0;
}
