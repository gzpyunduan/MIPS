#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include "scanner.h"
#include "parser.h"
#include "performer.h"
#include "memory.h"
#include "write.h"
using namespace std;

int main(int argc, char *argv[]){
  //freopen("19.s", "r", stdin);
  //freopen("1.out", "w", stdout);
  preProcess();
  //freopen("19.in", "r", stdin);
  fin.open(argv[1]);
  while(true){
	s = ""; t.tk = NONE;
	if (!m.empty()) m.pop();
	if (!w.empty()) w.pop();

	//cout << reg[34] << endl;
    InstructionFetch();
    InstructionDecode();
	Execute();
    MemoryAccess();
	WriteBack();
    
    if (s == "\0" && t.tk == NONE && m.empty() && w.empty())
      break;
  }
  while(true){}
  return 0;
}
