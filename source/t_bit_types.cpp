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
    if(shift < 0) return this->operator-(-shift);
    return BitPtr((this->byte + (bit + (int&)shift)/8), (this->bit + (int&)shift)%8);
}

BitPtr BitPtr::operator-(int shift)
{
    if(shift < 0) return this->operator+(-shift);
    return BitPtr(this->byte + (bit - (int&)shift - 7)/8, ((this->bit - (int&)shift)%8 + 8) % 8);
}

void BitPtr::operator+=(int shift) { *this = *this + shift; }
void BitPtr::operator-=(int shift) { *this = *this - shift; }
void BitPtr::operator++(int emp)   { *this += 1; }
void BitPtr::operator--(int emp)   { *this -= 1; }
//====================================================================================================


//====================================================================================================
//BitSeq:


void BitSeq::alloc_more(int bytes)
{
    cell new_start = new char[_allocated + bytes];
    memcpy(new_start, this->_start, _allocated);
    delete[] _start;
    _start = new_start;
    _allocated += bytes;
}

void BitSeq::alloc_less(int bytes)
{
    if(bytes >= _size){
        this->_size = 0;
        this->_allocated = 0;
        delete[] this->_start;
        return;
    }
    cell new_start = new char[_allocated - bytes];
    memcpy(new_start, this->_start, bytes);
    delete[] _start;
    _start = new_start;
    _allocated -= bytes;
}

void BitSeq::append(BitSeq &other)
{
    if(other.size() + this->_size > _allocated * 8)
        this->alloc_more(other.allocated());
    this->_size += other.size();

    BitPtr ptr_other = other.begin();
    BitPtr ptr_this  = this->end() + 1;

    for(int i = 0; i < other.size(); i++){
        ptr_this.w(ptr_other.r());
        ptr_this++;
        ptr_other++;
    }

}

BitPtr BitSeq::operator [](int pos)
{
    assert(pos < _size);
    return BitPtr(_start, 0) + pos;
}


//void BitSeq::fill(uint64_t bits)
//{
//    BitPtr point = this->start;
//    for(int i = 0; i < 64 && i < this->size; i++){
//        point.w(bits & (1ul << i));
//        point += 1;
//    }

//}

std::ostream & operator << (std::ostream & stream, BitSeq seq){
    stream << "size: " << seq.size() << ", alloc_size: " << seq.allocated();
    stream << ", data: ";
    BitPtr point = seq.end();
    for(int i = 0; i < seq.size(); i++){
        stream << point.r();
        point -= 1;
    }
    return stream << endl;
}

//====================================================================================================


//====================================================================================================
//BitStr:
