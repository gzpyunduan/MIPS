#ifndef _MEMORY
#define _MEMORY

#include "performer.h"
using namespace std;

void MemoryAccess(){
  if (m.empty()) return;
  FF tmp = m.front();
  if (tmp.t || tmp.rn == -1) w.push(tmp);
  else {
    if (tmp.type)
	  toChar(tmp.address, tmp.size, reg[tmp.rn]);
    else reg[tmp.rn] = CharToInt(tmp.address, tmp.size);
	FF tmp1;
	w.push(tmp1);
  }
}

#endif
