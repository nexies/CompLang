#ifndef LINDEX_BASIC_BIT_TYPES_H
#define LINDEX_BASIC_BIT_TYPES_H
#include <iostream>
#include <string>

class BitSeq;

class BitPtr
{
public:
    BitPtr(){}
    BitPtr(char * p_byte, uint8_t p_bit = 0) : byte(p_byte), bit(p_bit){}
public:
    char* byte;
    uint8_t bit;
public:
    int r(); // Read
    void w(int val); // Write

public:
    BitPtr operator+ (int shift);
    BitPtr operator- (int shift);
    void   operator+=(int shift);
    void   operator-=(int shift);
    void   operator++(int emp);
    void   operator--(int emp);
    void   operator++();
    void   operator--();
};


// BitSeq -- Класс-контейнер
/*      1) Всегда начинается с первого бита в байте
 *      2) Автоматически выделяет нужное количество памяти
 *      3) push_back(BitSeq) или append(BitSeq)
 *      4) Конструкторы для заполнения
 *      5) Оператор обращения к конкретному биту
*/

class BitSeq
{
public:
    BitSeq();
//    static int empty;

    explicit BitSeq(int p_size);
//    static int by_size;

    BitSeq(uint64_t p_data, int p_size);
//    static int by_data_size;

    BitSeq(BitPtr p_ptrdata, int p_size);
//    static int by_ptr_size;

    BitSeq(const BitSeq &other);
//    static int by_const_other;

    BitSeq(BitSeq &other);
//    static int by_other;

    ~BitSeq();
//    static int deletions;

//    static void init(){
/*        empty = 0;
        by_size = 0;
        by_data_size = 0;
        by_ptr_size = 0;
        by_const_other = 0;
        by_other = 0;
        deletions = 0;
    }*/
private:
    char* _start = 0;
    int _size = 0;
    int _allocated = 0;
public:
    void copy(const BitSeq & other);
    int bit_size() const;
    int byte_size() const;
    int allocated() const;
    BitPtr begin() const;
    BitPtr end() const;

    void alloc_more(int bytes);  //выделяет дополнительную память
    void alloc_less(int bytes);  //уменьшает количество выделенной памяти // Целесообразность?

    void append(BitSeq const &other);
    BitSeq cut_from_end(int size);
    BitSeq sub_BitSeq(int pos, int len);
public:
    BitPtr  operator [] (int pos);
    BitSeq& operator = (const BitSeq & other);
    bool    operator== (const BitSeq & other) const;
    bool    operator!= (const BitSeq & other) const;
    bool    operator>  (const BitSeq & other) const;
    bool    operator<  (const BitSeq & other) const;
    bool    operator>= (const BitSeq & other) const;
    bool    operator<=  (const BitSeq & other) const;
    BitSeq  operator+  (const BitSeq & other) const;
    BitSeq& operator+= (const BitSeq & other);
//    void   operator =  (BitSeq const & other);

};

std::ostream & operator << (std::ostream & stream, BitSeq seq);

class BitStr
{
public:
    BitStr(){
        _field.alloc_more(1);
        _point_pos = 0;
    }
private:
    BitSeq _field;
    int    _point_pos;
private:
inline int len() { return this->_field.bit_size(); }
public:
    void   reset();
    bool   eof() const { return _point_pos == 0; }
    void   write(const BitSeq & bseq);
    void   write(BitSeq & bseq);

    BitSeq check(int up_lim);
    void   skip(int up_lim);
    BitSeq read(int up_lim);
    BitSeq read_all();

    void   check_container();
    operator bool() const;
};

BitStr & operator << (BitStr & stream, BitSeq & bseq);


#endif // LINDEX_BASIC_BIT_TYPES_H
