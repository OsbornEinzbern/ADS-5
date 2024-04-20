// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <stack>
#include <string>
#include <climits>

using namespace std;

// Вспомогательная функция для возврата приоритета данного оператора.
int prec(char c)
{
    // Умножение и деление
    if (c == '*' || c == '/') {
        return 3;
    }

    // Сложение и вычитание
    if (c == '+' || c == '-') {
        return 4;
    }

    // Bitwise AND
    if (c == '&') {
        return 8;
    }

    // Побитовое XOR (исключающее или)
    if (c == '^') {
        return 9;
    }

    // Побитовое ИЛИ (включающее или)
    if (c == '|') {
        return 10;
    }

    // добавить больше операторов, если нужно

    return INT_MAX;            // для открывающей скобки '('
}

// Вспомогательная функция для проверки, является ли данный токен операндом
bool isOperand(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

//В теории готово(выводит - postfix)
string infx2pstfx(string inf) { //из инфиксной в постфиксную

    // создаем пустой stack для хранения операторов
    stack<char> s;

    // создаем строку для хранения постфиксного выражения
    string postfix;

    // обрабатываем инфиксное выражение слева направо
    for (char c : inf)
    {
        // Случай 1. Если текущий токен является открывающей скобкой '(',
        // помещаем его в stack
        if (c == '(') {
            s.push(c);
        }

        // Случай 2. Если текущий токен является закрывающей скобкой ')'
        else if (c == ')')
        {
            // извлекаем токены из stack до тех пор, пока не появится соответствующая открывающая скобка '('
            // устранен. Добавляйте каждый оператор в конец постфиксного выражения
            while (s.top() != '(')
            {
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop();
        }

        // Случай 3. Если текущий токен является операндом, добавляем его в конец
        // постфиксное выражение
        else if (isOperand(c)) {
            postfix.push_back(c);
        }

        // Случай 4. Если текущий токен является оператором
        else {
            // удаляем из stack операторы с более высоким или равным приоритетом
            // и добавляем их в конец постфиксного выражения
            while (!s.empty() && prec(c) >= prec(s.top()))
            {
                postfix.push_back(s.top());
                s.pop();
            }

            // наконец, помещаем текущий оператор на вершину stack
            s.push(c);
        }
    }

    // добавляем все оставшиеся операторы в stack в конце постфиксного выражения
    while (!s.empty())
    {
        postfix.push_back(s.top());
        s.pop();
    }

    // возвращаем постфиксное выражение
    return postfix;
}

int Eval(const string& left, char oper, const  string& right)
{
    int a = stoi(left);
    int b = stoi(right);
    switch (oper)
    {
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
//[2]саб-функция для оперирования с постфиксной формой

//В теории готово
int eval(const string& postfix) { //вычисление постфиксной
    stack<string> mstack;
    for (char cur : postfix)
    {
        if (isdigit(cur))
            mstack.push(string(1, cur));

        else if (!isOperand(cur))
        {
            string right = mstack.top();
            mstack.pop();
            string left = mstack.top();
            mstack.pop();
            int res = Eval(left, cur, right);
            mstack.push(to_string(res));
        }
    }
    return  stoi(mstack.top());
}
