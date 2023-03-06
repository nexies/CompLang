#include "lindex_basic_bit_types.h"
#include <cassert>
#include <cstring>

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
    return BitPtr(this->byte + ((int)bit - shift - 7)/8, (uint8_t)(this->bit - (uint8_t)shift) % 8); // ??
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

//int BitSeq::empty;
//int BitSeq::by_size;
//int BitSeq::by_data_size;
//int BitSeq::by_ptr_size;
//int BitSeq::by_const_other;
//int BitSeq::by_other;
//int BitSeq::deletions;

BitSeq::BitSeq(){/*empty++;*/}

BitSeq::BitSeq(int p_size) {
    this->_size = p_size;
    this->_allocated = (p_size-1)/8 + 1;
    this->_start = new char[_allocated];
    for(int i = 0; i < _allocated; i++)
        _start[i] = 0;
//    by_size++;
}

BitSeq::BitSeq(uint64_t p_data, int p_size) : BitSeq(p_size) {
    BitPtr point(_start, 0);
    for(int i = _allocated-1; i >= 0; i--){
        this->_start[_allocated - i - 1] = (p_data >> (i * 8)) & 0xFF;
    }
}

BitSeq::BitSeq(BitPtr p_ptrdata, int p_size) : BitSeq(p_size) {
    BitPtr point(_start, 0);
    for(int i = 0; i < p_size; i++){
        point.w(p_ptrdata.r());
        point++;
        p_ptrdata++;
    }
//    by_ptr_size++;
}

BitSeq::BitSeq(const BitSeq &other){ // : BitSeq(other.begin(), other.size()){
    this->copy(other);
//    by_const_other++;
}

BitSeq::BitSeq(BitSeq &other){// : BitSeq(other.begin(), other.size()) {
    this->copy(other);
//    by_other++;
}

BitSeq::~BitSeq(){
    if(_allocated > 0) delete[] _start;
//    deletions ++;
}

void BitSeq::copy(const BitSeq &other)
{
    if(_allocated > 0) delete[] _start;
    this->_size = other.bit_size();
    this->_allocated = (_size-1)/8 + 1;
    this->_start = new char[_allocated];
    for(int i = 0; i < _allocated; i++)
        _start[i] = other._start[i];
}

int BitSeq::bit_size()  const { return _size; }

int BitSeq::byte_size() const { return (_size-1)/8 + 1; }

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
    char* new_start = new char[_allocated - bytes];
    memcpy(new_start, this->_start, bytes);
    delete[] _start;
    _start = new_start;
    _allocated -= bytes;
}

void BitSeq::append(BitSeq const &other)
{
    if(other.bit_size() + this->_size > _allocated * 8)
        this->alloc_more(other.allocated());

    BitPtr ptr_other = other.begin();
    BitPtr ptr_this  = this->end() + 1;

    for(int i = 0; i < other.bit_size(); i++){
        ptr_this.w(ptr_other.r());
        ptr_this++;
        ptr_other++;
    }
    this->_size += other.bit_size();
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

bool BitSeq::operator==(const BitSeq &other) const
{
    if(this->bit_size() != other.bit_size())
        return false;

    return memcmp(this->begin().byte, other.begin().byte, this->byte_size()) == 0;
}

bool BitSeq::operator!=(const BitSeq &other) const
{
    return !(this->operator==(other));
}

bool BitSeq::operator>(const BitSeq &other) const
{
    if(this->bit_size() == other.bit_size()){
        BitPtr tp = this->begin();
        BitPtr op = other.begin();
        for(int i = 0; i < this->bit_size(); i++){
            if(tp.r() == op.r()){
                tp++; op++;
            }
            else
                return tp.r() > op.r();
        }
    }
    return this->bit_size() > other.bit_size();

}

bool BitSeq::operator<(const BitSeq &other) const
{
    return other > *this;
}

bool BitSeq::operator>=(const BitSeq &other) const
{
    return *this > other || *this == other;
}

bool BitSeq::operator<=(const BitSeq &other) const
{
    return other > *this || *this == other;
}

BitSeq BitSeq::operator+ (const BitSeq & other) const{
    BitSeq out(*this);
    out.append(other);
    return out;
}

BitSeq& BitSeq::operator+= (const BitSeq &other){
    *this = *this+other;
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

std::ostream & operator << (std::ostream & stream, BitSeq seq){
    printf("address: %i, ", seq.begin().byte);
    stream << "size: " << seq.bit_size() << " bits, alloc_size: " << seq.allocated() << " bytes";
    stream << ", data: ";
    BitPtr point = seq.begin();
    for(int i = 0; i < seq.bit_size(); i++){
        stream << point.r();
        point += 1;
    }
    return stream << endl;
}

//====================================================================================================


//====================================================================================================
//BitStr:

void BitStr::reset()
{
    this->_field = BitSeq(8);
    this->_point_pos = 0;
}

void BitStr::write(const BitSeq & bseq)
{
    this->_field.append(bseq);
    this->_point_pos += bseq.bit_size();
}

void BitStr::write(BitSeq &bseq)
{
    this->_field.append(bseq);
    this->_point_pos += bseq.bit_size();
}

BitSeq BitStr::check(int up_lim)
{
    up_lim = up_lim > _point_pos ? _point_pos : up_lim;
    BitPtr point = _field.begin() + (len() - _point_pos);
    return BitSeq(point, up_lim);
}

void BitStr::skip(int up_lim)
{
    up_lim = up_lim > _point_pos ? _point_pos : up_lim;
    _point_pos -= up_lim;
}

BitSeq BitStr::read(int up_lim)
{
    up_lim = up_lim > _point_pos ? _point_pos : up_lim;
    BitPtr point = _field.begin() + (len() - _point_pos);
    _point_pos -= up_lim;
    BitSeq out(point, up_lim);

    if(_point_pos == 0)
        this->reset();
    return out;
}

BitSeq BitStr::read_all()
{
    BitSeq out = _field;
    this->reset();
    return out;
}

void BitStr::check_container()
{
    BitPtr point = _field.begin();

    cout << "container : ";
    for(int i = 0; i < _field.allocated() * 8; i++)
        cout << (point + i).r();
    cout << endl;

    string pointer_line = "pointer   : " + (_point_pos > 0 ? string(len() - _point_pos, ' ') + "^" : "-");
    cout << pointer_line << endl;
}

BitStr::operator bool() const
{
    return !(this->eof());
}


BitStr & operator << (BitStr & stream, BitSeq & bseq){
    stream.write(bseq);
    return stream;
}
