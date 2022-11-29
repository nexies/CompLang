#include <iostream>
#include "t_bit_types.h"
#include <bitset>

using namespace std;

void run(BitSeq sequence)
{
    BitStr str;
    str.write(sequence);

}


int main()
{
    char a;
    BitSeq::init();
    BitPtr p(&a, 0);
    BitSeq seq(0b1111010001001111, 16);
    BitSeq seq2(seq);

    BitStr str;
    str.write(seq);
    str.check_container();
    cout << (seq2 = str.read(16));
    str.check_container();

    str.write(seq);
    str.check_container();
    str.write(seq);
    str.check_container();


    return 0;
}
