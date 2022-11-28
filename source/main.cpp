#include <iostream>
#include "t_bit_types.h"
#include <bitset>

using namespace std;

int main()
{
    char a;
    BitSeq::init();
    BitPtr p(&a, 0);
    BitSeq seq(0b111111111111111, 16);
    cout << seq;
//    BitSeq seq2(seq);
//    cout << seq2;
//    BitSeq seq3 = seq;

//    BitStr str;// = new BitStr();
//    str.write(seq);
//    BitSeq seq2 = str.read(10);
    //str.read(10);

//    seq[0].w(1);

//    cout << bs1;
//    cout << bs2;
//    cout << bs3;
//    cout << bs4;
    return 0;
}
