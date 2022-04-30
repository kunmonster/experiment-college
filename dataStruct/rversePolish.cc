#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> pri{{'(', 0}, {'+', 1}, {'-', 1},
                             {'*', 2}, {'/', 2}, {')', 3}};

class CsatExpression {
 public:
  string _m_o_exp;

  CsatExpression(string o_exp) : _m_o_exp(o_exp) {}

  //将中缀表达式转换为后缀表达式
  string getRversePolish() {
    if (!_m_o_exp.length())
      return "";
    else {
      stack<char> op;
      string res;
      for (auto item : _m_o_exp) {
        if (isdigit(item) || isalpha(item))
          res.push_back(item);

        else if (item == '(')
          op.push(item);
        else if (item == ')') {
          while ((!op.empty()) && (op.top() != '(')) {
            res.push_back(op.top());
            op.pop();
          }
          if (!op.empty()) op.pop();
        } else {
          while (!op.empty() && (pri[op.top()] >= pri[item]) &&
                 (op.top() != '(')) {
            res.push_back(op.top());
            op.pop();
          }
          op.push(item);
        }
      }
      while (!op.empty()) {
        res.push_back(op.top());
        op.pop();
      }
      return res;
    }
  }
};

int main() {
  string expression;
  cin >> expression;
  CsatExpression* a = new CsatExpression(expression);
  cout << a->getRversePolish();
  return 0;
}