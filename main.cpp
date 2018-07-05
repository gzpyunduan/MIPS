#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include "scanner.h"
#include "parser.h"
#include "performer.h"
#include "memory.h"
#include "write.h"
using namespace std;

int main(){
  freopen("1.s", "r", stdin);
  preProcess();
  while(true){
    InstructionFetch();
    InstructionDecode();
    Execute();
    MemoryAccess();
    WriteBack();
    if (s == "\0" && t.tk == NONE && m.empty() && w.empty())
      break;
  }
  return 0;
}
