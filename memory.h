#ifndef _MEMORY
#define _MEMORY

#include "performer.h"
using namespace std;

void MemoryAccess(){
  if (m.rn == -1) return;
  if (m.t || m.rn == -1) w = m;
  else {
    if (m.type)
	  toChar(m.address, m.size, reg[m.rn]);
    else reg[m.rn] = CharToInt(m.address, m.size);
	FF m1;
	w = m1;
  }
  m.rn = -1;
  //m.pop();
}

#endif
