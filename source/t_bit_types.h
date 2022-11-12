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
    void   operator++(int epm);
    void   operator--(int emp);
};


// Класс-контейнер. BitSeq всегда начинается с первого бита в байте.
/*
 *      1) Всегда начинается с первого бита в байте
 *      2) Автоматически выделяет нужное количество памяти
 *      3) push_back(BitSeq) или append(BitSeq)
 *      4) Конструкторы для заполнения
 *      5) Оператор обращения к конкретному биту
*/

class BitSeq
{
public:
    BitSeq(){}

    BitSeq(int p_size) {
        this->_size = p_size;
        this->_allocated = p_size/8 + 1;
        this->_start = new char[_allocated];
        for(int i = 0; i < _allocated; i++)
            _start[i] = 0;
    }

    BitSeq(uint64_t data, int p_size) : BitSeq(p_size) {
        BitPtr point(_start, 0);
        for(int i = 0; i < p_size; i++){
            point.w(data & (1ul << i));
        }
    }

    BitSeq(BitPtr p_ptrdata, int p_size) : BitSeq(p_size) {
        BitPtr point(_start, 0);
        for(int i = 0; i < p_size; i++){
            point.w(p_ptrdata.r());
            point++;
            p_ptrdata++;
        }
    }

    BitSeq(BitSeq &other) : BitSeq(other.begin(), other.size()) {}  //копирование памяти

    ~BitSeq(){
        if(_allocated > 0) delete[] _start;
    }
private:
   cell _start;
    int _size = 0;
    int _allocated = 0;
public:
    int size()        { return _size; }
    int allocated()   { return _allocated; }
    BitPtr begin()    { return BitPtr(_start, 0); }
    BitPtr end()      { return BitPtr(_start, 0) + _size - 1; }

    void alloc_more(int bytes);  //выделяет дополнительную память
    void alloc_less(int bytes);  //уменьшает количество выделенной памяти // Целесообразность?

    void append(BitSeq &other);
    BitSeq sub_BitSeq(int pos, int len);
public:
    BitPtr operator [] (int pos);

};

std::ostream & operator << (std::ostream & stream, BitSeq seq);

// Выделятся 1024 байт памяти. В случае переполнения выделяется в два раза больше. Другого решения пока не придумал
class BitStr
{
public:
    BitStr(){}
    ~BitStr(){
        delete &field; // --- почему по адресу?
    }
public:
    BitSeq field;
    BitPtr point;
public:
    void write(BitSeq bseq);
    void read_to(BitSeq & seq, int up_lim);
//    BitSeq read (int up_lim);
//    BitSeq read_all();
};

#endif // T_BIT_TYPES_H
