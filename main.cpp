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

int main(int argc, char *argv[]) {
	//freopen("1.s", "r", stdin);
	//freopen("1.out", "w", stdout);
	fin.open(argv[1]);
	preProcess();
	fin.close();
	//freopen("1.in", "r", stdin);

	while (true) {
		s = ""; t.tk = NONE;
		if (!m.empty()) m.pop();
		if (!w.empty()) w.pop();

		//cout << reg[34] << endl;
		InstructionFetch();
		InstructionDecode();
		Execute();
		MemoryAccess();
		WriteBack();

		if (l.tk == NONE && t.tk == NONE && m.rn == -1 && w.rn == -1 && fend)
			break;
	}
	return 0;
}
