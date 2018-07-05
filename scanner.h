#ifndef _SCANNER
#define _SCANNER

#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

static const int MAX = pow(2, 32);
static map<string, int> var;
static map<string, int> fun;
static char Data[3000000];
static char Static[1500000];
static string Text[1000];
static int reg[35];
static bool fjal = 0;
static bool fend = 0;
static int revalue;
static string s;
int posd, post;

int toIntTen(const string &s){
  int ans = 0;
  for (int i = 0; i < s.size(); i++)
    ans = ans * 10 + s[i] - '0';
  return ans;
}

void toChar(char *c, int pos, int size, int num){
  for (int i = 0; i < size; i++)
    c[pos + i] = (num >> (8 * i)) & 255;
}

void varieble(){
  string s = "";
  while(true){
    while(true){
      getline(cin, s);
      if (s[2] != '.') break;

      int i;
      for (i = 3; s[i] != ' '; i++);
      string opt = s.substr(3, i - 3);

      if (opt == "align"){
        int num = pow(2, s[9] - '0');
        if (posd % num != 0) posd = (posd / num + 1) * num;
      }
      else if (opt == "ascii"){
        int j;
        for (j = 9; s[j] != '\0'; j++);
        for (int k = 0; k < j - 9; k++)
          Static[posd++] = s[9 + k];
      }
      else if (opt == "asciiz"){
        int j;
        for (j = 10; s[j] != '\0'; j++);
        for (int k = 0; k < j - 10; k++)
          Static[posd++] = s[9 + k];
        Static[posd++] = '\0';
      }
      else if (opt == "byte"){
        int j = 8;
        int p = 0;
        string sd;
        while(true){
          if (s[j] != ',' && s[j] != '\0') sd[p++] = s[j];
          else {
            toChar(Static, posd++, 1, toIntTen(sd));
            sd = "";
            p = 0;
          }
          if (s[j] == '\0') break;
          j++;
        }
      }
      else if (opt == "half"){
        int j = 8;
        int p = 0;
        string sd;
        while(true){
          if (s[j] != ',' && s[j] != '\0') sd[p++] = s[j];
          else {
            toChar(Static, posd, 2, toIntTen(sd));
            sd = "";
            p = 0;
          }
          if (s[j] == '\0') break;
          j++;
        }
        posd += 2;
      }
      else if (opt == "word"){
        int j = 8;
        int p = 0;
        string sd;
        while(true){
          if (s[j] != ',' && s[j] != '\0') sd[p++] = s[j];
          else {
            toChar(Static, posd, 4, toIntTen(sd));
            sd = "";
            p = 0;
          }
          if (s[j] == '\0') break;
          j++;
        }
        posd += 4;
      }
      else if (opt == "space"){
        posd += s[9] - '0';
      }
      else if (opt == "text" || opt == "data")
        return;
    }
    var.insert(pair<string, int>(s, posd));
  }
}

void function(){
  while(getline(cin, s)){
    if (s == "  .data" || s == "  .text") break;
    if (s[s.size() - 1] = ':'){
      if (s == "main:") reg[34] = post;
      else fun.insert(pair<string, int>(s, post));
    }
    Text[post++] = s;
  }
}

void preProcess(){
  getline(cin, s);
  while(s != "\0"){
    if (s == "  .data") varieble();
    if (s == "  .text") function();
  }
  reg[30] = -1;
}

void InstructionFetch(){
  if (fend) return;
  s = Text[reg[34]++];
  if (fjal){
    reg[34] = reg[30];
    fjal = 0;
  }
}

#endif
