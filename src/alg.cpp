// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char a) {
  if (a == '(')
    return 0;
  else if (a == ')')
    return 1;
  else if (a == '-' || a == '+')
    return 2;
  else if (a == '/' || a == '*')
    return 3;
  else
    return -1;
}
int number(char a) {
  return (a <= '9' && a >= '0');
}
int operacia(char a) {
  return (a == '-' || a == '+' || a == '/' || a == '*');
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
    } else if (operacia(inf[i])) {
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

int eval(std::string post) {
  TStack<int, 100> stack2;
  for (int i = 0; i < post.length(); i++) {
    if (post[i] == ' ') {
      continue;
    } else if (number(post[i])) {
      int x = post[i] - '0';
      stack2.push(x);
    } else if (operacia(post[i])) {
      int x2 = stack2.get();
      stack2.pop();
      int x1 = stack2.get();
      stack2.pop();
      if (post[i] == '-') {
        stack2.push(x1 - x2);
      } else if (post[i] == '+') {
        stack2.push(x1 + x2);
      } else if (post[i] == '/') {
        stack2.push(x1 / x2);
      } else if (post[i] == '*') {
        stack2.push(x1 * x2);
      }
    }
  }
  return stack2.get();
}
