#ifndef _SCANNER
#define _SCANNER

#include "init.h"

void InstructionFetch(){
  if (fend) return;
  //cout << reg[34] << ' ';
  s = Text[reg[34]++];
  cout << s << endl;
}

#endif
