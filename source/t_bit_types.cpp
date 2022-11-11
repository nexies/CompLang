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

void BitSeq::fill(uint64_t bits)
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


//====================================================================================================
//BitStr:

void BitStr::expand_field()
{
    BitSeq n_field(new char[alloc_size * 2], alloc_size * 16);
    memcpy(n_field.start.byte, field.start.byte, sizeof(char) * alloc_size);
    delete[] field.start.byte;

    field = n_field;
    alloc_size *= 2;
}

void BitStr::write(BitSeq bseq)
{
    if(this->size + bseq.size >= alloc_size * 8)
        expand_field();

    this->size += bseq.size;
    BitPtr bseq_point = bseq.start + bseq.size - 1;
    for(int i = 0; i < bseq.size; i++){
        this->point.w(bseq_point.r());
        this->point += 1;
        bseq_point -= 1;
    }
}

void BitStr::read_to(BitSeq &seq, int up_lim)
{
    if(seq.size > this->size) // В потоке меньше битов, чем поместится в seq
        up_lim = size;

    size -= up_lim;
    seq.size = up_lim;

    BitPtr pseq = seq.start;
    for(int i = 0; i < up_lim; i++){
        this->point -= 1;
        pseq.w(point.r());
        pseq +=1;
    }
}
