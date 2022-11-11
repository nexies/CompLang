#include <iostream>
#include "t_bit_types.h"

using namespace std;

int main()
{

    char a = 0;
    char * pa = &a; // Игнорировать ворнинг?
    BitPtr bp(pa, 0);
    bp.w(1);

    BitSeq bs1(bp, 8);
    BitSeq bs2(0b110101, 16);

    cout << bs1;
    cout << bs2;
    return 0;
}
