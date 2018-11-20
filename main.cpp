#include <iostream>
#include "Btree.h"
#include <vector>
#include <stack>
using namespace std;

int main(int argc, char const *argv[]) {
  BTree T(3);
  int list[] = {30,20,62,110,140,15,65,136,150,120};

  for (size_t i = 0; i < 10; i++) {
    T.insertBT(list[i]);
    T.inorderBT();
  }

  return 0;
}
