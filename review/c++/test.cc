#include <iostream>
using namespace std;
#include "../c++/brass.h"

int main()
{
    Brass dom("Dominic Banker",11224,4183.45);
    BrassPlus dot("Dorothy Bankers",12118,2592.00);

    Brass & b1_ref = dom;
    Brass & b2_ref = dot;

    b1_ref.ViewAcct();
    b2_ref.ViewAcct();

    return 0;
}