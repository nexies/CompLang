#ifndef T_BIT_TYPES_H
#define T_BIT_TYPES_H
#include <iostream>

typedef char* cell;

class BitPtr  // Хорошо бы уметь считывать или записывать что-то в этот бит !
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


class BitSeq   //Хорошо бы выделять под это дело память ! или нет?
{
public:
    BitSeq(){}
    BitSeq(uint64_t data, int size)
    {
        this->start.byte = new char[size/8 + 1];
        this->start.bit = 0;
        this->size = size;
        write(data);
    }
    BitSeq(BitPtr p_start, int p_size) : start(p_start), size(p_size){}
    ~BitSeq(){} // Как чистить память?
public:
    BitPtr start;
    int size;
public:
    void write(uint64_t bits);
};

std::ostream & operator << (std::ostream & stream, BitSeq seq);

class BitStr
{
public:
    BitStr(){}
    ~BitStr(){} // Надо чистить поле. Как?
public:
    // Нужно выделять память для field? Мы не знаем, какого оно должно быть размера, к тому же оно динамически меняется
    BitSeq field;
    BitPtr point;
private:
    BitPtr expand_field(int bytes);  //Возвращает указатель на бит, после которого идет новое поле
public:
    void write(BitSeq bseq);
    BitSeq read(int up_lim);
    BitSeq read_all;
};

#endif // T_BIT_TYPES_H
