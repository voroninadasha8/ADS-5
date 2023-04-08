// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPrior(char c) {
    if (c == '(') return 0;
    else if (c == ')') return 1;
    else if (c == '+' || c == '-') return 2;
    else if (c == '*' || c == '/') return 3;
    else
        return -1;
}

bool isDigit(char c) {
    return ('0' <= c && c <= '9');
}

bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string pstfx = "";
    for (int i = 0; i < inf.length(); i++) {
        char ch = inf[i];
        if (isDigit(ch)) {
            pstfx += ch;
            pstfx += " ";
        } else if (ch == '(') {
            stack1.push(ch);
        } else if (ch == ')') {
            while (!stack1.isEmpty() && stack1.get() != '(') {
                pstfx += stack1.get();
                pstfx += " ";
                stack1.pop();
            }
            stack1.pop();
        } else if (isOperator(ch)) {
            while (!stack1.isEmpty() &&
                   getPrior(ch) <= getPrior(stack1.get())) {
                pstfx += stack1.get();
                pstfx += " ";
                stack1.pop();
            }
            stack1.push(ch);
        }
    }
    while (!stack1.isEmpty()) {
        pstfx += stack1.get();
        pstfx += " ";
        stack1.pop();
    }
    pstfx.erase(pstfx.length() - 1);
    return pstfx;
}

int eval(std::string post) {
    TStack<int, 100> stack2;
    for (int i = 0; i < post.length(); i++) {
        char ch = post[i];
        if (ch == ' ') {
            continue;
        } else if (isDigit(ch)) {
            int num = ch - '0';
            stack2.push(num);
        } else if (isOperator(ch)) {
            int num2 = stack2.get();
            stack2.pop();
            int num1 = stack2.get();
            stack2.pop();
            if (ch == '+') {
                stack2.push(num1 + num2);
            } else if (ch == '-') {
                stack2.push(num1 - num2);
            } else if (ch == '*') {
                stack2.push(num1 * num2);
            } else if (ch == '/') {
                stack2.push(num1 / num2);
            }
        }
    }
    return stack2.get();
}
