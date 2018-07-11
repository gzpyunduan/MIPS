#ifndef _SCANNER
#define _SCANNER

#include "init.h"

struct Line {
	optType tk = NONE;
	int p[4];
	dataType d[4];
	int size = 0;

	Line() :tk(NONE), size(0) {}

	Line(const string &s) {
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
				if (fti.find(word) != fti.end()) {
					d[size] = FUN;
					p[size++] = fti[word];
				}
				else {
					d[size] = VAR;
					p[size++] = vti[word];
				}
			}
			else if (word[0] == '$') {
				d[size] = REG;
				if (size == 0)
					p[size++] = rti[word];
				else
					p[size++] = rti[word];
			}

			else if (word[word.size() - 1] == ')') {
				int j = 0;
				while (word[j] != '(') j++;
				d[size] = NUM;
				p[size++] = toInt(word.substr(0, j));
				d[size] = REG;
				p[size++] = rti[word.substr(j + 1, word.size() - j - 2)];
			}
			else {
				d[size] = NUM;
				p[size++] = toInt(word);
			}
		}
	}
};

static Line l;
static Line ls[10000];

void InstructionFetch(){
  if (fend) return;
  //cout << reg[34] << ' ';
  s = Text[reg[34]];
  if (ls[reg[34]].tk == NONE) {
	  l = Line(s);
	  ls[reg[34]] = l;
  }
  else l = ls[reg[34]];
  reg[34]++;
  //cout << s << endl;
}

#endif
