#include <iostream>
#include "t_bit_types.h"

using namespace std;

int main()
{
    BitSeq bs1(new char, 8);
    BitSeq bs2(new char, 8);
    bs1.fill(0b11001010);

    BitStr str;
    str.write(bs1);

    str.read_to(bs2, 8);
    cout << bs1;
    cout << bs2;
    return 0;
}
