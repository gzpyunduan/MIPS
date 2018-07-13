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
	//freopen("2.s", "r", stdin);
	//freopen("1.out", "w", stdout);
	fin.open(argv[1]);
	preProcess();
	fin.close();
	//freopen("2.in", "r", stdin);

	while (true) {
		InstructionFetch();
		InstructionDecode();
		Execute();
		MemoryAccess();
		WriteBack();

		if (fend)
			break;
	}
	while (true) {}
	return 0;
}
