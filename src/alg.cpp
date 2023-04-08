// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"


int priority(char symbol) {
  switch (symbol) {
    case ('('):
      return 0;
      break;
    case (')'):
      return 1;
      break;
    case ('+'):
      return 2;
      break;
    case ('-'):
      return 2;
      break;
    case ('*'):
      return 3;
      break;
    case ('/'):
      return 3;
      break;
    default:
      return -1;
      break;
  }
}
int calculations(char operation, int i, int j) {
  switch (operation) {
    case '+':
      return i + j;
      break;
    case '-':
      return i - j;
      break;
    case '*':
      return i * j;
      break;
    case '/':
      return i / j;
      break;
  }
  return 0;
}


std::string infx2pstfx(std::string inf) {
  TStack<char, 100> s1;
  std::string x = "";
  int prior1 = -1;
  int prior2 = 0;
  for (int k = 0; i < inf.length(); ++k) {
    prior1 = priority(s1.get());
    prior2 = priority(inf[k]);
    if (inf[k] == '\n') {
      while (priority(s1.get()) > 1) {
        x += s1.pop();
        x += " ";
      }
      s1.pop();
    }
    if (prior2 == -1) {
      x += inf[k];
      x += " ";
    } else if (prior2 == 0) {
      s1.push(inf[k]);
    } else if (prior2 == 1) {
      while (priority(s1.get()) > 0) {
        x += s1.pop();
        x += " ";
      }
      s1.pop();
    } else if (prior2 > prior1 || s1.isEmpty()) {
      s1.push(inf[k]);
    } else if (prior2 <= prior1 && prior2 > 1) {
      while (priority(s1.get()) > 1) {
        x += s1.pop();
        x += " ";
      }
      s1.push(inf[k]);
    }
  }
  while (priority(s1.get()) > 1) {
    x += s1.pop();
    x += " ";
  }
  std::string res = "";
  for (int k = 0; k < x.length() - 1; ++k) {
    res += x[k];
  }
  return res;
}

int eval(std::string pref) {
  TStack<int, 100> s2;
  int num = 0;
  int prioritet = 0;
  for (int m = 0; m < pref.length(); ++m) {
    prioritet = priority(pref[m]);
    if (prioritet == -100) {
      continue;
    }
    if (prioritet == -1) {
      s2.push(pref[m] - 48);
    } else {
      int count = 0;
      while (!(s2.isEmpty() + count)) {
        count += 1;
        int i = s2.pop();
        int j = s2.pop();
        num = calculations(j, i, pref[m]);
        s2.push(num);
      }
    }
  }
  return s2.pop();
}
