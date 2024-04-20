// Copyright 2021 NNTU-CS
// NOLINT
#include <climits>
#include <iostream>
#include <stack>
#include <string>

int prec(char c) {
  if (c == '*' || c == '/') {
    return 3;
  }
  if (c == '+' || c == '-') {
    return 4;
  }
  if (c == '&') {
    return 8;
  }
  if (c == '^') {
    return 9;
  }
  if (c == '|') {
    return 10;
  }
  return INT_MAX;
}
bool isOperand(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
         (c >= '0' && c <= '9');
}
std::string infx2pstfx(std::string inf) {
  std::stack<char> s;
  std::string postfix;
  for (char c : inf) {
    if (c == '(') {
      s.push(c);
    } else if (c == ')') {
      while (s.top() != '(') {
        postfix.push_back(s.top());
        s.pop();
      }
      s.pop();
    } else if (isOperand(c)) {
      postfix.push_back(c);
    } else {
      while (!s.empty() && prec(c) >= prec(s.top())) {
        postfix.push_back(s.top());
        s.pop();
      }
      s.push(c);
    }
  }
  while (!s.empty()) {
    postfix.push_back(s.top());
    s.pop();
  }
  return postfix;
}
int Eval(const std::string& left, char oper, const std::string& right) {
  int a = stoi(left);
  int b = stoi(right);
  switch (oper) {
    case '*':
      return a * b;
    case '/':
      return a / b;
    case '+':
      return a + b;
    case '-':
      return a - b;
    default:
      return 0;
  }
}
int eval(const std::string& postfix) {
  std::stack<std::string> mstack;
  for (char cur : postfix) {
    if (isdigit(cur)) 
      mstack.push(std::string(1, cur));

    else if (!isOperand(cur)) {
      std::string right = mstack.top();
      mstack.pop();
      std::string left = mstack.top();
      mstack.pop();
      int res = Eval(left, cur, right);
      mstack.push(std::to_string(res));
    }
  }
  return stoi(mstack.top());
}
