#include "t_bit_types.h"
#include <cassert>

using namespace std;

//====================================================================================================
//BitPtr:

int BitPtr::r() /* Read */
{ return ((*byte)>>bit)&0b1; }

void BitPtr::w(int val) /* Write */
{
    if(val)
        (*byte) |=  char(1)<<(bit);
    else
        (*byte) &= ~(char(1)<<(bit));
}

BitPtr BitPtr::operator+(int shift)
{
    assert(shift >= 0);
    return BitPtr((this->byte + (bit + (int&)shift)/8), (this->bit + (int&)shift)%8);
}

BitPtr BitPtr::operator-(int shift)
{
    assert(shift >= 0);
    return BitPtr(this->byte + (bit - (int&)shift - 7)/8, ((this->bit - (int&)shift)%8 + 8) % 8);
}

void BitPtr::operator+=(int shift)
{
    *this = *this + shift;
}

void BitPtr::operator-=(int shift)
{
    *this = *this - shift;
}
//====================================================================================================


//====================================================================================================
//BitSeq:

void BitSeq::write(uint64_t bits)
{
    BitPtr point = this->start;
    for(int i = 0; i < 64 && i < this->size; i++){
        point.w(bits & (1ul << i));
        point += 1;
    }

}

std::ostream & operator << (std::ostream & stream, BitSeq seq){
    stream << "byte: " << (uint64_t&)seq.start.byte << ", bit: " << seq.start.bit << ", size: " << seq.size;
    stream << ", data: ";
    BitPtr point = seq.start + seq.size - 1;
    for(int i = 0; i < seq.size; i++){
        stream << point.r();
        point -= 1;
    }
    return stream << endl;
}

//====================================================================================================
