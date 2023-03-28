#ifndef BRASS_H_
#define BRASS_H_

#include <iostream>
#include <string>
using namespace std;

class Brass
{
private:
    std::string fullName;
    long acctNum;
    double balance;

public:
    // 默认构造(要么参数为空,要么都有默认值)
    Brass(const std::string &s = "NullBody", long an = -1, double bal = 0.0) { cout << "基类构造调用\n"; }
    void Deposit(double amt);
    virtual void WithDraw(double amt);
    double Balance() const;
    virtual void ViewAcct() const;
    virtual ~Brass() {}
};

class BrassPlus : public Brass
{
private:
    double maxLoan;
    double rate;
    double owesBank;

public:
    BrassPlus(const std::string &s = "NullBody", long an = -1,
              double bal = 0.0, double ml = 500,
              double r = 0.11125);
    BrassPlus(const Brass &ba, double ml = 500, double r = 0.11125);
    virtual void ViewAcct() const;
    virtual void WithDraw(double amt);
    void ResetMax(double m) { maxLoan = m; }
    void ResetRate(double r) { rate = r; }
    void ResetOwes() { owesBank = 0; }
    ~BrassPlus(){}
};

#endif