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
    return BitPtr((this->byte + ((int)bit + shift)/8), (this->bit + (uint8_t)shift)%8);
}

BitPtr BitPtr::operator-(int shift)
{
    if(shift < 0) return this->operator+(-shift);
    return BitPtr(this->byte + (bit - (int&)shift - 7)/8, ((this->bit - (uint8_t)shift)%8)); // ??
}

void BitPtr::operator+=(int shift) { *this = *this + shift; }
void BitPtr::operator-=(int shift) { *this = *this - shift; }
void BitPtr::operator++(int emp)   { *this += 1; }
void BitPtr::operator--(int emp)   { *this -= 1; }
void BitPtr::operator++()          { *this += 1; }
void BitPtr::operator--()          { *this -= 1; }
//====================================================================================================


//====================================================================================================
//BitSeq:

int BitSeq::empty;
int BitSeq::by_size;
int BitSeq::by_data_size;
int BitSeq::by_ptr_size;
int BitSeq::by_const_other;
int BitSeq::by_other;
int BitSeq::deletions;

BitSeq::BitSeq(){empty++;}

BitSeq::BitSeq(int p_size) {
    this->_size = p_size;
    this->_allocated = p_size/8 + 1;
    this->_start = new char[_allocated];
    for(int i = 0; i < _allocated; i++)
        _start[i] = 0;
    by_size++;
}

BitSeq::BitSeq(uint64_t p_data, int p_size) : BitSeq(p_size) {
    BitPtr point(_start, 0);
    for(int i = 0; i < p_size; i++){
        point.w(p_data & (1ul << i));
        point++;
    }
    by_data_size++;
}

BitSeq::BitSeq(BitPtr p_ptrdata, int p_size) : BitSeq(p_size) {
    BitPtr point(_start, 0);
    for(int i = 0; i < p_size; i++){
        point.w(p_ptrdata.r());
        point++;
        p_ptrdata++;
    }
    by_ptr_size++;
}

BitSeq::BitSeq(const BitSeq &other){ // : BitSeq(other.begin(), other.size()){
    this->copy(other);
    by_const_other++;
}

BitSeq::BitSeq(BitSeq &other){// : BitSeq(other.begin(), other.size()) {
    this->copy(other);
    by_other++;
}

BitSeq::~BitSeq(){
    if(_allocated > 0) delete[] _start;
    deletions ++;
}

void BitSeq::copy(const BitSeq &other)
{
    if(_allocated > 0) delete[] _start;
    this->_size = other.size();
    this->_allocated = _size/8 + 1;
    this->_start = new char[_allocated];
    for(int i = 0; i < _allocated; i++)
        _start[i] = other._start[i];
}

int BitSeq::size()      const { return _size; }

int BitSeq::allocated() const { return _allocated; }

BitPtr BitSeq::begin()  const { return BitPtr(_start, 0); }

BitPtr BitSeq::end()    const { return BitPtr(_start, 0) + _size - 1; }

void BitSeq::alloc_more(int bytes)
{
    char* new_start = new char[_allocated + bytes];
//    char* nn_start  = new char[10];
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

void BitSeq::append(BitSeq const &other)
{
    if(other.size() + this->_size > _allocated * 8)
        this->alloc_more(other.allocated());

    BitPtr ptr_other = other.begin();
    BitPtr ptr_this  = this->end() + 1;

    for(int i = 0; i < other.size(); i++){
        ptr_this.w(ptr_other.r());
        ptr_this++;
        ptr_other++;
    }
    this->_size += other.size();
}

BitSeq BitSeq::cut_from_end(int size)
{
    size = size > this->_size ? this->_size : size;
    this->_size -= size;
    return BitSeq(this->end() + 1, size);

//    BitSeq out(size);

//    BitPtr this_end = this->end();
//    BitPtr out_end  = out.end();

//    for(int i = 0; i < size; i++){
//        out_end.w(this_end.r());
//        out_end--;
//        this_end--;
//    }
//    return out;
}

BitPtr BitSeq::operator [](int pos)
{
    assert(pos < _size);
    return BitPtr(_start, 0) + pos;
}

BitSeq& BitSeq::operator =(const BitSeq &other)
{
    this->copy(other);
    return *this;
}

//void BitSeq::operator =(const BitSeq &other)
//{
//    if(_allocated > 0) delete[] _start;
//    this->_allocated = 0;

//    this->append(other);
//}


//void BitSeq::fill(uint64_t bits)
//{
//    BitPtr point = this->start;
//    for(int i = 0; i < 64 && i < this->size; i++){
//        point.w(bits & (1ul << i));
//        point += 1;
//    }

//}

std::ostream & operator << (std::ostream & stream, BitSeq &seq){
    stream << "size: " << seq.size() << " bits, alloc_size: " << seq.allocated() << " bytes";
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

void BitStr::write(BitSeq & bseq)
{
    if(_field.allocated() * 8 < _point_pos + bseq.size())
        _field.alloc_more(bseq.size() / 8 + 1);

    for(int i = 0; i < bseq.size(); i++){
        _point.w(bseq[i].r());
        _point++;
    }
    _point_pos += bseq.size();
}

BitSeq BitStr::read(int up_lim)
{
    up_lim = up_lim > _point_pos ? _point_pos : up_lim;
    BitSeq out(up_lim);
    for(int i = up_lim - 1; i >= 0; i--){
        out[i].w(_point.r());
        _point--;
    }
    return out;
}

BitSeq BitStr::read_all()
{
    return _field;
}
