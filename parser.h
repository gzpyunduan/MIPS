#ifndef _PARSER
#define _PARSER

#include <iostream>
#include <cstdio>
#include <cstring>
#include "scanner.h"
using namespace std;

int getAddress(const string &s) {
	int i = 0, mv;
	string tmp;
	if (s[i] == '-') {
		i++;
		while (s[i] != '(')
			tmp += s[i++];
		mv = -toInt(tmp);
	}
	else {
		while (s[i] != '(')
			tmp += s[i++];
		mv = toInt(tmp);
	}
	tmp = "";

	i++;
	while (s[i] != ')')
		tmp += s[i++];
	return reg[rti[tmp]] + mv;
}

struct Token {
	tokenType tk = NONE;
	int p[3];
	int size = 0;

	Token() :tk(NONE), size(0) {}

	Token(const string &s) {
		int i = 0;
		while (s[i] == '\t' || s[i] == ' ') i++;
		int h = i;
		while (s[i] != ' ' && s[i] != '\0') i++;
		string order = s.substr(h, i - h);
		if (oti.find(order) == oti.end()) tk == NONE;
		else tk = oti[order];

		while (s[i] != '\0') {
			while (s[i] == ' ' || s[i] == ',') i++;
			h = i;
			while (s[i] != ' ' && s[i] != ',' && s[i] != '\0') i++;
			string word = s.substr(h, i - h);
			if (word[0] == '_') {
				word += ':';
				if (fti.find(word) != fti.end())
					p[size++] = fun[fti[word]];
				else
					p[size++] = var[vti[word]];
			}
			else if (word[0] == '$') {
				if (size == 0)
					p[size++] = rti[word];
				else
					p[size++] = reg[rti[word]];
			}
				
			else if (word[word.size() - 1] == ')')
				p[size++] = getAddress(word);
			else p[size++] = toInt(word);
		}
	}
};

static Token t;

void InstructionDecode() {
	if (s == "\0") return;
	t = Token(s);
	//s = "";
}

#endif
