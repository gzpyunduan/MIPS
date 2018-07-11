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

	Token(const Line &l) {
		tk = l.tk;

		if (tk == LA) {
			size = l.size;
			p[0] = l.p[0];
			if (l.d[1] == FUN)
				p[1] = fun[l.p[1]];
			else
				p[1] = var[l.p[1]];
		}
		else if (tk >= LB && tk <= SW) {
			if (l.size == 3) {
				size = l.size - 1;
				p[0] = l.p[0];
				p[1] = l.p[1] + reg[l.p[2]];
			}
			else {
				size = l.size - 1;
				p[0] = l.p[0];
				if (l.d[1] == FUN)
					p[1] = fun[l.p[1]];
				else
					p[1] = var[l.p[1]];
			}
		}
		else if (tk >= MUL && tk <= DIVU) {
			size = l.size;
			if (size == 2) {
				p[0] = reg[l.p[0]];
				if (l.d[1] == REG)
					p[1] = reg[l.p[1]];
				else
					p[1] = l.p[1];
			}
			else {
				p[0] = l.p[0];
				p[1] = reg[l.p[1]];
				if (l.d[2] == REG)
					p[2] = reg[l.p[2]];
				else
					p[2] = l.p[2];
			}
		}
		else if (tk == B || tk == J || tk == JAL) {
			size = l.size;
			if (l.d[0] == FUN)
				p[0] = fun[l.p[0]];
			else
				p[0] = var[l.p[0]];
		}
		else if (tk == JR || tk == JALR) {
			size = l.size;
			p[0] = reg[l.p[0]];
		}
		else if (tk >= BEQ && tk <= BLT) {
			size = l.size;
			p[0] = reg[l.p[0]];
			if (l.d[1] == REG)
				p[1] = reg[l.p[1]];
			else
				p[1] = l.p[1];
			if (l.d[2] == FUN)
				p[2] = fun[l.p[2]];
			else
				p[2] = var[l.p[2]];
		}
		else if (tk >= BEQZ && tk <= BLTZ) {
			size = l.size;
			p[0] = reg[l.p[0]];
			if (l.d[1] == FUN)
				p[1] = fun[l.p[1]];
			else
				p[1] = var[l.p[1]];
		}
		else if (tk == NOP || tk == SYSCALL) {
			size = 0;
		}
		else {
			p[0] = l.p[0];
			size = l.size;
			for (int i = 1; i < size; i++) {
				if (l.d[i] == REG)
					p[i] = reg[l.p[i]];
				else p[i] = l.p[i];
			}
		}
	}
};

static Token t;
static Token ts[10000];

void InstructionDecode() {
	if (s == "\0") return;
	t = Token(s);
	//s = "";
}

#endif
