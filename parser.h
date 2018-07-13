#ifndef _PARSER
#define _PARSER

#include <iostream>
#include <cstdio>
#include <cstring>
#include "scanner.h"
using namespace std;

struct Token {
	optType tk = NONE;
	int p[3];
	int size = 0;

	Token() :tk(NONE), size(0) {}

	Token(const Line &_l) {
		tk = _l.tk;

		if (tk == LA) {
			size = _l.size;
			p[0] = _l.p[0];
			if (_l.d[1] == FUN)
				p[1] = fun[_l.p[1]];
			else
				p[1] = var[_l.p[1]];
		}
		else if (tk >= LB && tk <= SW) {
			if (_l.size == 3) {
				size = _l.size - 1;
				p[0] = _l.p[0];
				p[1] = _l.p[1] + reg[_l.p[2]];
			}
			else {
				size = _l.size - 1;
				p[0] = _l.p[0];
				if (_l.d[1] == FUN)
					p[1] = fun[_l.p[1]];
				else
					p[1] = var[_l.p[1]];
			}
		}
		else if (tk >= MUL && tk <= DIVU) {
			size = _l.size;
			if (size == 2) {
				p[0] = reg[_l.p[0]];
				if (_l.d[1] == REG)
					p[1] = reg[_l.p[1]];
				else
					p[1] = _l.p[1];
			}
			else {
				p[0] = _l.p[0];
				p[1] = reg[_l.p[1]];
				if (_l.d[2] == REG)
					p[2] = reg[_l.p[2]];
				else
					p[2] = _l.p[2];
			}
		}
		else if (tk == B || tk == J || tk == JAL) {
			size = _l.size;
			if (_l.d[0] == FUN)
				p[0] = fun[_l.p[0]];
			else
				p[0] = var[_l.p[0]];
		}
		else if (tk == JR || tk == JALR) {
			size = _l.size;
			p[0] = reg[_l.p[0]];
		}
		else if (tk >= BEQ && tk <= BLT) {
			size = _l.size;
			p[0] = reg[_l.p[0]];
			if (_l.d[1] == REG)
				p[1] = reg[_l.p[1]];
			else
				p[1] = _l.p[1];
			if (l.d[2] == FUN)
				p[2] = fun[_l.p[2]];
			else
				p[2] = var[_l.p[2]];
		}
		else if (tk >= BEQZ && tk <= BLTZ) {
			size = _l.size;
			p[0] = reg[_l.p[0]];
			if (_l.d[1] == FUN)
				p[1] = fun[_l.p[1]];
			else
				p[1] = var[_l.p[1]];
		}
		else if (tk == NOP || tk == SYSCALL) {
			size = 0;
		}
		else {
			p[0] = _l.p[0];
			size = _l.size;
			for (int i = 1; i < size; i++) {
				if (_l.d[i] == REG)
					p[i] = reg[_l.p[i]];
				else p[i] = _l.p[i];
			}
		}
	}
};

static Token t;

void InstructionDecode() {
	if (Pau) return;
	if (l.tk == NONE || fj) {
		t.tk = NONE;
		return;
	}
	for (int i = 0; i < l.size; i++) {
		if (l.d[i] == REG) {
			if (dwb[0] == 42) {
				if (l.p[i] == 31 || l.p[i] == 34)
					if (pau < 1) pau = 1;
			}
			else if (dwb[1] == 42) {
				if (l.p[i] == 31 || l.p[i] == 34)
					if (pau < 2) pau = 2;
			}
			else if (l.p[i] == dwb[0]) {
				if (pau < 1) pau = 1;
			}
			else if (l.p[i] == dwb[1]) {
				if (pau < 2) pau = 2;
			}
		}
		else if (l.tk == SYSCALL) {
			if (dwb[0] == 2 || dwb[1] == 2) {
				if (pau < 1) pau = 1;
			}
			else if (reg[2] == 1 || reg[2] == 4 || reg[2] == 9 || reg[2] == 17) {
				if (dwb[0] == 4 || dwb[1] == 4)
					if (pau < 1) pau = 1;
			}
			else if (reg[2] == 8) {
				if (dwb[0] == 4 || dwb[0] == 5 || dwb[1] == 4 || dwb[1] == 5)
					if (pau < 1) pau = 1;
			}
		}
	}
	t = Token(l);
	l.tk = NONE;
	//s = "";
}

#endif
