#ifndef _WRITE
#define _WRITE

#include "memory.h"

void WriteBack(){
  if (w.rn == -1) return;
  if (w.rn == 42) {
	reg[31] = ra;
	reg[34] = w.ans1;
  }
  else {
	reg[w.rn] = w.ans1;
	if (w.rn == 32) reg[33] = w.ans2;
  }
  w.rn = -1;
  fj = 0;
  //w.pop();
}

#endif
