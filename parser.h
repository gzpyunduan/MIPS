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
	if (s == "\0") return;
	t = Token(l);
	//s = "";
}

#endif
