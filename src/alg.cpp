// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char symbol) {
  if (symbol == '(')
    return 0;
  else if (symbol == ')')
    return 1;
  else if (symbol == '-' || symbol == '+')
    return 2;
  else if (symbol == '/' || symbol == '*')
    return 3;
  else
    return -1;
}
int number(char symbol) {
  return (symbol <= '9' && symbol >= '0');
}
int operacia(char symbol) {
  return (symbol == '-' || symbol == '+' || symbol == '/' || symbol == '*');
}

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack1;
  std::string str = "";
  for (int i = 0; i < inf.length(); i++) {
    if (number(inf[i])) {
      str += inf[i];
      str += " ";
    } else if (inf[i] == '(') {
      stack1.push(inf[i]);
    } else if (inf[i] == ')') {
      while (!stack1.isEmpty() && stack1.get() != '(') {
        str += stack1.get();
        str += " ";
        stack1.pop();
      }
      stack1.pop();
    } else if (oper(inf[i])) {
      while (!stack1.isEmpty() && prioritet(inf[i]) <= prioritet(stack1.get())) {
        str += stack1.get();
        str += " ";
        stack1.pop();
      }
      stack1.push(inf[i]);
    }
  }
  while (!stack1.isEmpty()) {
    str += stack1.get();
    str += " ";
    stack1.pop();
  }
  str.erase(str.length() - 1);
  return str;
}

int eval(std::string pref) {
  TStack<int, 100> stack2;
  for (int i = 0; i < pref.length(); i++) {
    if (pref[i] == ' ') {
      continue;
    } else if (number(pref[i])) {
      int n = pref[i] - '0';
      stack2.push(n);
    } else if (operacia(pref[i])) {
      int x2 = stack2.get();
      stack2.pop();
      int x1 = stack2.get();
      stack2.pop();
      if (pref[i] == '-') {
        stack2.push(x1 - x2);
      } else if (pref[i] == '+') {
        stack2.push(x1 + x2);
      } else if (pref[i] == '/') {
        stack2.push(x1 / x2);
      } else if (pref[i] == '*') {
        stack2.push(x1 * x2);
      }
    }
  }
  return stack2.get();
}



