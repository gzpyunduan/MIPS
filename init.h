#ifndef _INIT
#define _INIT

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

enum tokenType {
	ADD, ADDU, ADDIU, SUB, SUBU, MUL, MULU, DIV,
	DIVU, XOR, XORU, NEG, NEGU, REM, REMU, LI, SEQ, SGE,
	SGT, SLE, SLT, SNE, B, BEQ, BNE, BGE, BLE, BGT, BLT,
	BEQZ, BNEZ, BLEZ, BGEZ, BGTZ, BLTZ, J, JR, JAL, JALR, LA,
	LB, LH, LW, SB, SH, SW, MOVE, MFHI, MFLO, NOP, SYSCALL, NONE
};

static const int SP = 4000000;
static ifstream fin;
static int var[1000];
static int fun[1000];
static unsigned char Data[4000000];
static string Text[10000];
static int reg[35];
static int posh = 1000000;
static bool fend = 0;
static int revalue = 0;
static string s;
static map<string, int> rti;
static map<string, tokenType> oti;
static map<string, int> fti;
static map<string, int> vti;
int posd, post;
bool v = 0;

int toInt(const string &s) {
	int ans = 0;
	for (int i = (s[0] == '-') ? 1 : 0; i < s.size(); i++)
		ans = ans * 10 + s[i] - '0';
	return (s[0] == '-') ? -ans : ans;
}

void toChar(int pos, int size, int num) {
	for (int i = 0; i < size; i++)
		Data[pos + i] = (num >> (8 * i)) & 255;
}

int CharToInt(int pos, int size) {
	int a = 0;
	for (int i = 0; i < size; i++)
		a += Data[pos + i] << (i * 8);
	return a;
}

void RegToInt() {
	rti["$0"] = 0; rti["$zero"] = 0;
	rti["$1"] = 1; rti["$at"] = 1;
	rti["$2"] = 2; rti["$v0"] = 2;
	rti["$3"] = 3; rti["$v1"] = 3;
	rti["$4"] = 4; rti["$a0"] = 4;
	rti["$5"] = 5; rti["$a1"] = 5;
	rti["$6"] = 6; rti["$a2"] = 6;
	rti["$7"] = 7; rti["$a3"] = 7;
	rti["$8"] = 8; rti["$t0"] = 8;
	rti["$9"] = 9; rti["$t1"] = 9;
	rti["$10"] = 10; rti["$t2"] = 10;
	rti["$11"] = 11; rti["$t3"] = 11;
	rti["$12"] = 12; rti["$t4"] = 12;
	rti["$13"] = 13; rti["$t5"] = 13;
	rti["$14"] = 14; rti["$t6"] = 14;
	rti["$15"] = 15; rti["$t7"] = 15;
	rti["$16"] = 16; rti["$s0"] = 16;
	rti["$17"] = 17; rti["$s1"] = 17;
	rti["$18"] = 18; rti["$s2"] = 18;
	rti["$19"] = 19; rti["$s3"] = 19;
	rti["$20"] = 20; rti["$s4"] = 20;
	rti["$21"] = 21; rti["$s5"] = 21;
	rti["$22"] = 22; rti["$s6"] = 22;
	rti["$23"] = 23; rti["$s7"] = 23;
	rti["$24"] = 24; rti["$t8"] = 24;
	rti["$25"] = 25; rti["$t9"] = 25;
	rti["$28"] = 28; rti["$gp"] = 28;
	rti["$29"] = 29; rti["$sp"] = 29;
	rti["$30"] = 30; rti["$fp"] = 30;
	rti["$31"] = 31; rti["$ra"] = 31;
	rti["$hi"] = 32;
	rti["$lo"] = 33;
	rti["$pc"] = 34;
}

void OptToInt(){
	oti["add"] = ADD;
	oti["addu"] = ADDU;
	oti["addit"] = ADDIU;
	oti["sub"] = SUB;
	oti["subu"] = SUBU;
	oti["mul"] = MUL;
	oti["mulu"] = MULU;
	oti["div"] = DIV;
	oti["divu"] = DIVU;
	oti["xor"] = XOR;
	oti["xoru"] = XORU;
	oti["neg"] = NEG;
	oti["negu"] = NEGU;
	oti["rem"] = REM;
	oti["remu"] = REMU;
	oti["li"] = LI;
	oti["seq"] = SEQ;
	oti["sge"] = SGE;
	oti["sgt"] = SGT;
	oti["sle"] = SLE;
	oti["slt"] = SLT;
	oti["sne"] = SNE;
	oti["b"] = B;
	oti["beq"] = BEQ;
	oti["bne"] = BNE;
	oti["bge"] = BGE;
	oti["ble"] = BLE;
	oti["bgt"] = BGT;
	oti["blt"] = BLT;
	oti["beqz"] = BEQZ;
	oti["bnez"] = BNEZ;
	oti["blez"] = BLEZ;
	oti["bgez"] = BGEZ;
	oti["bgtz"] = BGTZ;
	oti["bltz"] = BLTZ;
	oti["j"] = J;
	oti["jr"] = JR;
	oti["jal"] = JAL;
	oti["jalr"] = JALR;
	oti["la"] = LA;
	oti["lb"] = LB;
	oti["lh"] = LH;
	oti["lw"] = LW;
	oti["sb"] = SB;
	oti["sh"] = SH;
	oti["sw"] = SW;
	oti["move"] = MOVE;
	oti["mfhi"] = MFHI;
	oti["mflo"] = MFLO;
	oti["nop"] = NOP;
	oti["syscall"] = SYSCALL;
}

void varieble() {
	s = "";
	while (true) {
		while (true) {
			getline(fin, s);
			if (!v) while (s[s.size() - 1] != ':') getline(fin, s);
			if (s[1] != '.') break;
			if (s == "\t.data" || s == "\t.text") return;

			int i;
			for (i = 2; s[i] != ' '; i++);
			string opt = s.substr(2, i - 2);

			if (opt == "align") {
				int num = pow(2, s[8] - '0');
				if (posd % num != 0) posd = (posd / num + 1) * num;
			}
			else if (opt == "ascii") {
				int j;
				if (s[9] == '\\') {
					if (s[10] == 'n') Data[posd++] = '\n';
					else if (s[10] == 't') Data[posd++] = '\t';
					else if (s[10] == '\\') Data[posd++] = '\\';
				}
				else {
					for (int k = 0; k < j - 9; k++)
						Data[posd++] = s[9 + k];
				}
			}
			else if (opt == "asciiz") {
				int j = 10;
				while (s[j] != '"') j++;
				if (s[10] == '\\') {
					if (s[11] == 'n') Data[posd++] = '\n';
					else if (s[11] == 't') Data[posd++] = '\t';
					else if (s[11] == '\\') Data[posd++] = '\\';
				}
				else {
					for (int k = 0; k < j - 10; k++)
						Data[posd++] = s[10 + k];
				}
				Data[posd++] = '\0';
			}
			else if (opt == "byte") {
				int j = 7;
				int p = 0;
				string sd;
				while (true) {
					if (s[j] != ',' && s[j] != '\0') sd += s[j];
					else {
						toChar(posd++, 1, toInt(sd));
						sd = "";
						p = 0;
					}
					if (s[j] == '\0') break;
					j++;
				}
			}
			else if (opt == "half") {
				int j = 7;
				int p = 0;
				string sd;
				while (true) {
					if (s[j] != ',' && s[j] != '\0') sd += s[j];
					else {
						toChar(posd, 2, toInt(sd));
						sd = "";
						p = 0;
					}
					if (s[j] == '\0') break;
					j++;
				}
				posd += 2;
			}
			else if (opt == "word") {
				int j = 7;
				string sd = "";
				while (true) {
					if (s[j] != ',' && s[j] != '\0') sd += s[j];
					else {
						toChar(posd, 4, toInt(sd));
						sd = "";
					}
					if (s[j] == '\0') break;
					j++;
				}
				posd += 4;
			}
			else if (opt == "space") {
				posd += s[8] - '0';
				for (int i = 0; i < s[8] - '0'; i++)
					Data[posd++] = ' ';
			}
			else if (opt == "text" || opt == "data")
				return;
		}
		if (s == "\t.data" || s == "\t.text") break;
		v = 1;
		int si = vti.size();
		var[si] = posd;
		vti[s] = si;
	}
}

void function() {
	while (getline(fin, s)) {
		if (s == "\t.data" || s == "\t.text") return;
		if (s == "\0") continue;
		if (s[s.size() - 1] == ':') {
			if (s == "main:") reg[34] = post;
			else {
				int k = 0;
				while (s[k] == '\t') k++;
				string s1 = s.substr(k, s.size() - k);
				fun[fti.size()] = post;
				fti[s1] = fti.size();
			}
		}
		else Text[post++] = s;
	}
}

void preProcess() {
	RegToInt();
	OptToInt();
	getline(fin, s);
	while (s != "\0") {
		if (s == "\t.data") varieble();
		if (s == "\t.text") function();
	}
	reg[29] = SP;
}

#endif
