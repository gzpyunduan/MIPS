#ifndef _PERFORMER
#define _PERFORMER

#include "parser.h"
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

struct FF {
	bool t;
	bool type;
	int rn;
	int address;
	int size;
	long long ans1;
	long long ans2;

	FF(bool t1 = 0, bool t2 = 0, int x = -1, int y = 0, int z = 0, long long a = 0, long long b = 0) {
		t = t1; type = t2; rn = x; address = y; size = z; ans1 = a; ans2 = b;
	}
};

static queue<FF> m;
static queue<FF> w;
FF ff;

bool isChar(const char &c) {
	if ((c <= '9' && c >= '0') || (c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return 1;
	else return 0;
}

void Syscall() {
	int l;
	char c;
	switch (reg[2]) {
	case 1: { printf("%d", reg[4]); dwb[1] = -1; break; }
	case 4: { printf("%s", Data + reg[4]); dwb[1] = -1; break; }
	case 5: {
		int a = 0;
		scanf("%d", &a);
		//cout << "cin >> " << a;
		ff = FF(1, 0, 2, 0, 0, a);
		dwb[1] = 2;
		break;
	}
	case 8: {
		string s1;
		c = getchar();
		if (!isChar(c)) c = getchar();
		while (isChar(c)) {
			s1 += c;
			c = getchar();
		}
		//cout << "cin >> " << s1;
		l = s1.size() >= (reg[5] + 1) ? (reg[5] + 1) : s1.size();
		for (int j = 0; j < l; j++)
			Data[reg[4] + j] = s1[j];
		Data[reg[4] + l] = '\0';
		dwb[1] = -1;
		break;
	}
	case 9: {
		ff = FF(1, 0, 2, 0, 0, posh);
		dwb[1] = 2;
		posh += reg[4];
		break;
	}
	case 10: { fend = 1; dwb[1] = -1; revalue = 0; break; }
	case 17: { fend = 1; dwb[1] = -1; revalue = reg[4]; break; }
	}
}

void Execute() {
	ff = FF();
	if (t.tk == NONE) return;
	switch (t.tk) {
	case ADD: case ADDU: case ADDIU:
		ff = FF(1, 0, t.p[0], 0, 0, t.p[1] + t.p[2]);
		dwb[1] = t.p[0];
		break;
	case SUB: case SUBU:
		ff = FF(1, 0, t.p[0], 0, 0, t.p[1] - t.p[2]);
		dwb[1] = t.p[0];
		break;
	case MUL: case MULU:
		if (t.size == 3) {
			dwb[1] = t.p[0];
			ff = FF(1, 0, t.p[0], 0, 0, t.p[1] * t.p[2]);
		}
		else {
			dwb[1] = -1;
			ff = FF(1, 0, 32, 0, 0, t.p[0] * t.p[1] >> 32, t.p[0] * t.p[1]);
		}
		break;
	case DIV: case DIVU:
		if (t.size == 3) {
			dwb[1] = t.p[0];
			ff = FF(1, 0, t.p[0], 0, 0, t.p[1] / t.p[2]);
		}
		else {
			dwb[1] = -1;
			ff = FF(1, 0, 32, 0, 0, t.p[0] % t.p[1], t.p[0] / t.p[1]);
		}
		break;
	case XOR: case XORU:
		ff = FF(1, 0, t.p[0], 0, 0, t.p[1] ^ t.p[2]);
		dwb[1] = t.p[0];
		break;
	case NEG:
		ff = FF(1, 0, t.p[0], 0, 0, -t.p[1]);
		dwb[1] = t.p[0];
		break;
	case NEGU:
		ff = FF(1, 0, t.p[0], 0, 0, ~t.p[1]);
		dwb[1] = t.p[0];
		break;
	case REM: case REMU:
		ff = FF(1, 0, t.p[0], 0, 0, t.p[1] % t.p[2]);
		dwb[1] = t.p[0];
		break;

	case LI:
		ff = FF(1, 0, t.p[0], 0, 0, t.p[1]);
		dwb[1] = t.p[0];
		break;

	case SEQ:
		ff = FF(1, 0, t.p[0], 0, 0, (t.p[1] == t.p[2]));
		dwb[1] = t.p[0];
		break;
	case SGE:
		ff = FF(1, 0, t.p[0], 0, 0, (t.p[1] >= t.p[2]));
		dwb[1] = t.p[0];
		break;
	case SGT:
		ff = FF(1, 0, t.p[0], 0, 0, (t.p[1] > t.p[2]));
		dwb[1] = t.p[0];
		break;
	case SLE:
		ff = FF(1, 0, t.p[0], 0, 0, (t.p[1] <= t.p[2]));
		dwb[1] = t.p[0];
		break;
	case SLT:
		ff = FF(1, 0, t.p[0], 0, 0, (t.p[1] < t.p[2]));
		dwb[1] = t.p[0];
		break;
	case SNE:
		ff = FF(1, 0, t.p[0], 0, 0, (t.p[1] != t.p[2]));
		dwb[1] = t.p[0];
		break;

	case B:
		ff = FF(1, 0, 34, 0, 0, t.p[0]);
		fj = 1;
		dwb[1] = 34;
		break;
	case BEQ:
		if (t.p[0] == t.p[1]) {
			ff = FF(1, 0, 34, 0, 0, t.p[2]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BNE:
		if (t.p[0] != t.p[1]) {
			ff = FF(1, 0, 34, 0, 0, t.p[2]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BGE:
		if (t.p[0] >= t.p[1]) {
			ff = FF(1, 0, 34, 0, 0, t.p[2]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BLE:
		if (t.p[0] <= t.p[1]) {
			ff = FF(1, 0, 34, 0, 0, t.p[2]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BGT:
		if (t.p[0] > t.p[1]) {
			ff = FF(1, 0, 34, 0, 0, t.p[2]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BLT:
		if (t.p[0] < t.p[1]) {
			ff = FF(1, 0, 34, 0, 0, t.p[2]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BEQZ:
		if (t.p[0] == 0) {
			ff = FF(1, 0, 34, 0, 0, t.p[1]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BNEZ:
		if (t.p[0] != 0) {
			ff = FF(1, 0, 34, 0, 0, t.p[1]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BLEZ:
		if (t.p[0] <= 0) {
			ff = FF(1, 0, 34, 0, 0, t.p[1]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BGEZ:
		if (t.p[0] >= 0) {
			ff = FF(1, 0, 34, 0, 0, t.p[1]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BGTZ:
		if (t.p[0] > 0) {
			ff = FF(1, 0, 34, 0, 0, t.p[1]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case BLTZ:
		if (t.p[0] < 0) {
			ff = FF(1, 0, 34, 0, 0, t.p[1]);
			dwb[1] = 34;
			fj = 1;
		}
		else dwb[1] = -1;
		break;
	case J:
		ff = FF(1, 0, 34, 0, 0, t.p[0]);
		fj = 1;
		dwb[1] = 34;
		break;
	case JR:
		ff = FF(1, 0, 34, 0, 0, t.p[0]);
		fj = 1;
		dwb[1] = 34;
		break;
	case JAL:
		ff = FF(1, 0, 42, 0, 0, t.p[0]);
		fj = 1;
		dwb[1] = 42;
		break;
	case JALR:
		ff = FF(1, 0, 42, 0, 0, t.p[0]);
		fj = 1;
		dwb[1] = 42;
		break;

	case LA:
		ff = FF(1, 0, t.p[0], 0, 0, t.p[1]);
		dwb[1] = t.p[0];
		break;
	case LB:
		ff = FF(0, 0, t.p[0], t.p[1], 1);
		dwb[1] = t.p[0];
		break;
	case LH:
		ff = FF(0, 0, t.p[0], t.p[1], 2);
		dwb[1] = t.p[0];
		break;
	case LW:
		ff = FF(0, 0, t.p[0], t.p[1], 4);
		dwb[1] = t.p[0];
		break;

	case SB:
		ff = FF(0, 1, t.p[0], t.p[1], 1);
		dwb[1] = -1;
		break;
	case SH:
		ff = FF(0, 1, t.p[0], t.p[1], 2);
		dwb[1] = -1;
		break;
	case SW:
		ff = FF(0, 1, t.p[0], t.p[1], 4);
		dwb[1] = -1;
		break;
	case MOVE:
		ff = FF(1, 0, t.p[0], 0, 0, t.p[1]);
		dwb[1] = t.p[0];
		break;
	case MFHI:
		ff = FF(1, 0, t.p[0], 0, 0, reg[32]);
		dwb[1] = t.p[0];
		break;
	case MFLO:
		ff = FF(1, 0, t.p[0], 0, 0, reg[33]);
		dwb[1] = t.p[0];
		break;

	case NOP: dwb[1] = -1; break;
	case SYSCALL: Syscall(); break;
	}
	m.push(ff);
}


#endif
