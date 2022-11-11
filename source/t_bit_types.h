#ifndef T_BIT_TYPES_H
#define T_BIT_TYPES_H
#include <iostream>

//Note 11.11.22: Закрыл глаза на возможные проблемы с выделением памяти


typedef char* cell;

class BitPtr
{
public:
    BitPtr(){}
    BitPtr(cell p_byte, int p_bit = 0) : byte(p_byte), bit(p_bit){}
public:
    cell byte;
    int bit;
public:
    int r(); // Read
    void w(int val); // Write

public:
    BitPtr operator+ (int shift);
    BitPtr operator- (int shift);
    void   operator+=(int shift);
    void   operator-=(int shift);
};


class BitSeq
{
public:
    BitSeq(){}
    /*BitSeq(uint64_t data, int size)
    {
        this->start = new char[size/8 + 1]; //динамически выделяется, значит должна удаляться
        this->size = size;
        write(data);
    }*/

    BitSeq(BitPtr p_start, int p_size) : start(p_start), size(p_size){}
    ~BitSeq(){} // Как чистить память?
public:
    BitPtr start;
    int size;
public:
    void fill(uint64_t bits);
};

std::ostream & operator << (std::ostream & stream, BitSeq seq);

// Выделятся 1024 байт памяти. В случае переполнения выделяется в два раза больше. Другого решения пока не придумал
class BitStr
{
public:
    BitStr(){
        alloc_size = 1024;
        field.start = new char[alloc_size];
        point = field.start;
    }
    ~BitStr(){
        delete[] field.start.byte;
    }
public:
    BitSeq field;
    BitPtr point;
    int size;
private:
    int alloc_size;
    void expand_field();
public:
    void write(BitSeq bseq);
    void read_to(BitSeq & seq, int up_lim);
//    BitSeq read (int up_lim);
//    BitSeq read_all();
};

#endif // T_BIT_TYPES_H
