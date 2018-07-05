#ifndef _PERFORMER
#define _PERFORMER

#include "parser.h"
#include "scanner.h"
#include <vector>
#include <cstring>
#include <queue>

struct MA{
  bool type;
  int rn;
  int address;
  int size;

  MA(): type(0), rn(0), address(0), size(0){}
  MA(bool t, int x, int y, int z): type(t), rn(x), address(y), size(z){}
};

struct WB{
  int rn;
  long long ans1;
  long long ans2;

  WB(): rn(0), ans1(0), ans2(0){}
  WB(int x, long long y, long long z): rn(x), ans1(y), ans2(z){}
};

static queue<MA> m;
static queue<WB> w;

int toReg(const string &s){
  if (s == "$zero" || s == "$0") return 0;
  if (s == "$at" || s == "$1") return 1;
  if (s == "$v0" || s == "$2") return 2;
  if (s == "$v1" || s == "$3") return 3;
  if (s == "$a0" || s == "$4") return 4;
  if (s == "$a1" || s == "$5") return 5;
  if (s == "$a2" || s == "$6") return 6;
  if (s == "$a3" || s == "$7") return 7;
  if (s == "$t0" || s == "$8") return 8;
  if (s == "$t1" || s == "$9") return 9;
  if (s == "$t2" || s == "$10") return 10;
  if (s == "$t3" || s == "$11") return 11;
  if (s == "$t4" || s == "$12") return 12;
  if (s == "$t5" || s == "$13") return 13;
  if (s == "$t6" || s == "$14") return 14;
  if (s == "$t7" || s == "$15") return 15;
  if (s == "$s0" || s == "$16") return 16;
  if (s == "$s1" || s == "$17") return 17;
  if (s == "$s2" || s == "$18") return 18;
  if (s == "$s3" || s == "$19") return 19;
  if (s == "$s4" || s == "$20") return 20;
  if (s == "$s5" || s == "$21") return 21;
  if (s == "$s6" || s == "$22") return 22;
  if (s == "$s7" || s == "$23") return 23;
  if (s == "$t8" || s == "$24") return 24;
  if (s == "$t9" || s == "$25") return 25;
  if (s == "$gp" || s == "$28") return 28;
  if (s == "$sp" || s == "$29") return 29;
  if (s == "$fp" || s == "$30") return 30;
  if (s == "$ra" || s == "$31") return 31;
}

int getFromLable(int p){
  int a;
  while(Static[p]){
    a = a * 10 + Static[p] - '0';
    p++;
  }
  return a;
}

int toInt(const string &s){
  int i = 0, a = 0;
  while(s[i]){
    a = a * 10 + s[i] - '0';
    i++;
  }
  return a;
}

int getAddress(const string &s){
  int i = 0, j = 0, mv;
  string tmp;
  if (s[i] == '-'){
    i++;
    while(s[i] != '(')
      tmp[j++] = s[i++];
    mv = -toInt(tmp);
  }
  else{
    while(s[i] != '(')
      tmp[j++] = s[i++];
    mv = toInt(tmp);
  }
  tmp = ""; j = 0;

  i++;
  while(s[i] != ')')
    tmp[j++] = s[i++];
  return toReg(tmp) + mv;
}

void Add(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), l + r, 0);
  w.push(tmp);
}

void Sub(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), l - r, 0);
  w.push(tmp);
}

void Mul(){
  if (t.vec.size() == 3){
    int l = reg[toReg(t.vec[1])], r;
    if (t.vec[2][0] == '$')
      r = reg[toReg(t.vec[2])];
    else if (t.vec[2][0] == '_')
      r = getFromLable(var.at(t.vec[2]));
    else r = toInt(t.vec[2]);
    WB tmp(toReg(t.vec[0]), l * r, 0);
    w.push(tmp);
  }
  else {
    int l = reg[toReg(t.vec[0])], r;
    if (t.vec[1][0] == '$')
      r = reg[toReg(t.vec[1])];
    else if (t.vec[1][0] == '_')
      r = getFromLable(var.at(t.vec[1]));
    else r = toInt(t.vec[1]);
    WB tmp(32, l * r / MAX, l * r % MAX);
    w.push(tmp);
  }
}

void Div(){
  if (t.vec.size() == 3){
    int l = reg[toReg(t.vec[1])], r;
    if (t.vec[2][0] == '$')
      r = reg[toReg(t.vec[2])];
    else if (t.vec[2][0] == '_')
      r = getFromLable(var.at(t.vec[2]));
    else r = toInt(t.vec[2]);
    WB tmp(32, l / r, 0);
    w.push(tmp);
  }
  else {
    int l = reg[toReg(t.vec[0])], r;
    if (t.vec[1][0] == '$')
      r = reg[toReg(t.vec[1])];
    else if (t.vec[1][0] == '_')
      r = getFromLable(var.at(t.vec[1]));
    else r = toInt(t.vec[1]);
    WB tmp(32, l % r, l / r);
    w.push(tmp);
  }
}

void Xor(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), l ^ r, 0);
  w.push(tmp);
}

void Neg(){
  int l = reg[toReg(t.vec[1])];
  WB tmp(toReg(t.vec[0]), ~l, 0);
  w.push(tmp);
}

void Rem(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), l % r, 0);
  w.push(tmp);
}

void Li(){
  WB tmp(toReg(t.vec[0]), toInt(t.vec[1]), 0);
  w.push(tmp);
}

void Seq(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), (l == r), 0);
  w.push(tmp);
}

void Sge(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), (l >= r), 0);
  w.push(tmp);
}

void Sgt(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), (l > r), 0);
  w.push(tmp);
}

void Sle(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), (l <= r), 0);
  w.push(tmp);
}

void Slt(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), (l < r), 0);
  w.push(tmp);
}

void Sne(){
  int l = reg[toReg(t.vec[1])], r;
  if (t.vec[2][0] == '$')
    r = reg[toReg(t.vec[2])];
  else if (t.vec[2][0] == '_')
    r = getFromLable(var.at(t.vec[2]));
  else r = toInt(t.vec[2]);
  WB tmp(toReg(t.vec[0]), (l != r), 0);
  w.push(tmp);
}

void Bf(){
  WB tmp(34, fun.at(t.vec[0]), 0);
  w.push(tmp);
  t.tk = NONE;
  s = "";
}

void Beq(){
  int l = reg[toReg(t.vec[0])], r;
  if (t.vec[1][0] == '$')
    r = reg[toReg(t.vec[1])];
  else if (t.vec[1][0] == '_')
    r = getFromLable(var.at(t.vec[1]));
  else r = toInt(t.vec[1]);
  if (l == r){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Bne(){
  int l = reg[toReg(t.vec[0])], r;
  if (t.vec[1][0] == '$')
    r = reg[toReg(t.vec[1])];
  else if (t.vec[1][0] == '_')
    r = getFromLable(var.at(t.vec[1]));
  else r = toInt(t.vec[1]);
  if (l != r){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Bge(){
  int l = reg[toReg(t.vec[0])], r;
  if (t.vec[1][0] == '$')
    r = reg[toReg(t.vec[1])];
  else if (t.vec[1][0] == '_')
    r = getFromLable(var.at(t.vec[1]));
  else r = toInt(t.vec[1]);
  if (l >= r){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Ble(){
  int l = reg[toReg(t.vec[0])], r;
  if (t.vec[1][0] == '$')
    r = reg[toReg(t.vec[1])];
  else if (t.vec[1][0] == '_')
    r = getFromLable(var.at(t.vec[1]));
  else r = toInt(t.vec[1]);
  if (l <= r){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Bgt(){
  int l = reg[toReg(t.vec[0])], r;
  if (t.vec[1][0] == '$')
    r = reg[toReg(t.vec[1])];
  else if (t.vec[1][0] == '_')
    r = getFromLable(var.at(t.vec[1]));
  else r = toInt(t.vec[1]);
  if (l > r){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Blt(){
  int l = reg[toReg(t.vec[0])], r;
  if (t.vec[1][0] == '$')
    r = reg[toReg(t.vec[1])];
  else if (t.vec[1][0] == '_')
    r = getFromLable(var.at(t.vec[1]));
  else r = toInt(t.vec[1]);
  if (l < r){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Beqz(){
  int l = reg[toReg(t.vec[0])];
  if (l == 0){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Bnez(){
  int l = reg[toReg(t.vec[0])];
  if (l != 0){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Blez(){
  int l = reg[toReg(t.vec[0])];
  if (l <= 0){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Bgez(){
  int l = reg[toReg(t.vec[0])];
  if (l >= 0){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Bgtz(){
  int l = reg[toReg(t.vec[0])];
  if (l > 0){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Bltz(){
  int l = reg[toReg(t.vec[0])];
  if (l < 0){
    WB tmp(34, fun.at(t.vec[0]), 0);
    w.push(tmp);
    t.tk = NONE;
    s = "";
  }
}

void Jf(){
  WB tmp(34, fun.at(t.vec[0]), 0);
  w.push(tmp);
  t.tk = NONE;
  s = "";
}

void Jr(){
  WB tmp(34, reg[toReg(t.vec[0])], 0);
  w.push(tmp);
  t.tk = NONE;
  s = "";
}

void Jal(){
  WB tmp(34, fun.at(t.vec[0]), 0);
  w.push(tmp);
  fjal = 1;
  t.tk = NONE;
  s = "";
}

void Jalr(){
  WB tmp(34, reg[toReg(t.vec[0])], 0);
  w.push(tmp);
  fjal = 1;
  t.tk = NONE;
  s = "";
}

void La(){
  Li();
}

void Lb(){
  MA tmp(0, toReg(t.vec[0]), getAddress(t.vec[1]), 1);
  m.push(tmp);
}

void Lh(){
  MA tmp(0, toReg(t.vec[0]), getAddress(t.vec[1]), 2);
  m.push(tmp);
}

void Lw(){
  MA tmp(0, toReg(t.vec[0]), getAddress(t.vec[1]), 4);
  m.push(tmp);
}

void Sb(){
  MA tmp(1, toReg(t.vec[0]), getAddress(t.vec[1]), 1);
  m.push(tmp);
}

void Sh(){
  MA tmp(1, toReg(t.vec[0]), getAddress(t.vec[1]), 2);
  m.push(tmp);
}

void Sw(){
  MA tmp(1, toReg(t.vec[0]), getAddress(t.vec[1]), 4);
  m.push(tmp);
}

void Move(){
  WB tmp(toReg(t.vec[0]), reg[toReg(t.vec[1])], 0);
  w.push(tmp);
}

void Mfhi(){
  WB tmp(toReg(t.vec[0]), reg[32], 0);
  w.push(tmp);
}

void Mflo(){
  WB tmp(toReg(t.vec[0]), reg[33], 0);
  w.push(tmp);
}

void Nop(){
  return;
}

void Syscall(){
  char ch;
  switch(reg[2]){
    case 1: printf("%d", reg[4]); break;
    case 4: printf("%s", Data + reg[4]); break;
    case 5: scanf("%d", &reg[2]); break;
    case 8:
    int i;
      for (i = 0; ; i++){
        scanf("%c", &ch);
        if (ch == '\0') break;
        Data[reg[4] + i] = ch;
      }
      reg[5] = i;
      break;
    case 9: break;
    case 10: fend = 1; break;
    case 17:
      fend = 1;
      WB tmp(4, revalue, 0);
      w.push(tmp);
      break;
  }
}

void Execute(){
  if (t.tk == NONE) return;
  switch(t.tk){
    case 0: case 1: case 2: Add(); break;
    case 3: case 4: Sub(); break;
    case 5: case 6: Mul(); break;
    case 7: case 8: Div(); break;
    case 9: case 10: Xor(); break;
    case 11: case 12: Neg(); break;
    case 13: case 14: Rem(); break;
    case 15: Li(); break;
    case 16: Seq(); break;
    case 17: Sge(); break;
    case 18: Sgt(); break;
    case 19: Sle(); break;
    case 20: Slt(); break;
    case 21: Sne(); break;
    case 22: Bf(); break;
    case 23: Beq(); break;
    case 24: Bne(); break;
    case 25: Bge(); break;
    case 26: Ble(); break;
    case 27: Bgt(); break;
    case 28: Blt(); break;
    case 29: Beqz(); break;
    case 30: Bnez(); break;
    case 31: Blez(); break;
    case 32: Bgez(); break;
    case 33: Bgtz(); break;
    case 34: Bltz(); break;
    case 35: Jf(); break;
    case 36: Jr(); break;
    case 37: Jal(); break;
    case 38: Jalr(); break;
    case 39: La(); break;
    case 40: Lb(); break;
    case 41: Lh(); break;
    case 42: Lw(); break;
    case 43: Sb(); break;
    case 44: Sh(); break;
    case 45: Sw(); break;
    case 46: Move(); break;
    case 47: Mfhi(); break;
    case 48: Mflo(); break;
    case 49: Nop(); break;
    case 50: Syscall(); break;
  }
  t.tk = NONE;
}


#endif
