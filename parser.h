#ifndef _PARSER
#define _PARSER

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include "enumType.h"
#include "scanner.h"
using namespace std;

struct Token{
  tokenType tk;
  vector<string> vec;

  Token(){}

  Token(const string &s){
    int i = 0;
    while(s[i] == '\t' || s[i] == ' ') i++;
    int h = i;
    while(s[i] != ' ') i++;
    string order = s.substr(h, i - h);
    if (order.compare("add") == 0) tk = ADD;
    else if (order.compare("addu") == 0) tk = ADDU;
    else if (order.compare("addiu") == 0) tk = ADDIU;
    else if (order.compare("sub") == 0) tk = SUB;
    else if (order.compare("subu") == 0) tk = SUBU;
    else if (order.compare("mul") == 0) tk = MUL;
    else if (order.compare("mulu") == 0) tk = MULU;
    else if (order.compare("div") == 0) tk = DIV;
    else if (order.compare("divu") == 0) tk = DIVU;
    else if (order.compare("xor") == 0) tk = XOR;
    else if (order.compare("xoru") == 0) tk = XORU;
    else if (order.compare("neg") == 0) tk = NEG;
    else if (order.compare("negu") == 0) tk = NEGU;
    else if (order.compare("rem") == 0) tk = REM;
    else if (order.compare("remu") == 0) tk = REMU;
    else if (order.compare("li") == 0) tk = LI;
    else if (order.compare("seq") == 0) tk = SEQ;
    else if (order.compare("sge") == 0) tk = SGE;
    else if (order.compare("sgt") == 0) tk = SGT;
    else if (order.compare("sle") == 0) tk = SLE;
    else if (order.compare("slt") == 0) tk = SLT;
    else if (order.compare("sne") == 0) tk = SNE;
    else if (order.compare("b") == 0) tk = B;
    else if (order.compare("beq") == 0) tk = BEQ;
    else if (order.compare("bne") == 0) tk = BNE;
    else if (order.compare("bge") == 0) tk = BGE;
    else if (order.compare("ble") == 0) tk = BLE;
    else if (order.compare("bgt") == 0) tk = BGT;
    else if (order.compare("blt") == 0) tk = BLT;
    else if (order.compare("beqz") == 0) tk = BEQZ;
    else if (order.compare("bnez") == 0) tk = BNEZ;
    else if (order.compare("blez") == 0) tk = BLEZ;
    else if (order.compare("j") == 0) tk = J;
    else if (order.compare("jr") == 0) tk = JR;
    else if (order.compare("jal") == 0) tk = JAL;
    else if (order.compare("jalr") == 0) tk = JALR;
    else if (order.compare("la") == 0) tk = LA;
    else if (order.compare("lb") == 0) tk = LB;
    else if (order.compare("lh") == 0) tk = LH;
    else if (order.compare("lw") == 0) tk = LW;
    else if (order.compare("sb") == 0) tk = SB;
    else if (order.compare("sh") == 0) tk = SH;
    else if (order.compare("sw") == 0) tk = SW;
    else if (order.compare("move") == 0) tk = MOVE;
    else if (order.compare("mfhi") == 0) tk = MFHI;
    else if (order.compare("mflo") == 0) tk = MFLO;
    else if (order.compare("nop") == 0) tk = NOP;
    else if (order.compare("syscall") == 0) tk = SYSCALL;

    while(s[i] != '\0'){
      while(s[i] == ' ' || s[i] == ',') i++;
      h = i;
      while(s[i] != ' ' && s[i] != ',') i++;
      string word = s.substr(h, i - h);
      vec.push_back(word);
    }
  }
};

static Token t;

void InstructionDecode(){
  if (s == "\0") return;
  t = Token(s);
  s = "";
}

#endif
