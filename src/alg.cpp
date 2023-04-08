// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPrior(char character) {
    switch (character) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+':
        return 2;
    case '-':
        return 2;
    case '*':
        return 3;
    case '/':
        return 3;
    case ' ':
        return -100;
    }
    return -1;
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> s1;
    std::string outExpr = "";
    int PriopOFTop = -1;
    int prioritet = 0;
    for (int i = 0; i < inf.length(); ++i) {
        prioritet = getPrior(inf[i]);
        PriopOFTop = getPrior(s1.get());
        if (inf[i] == '\n') {
            while (getPrior(s1.get()) > 1) {
                outExpr += s1.pop();
                outExpr += " ";
            }
            s1.pop();
        }
        if (prioritet == -1) {
            outExpr += inf[i];
            outExpr += " ";
        } else if (prioritet == 0) {
            s1.push(inf[i]);
        } else if (prioritet == 1) {
            while (getPrior(s1.get()) > 0) {
                outExpr += s1.pop();
                outExpr += " ";
            }
            s1.pop();
        } else if (prioritet > PriopOFTop || s1.isEmpty()) {
            s1.push(inf[i]);
        } else if (prioritet <= PriopOFTop && prioritet > 1) {
            while (getPrior(s1.get()) > 1) {
                outExpr += s1.pop();
                outExpr += " ";
            }
            s1.push(inf[i]);
        }
    }
    while (getPrior(s1.get()) > 1) {
        outExpr += s1.pop();
        outExpr += " ";
    }
    std::string result = "";
    for (int i = 0; i < outExpr.length() - 1; ++i) {
        result += outExpr[i];
    }
    return result;
}

int operatoR(int n1, int n2, char sign) {
    switch (sign) {
    case '+':
        return n1 + n2;
    case '-':
        return n1 - n2;
    case '*':
        return n1 * n2;
    case '/':
        return n1 / n2;
    }
    return 0;
}
int eval(std::string pref) {
    TStack<int, 100> s2;
    int num = 0;
    int prioritet = 0;
    for (int i = 0; i < pref.length(); ++i) {
        prioritet = getPrior(pref[i]);
        if (prioritet == -100) {
            continue;
        }
        if (prioritet == -1) {
            s2.push(pref[i] - 48);
        } else {
            int count = 0;
            while (!(s2.isEmpty() + count)) {
                count += 1;
                int n1 = s2.pop();
                int n2 = s2.pop();
                num = operatoR(n2, n1, pref[i]);
                s2.push(num);
            }
        }
    }
    return s2.pop();
}
