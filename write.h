#ifndef _WRITE
#define _WRITE

void WriteBack(){
  WB tmp = w.front();
  if (w.empty()){
    reg[tmp.rn] = tmp.ans1;
    if (tmp.rn == 32) reg[33] = tmp.ans2;
  }
  w.pop();
}

#endif
