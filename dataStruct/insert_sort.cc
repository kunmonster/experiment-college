#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Element
{

private:
    T m_data;

public:
    Element(T p_data=NULL) : m_data(p_data) {}
    bool operator<(const Element &a)
    {
        return this->m_data < a.m_data;
    }
    bool operator == (const Element &a)
    {
        return this->m_data == a.m_data;
    }
    bool operator>(const Element &a)
    {
        return this->m_data > a.m_data;
    }
    bool operator <= (const Element & a){
        return this->m_data <= a.m_data;
    }
    bool operator >= (const Element & a){
        return this->m_data >= a.m_data;
    }
    friend ostream & operator <<(ostream & os,Element & a);

};
template<typename T>
ostream & operator <<(ostream & os, const Element<T>& a){
        os<<a.m_data;
        return os;
    }

/***
 * 直接插入排序,升序
 * para : 数组,数组长度
 * **/
template<typename T>
void stright_insert_sort(Element<T> *arr, int len)
{
    if (len <= 1)
        return;
    // set the first element as the standard
    Element<T> guard;
    int j = 0;
    for (int i = 1; i < len; i++)
    {
        if (*(arr + i) < *(arr + i - 1))
        {
            //当前元素小于前一个元素
            guard = *(arr + i);
            for (j = (i - 1); j >= 0 && arr[j] >= arr[i]; --j)
                arr[j + 1] = arr[j];
            arr[j + 1] = guard;
        }
    }
}

int main()
{
    Element<int> *arr = new Element<int>[10]{9, 1, 3, 4, 5, 6, 5, 1, 6, 7};
    stright_insert_sort(arr, 10);
    for(int i=0;i<9;i++){
        cout<<*(arr+i);
    }
    return 0;
}