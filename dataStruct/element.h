#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <bits/stdc++.h>
using namespace std;

template <class T>
class Element;

template <class T>
std::ostream &operator<<(std::ostream &, const Element<T> &);

template <class T>
class Element {
  friend std::ostream &operator<< <>(std::ostream &, const Element<T> &);

 private:
  T m_data;

 public:
  Element(){};
  Element(T p_data) : m_data(p_data) {}
  bool operator<(const Element &a) { return this->m_data < a.m_data; }
  bool operator==(const Element &a) { return this->m_data == a.m_data; }
  bool operator>(const Element &a) { return this->m_data > a.m_data; }
  bool operator<=(const Element &a) { return this->m_data <= a.m_data; }
  bool operator>=(const Element &a) { return this->m_data >= a.m_data; }
};
template <class T>
std::ostream &operator<<(std::ostream &os, const Element<T> &a) {
  os << a.m_data;
  return os;
}

#endif