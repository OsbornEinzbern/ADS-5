// Copyright 2021 NNTU-CS
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
  std::string result(1, postfix[0]);
  for (int i = 1; i < postfix.length() - 1; i++) {
    result += " ";
    result += postfix[i];
  }
  result += " ";
  result += postfix[postfix.length() - 1];
  return result;
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
int eval(std::string pref) {
  std::string a(1, pref[0]);
  for (int i = 2; i < pref.length(); i += 2) {
    a += pref[i];
  }
  if (a[a.length() - 1] != pref[pref.length() - 1]) {
    a += pref[pref.length() - 1];
  }
  pref = a;
  std::stack<std::string> mstack;
  for (char cur : pref) {
    if (isdigit(cur)) {
      mstack.push(std::string(1, cur));
    } else {
      if (!isOperand(cur)) {
      std::string right = mstack.top();
      mstack.pop();
      std::string left = mstack.top();
      mstack.pop();
      int res = Eval(left, cur, right);
      mstack.push(std::to_string(res));
    }
    }
  }
  return stoi(mstack.top());
}
