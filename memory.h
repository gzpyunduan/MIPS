#ifndef _MEMORY
#define _MEMORY

#include "scanner.h"
#include "parser.h"
#include "performer.h"
using namespace std;

int CharToInt(int pos, int size){
  int a;
  for (int i = 0; i < size; i++)
    a += Data[pos + i] << (i * 8);
  return a;
}

void MemoryAccess(){
  if (m.empty()) return;
  MA tmp = m.front();
  if (tmp.type)
    toChar(Data, tmp.address, tmp.size, reg[tmp.rn]);
  else reg[tmp.rn] = CharToInt(tmp.address, tmp.size);
  m.pop();
}

#endif
