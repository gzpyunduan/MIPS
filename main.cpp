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

void init(){
	s = ""; l.tk = NONE; t.tk = NONE;
	if (!m.empty()) m.pop();
	if (!w.empty()) w.pop();
}

int main(int argc, char *argv[]) {
	//freopen("28.s", "r", stdin);
	//freopen("1.out", "w", stdout);
	fin.open(argv[1]);
	preProcess();
	fin.close();
	//freopen("28.in", "r", stdin);

	while (true) {
		init();
		InstructionFetch();
		InstructionDecode();
		Execute();
		MemoryAccess();
		WriteBack();

		if (fend)
			break;
	}
	return 0;
}
