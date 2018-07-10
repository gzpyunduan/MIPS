#ifndef _WRITE
#define _WRITE

#include "memory.h"

void WriteBack(){
  if (w.empty()) return;
  FF tmp = w.front();
  if (tmp.rn == -1) return;
  if (tmp.rn == 42) {
	reg[31] = reg[34];
	reg[34] = tmp.ans1;
  }
  else {
	reg[tmp.rn] = tmp.ans1;
	if (tmp.rn == 32) reg[33] = tmp.ans2;
  }
  //w.pop();
}

#endif
