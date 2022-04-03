// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char op) {
  switch (op) {
    case '(': return 0;
    case ')': return 1;
    case '+': case '-': return 2;
    case '*': case '/': return 3;
    case ' ': return 5;
    default: return 4;
  }
}
int calcul(char o, int a, int b) {
  switch (o) {
    case '+': return (a + b);
    case '-': return (a - b);
    case '*': return (a * b);
    case '/':
      if (b != 0)
        return a / b;
    default: return 0;
  }
}

std::string infx2pstfx(std::string inf) {
  TStack <char, 100> stack;
    std::string result = "";
  for (int j = 0; j < inf.length(); j++) {
    char s = inf[j];
    int sPrior = prior(s);
    if (sPrior == 4) {
      result += s;
      result += ' ';
    } else {
      bool empty = stack.isEmpty();
      int priorTop = prior(stack.get());
      if (sPrior == 0 || sPrior > priorTop || empty) {
        stack.push(s);
      } else if (sPrior == 1) {
        while (prior(stack.get()) != 0) {
          result += stack.get();
          result += ' ';
          stack.pop();
        }
        stack.pop();
      } else if (sPrior <= prior(stack.get())) {
        if (sPrior <= prior(stack.get())) {
          result += stack.get();
          result += ' ';
          stack.pop();
        }
        stack.push(s);
      }
    }
  }
  if (!stack.isEmpty()) {
    while (!stack.isEmpty()) {
      result += stack.get();
          result += ' ';
          stack.pop();
    }
    result.pop_back();
  }
  return result;
  return std::string("");
}

int eval(std::string pref) {
  TStack <int, 100> stack0;
  int result = 0;
  for (int j = 0; j < pref.length(); j++) {
    char s = pref[j];
    if (prior(s) == 4) {
      stack0.push(s - '0');
    } else if (prior(s) < 4) {
      int c1 = stack0.get();
      stack0.pop();
      int c2 = stack0.get();
      stack0.pop();
      stack0.push(calcul(s, c1, c2));
    }
  }
  result = stack0.get();
  return result;
  return 0;
}
