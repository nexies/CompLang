#ifndef LINDEX_BASIC_DATA_TYPES_CPP
#define LINDEX_BASIC_DATA_TYPES_CPP

#include "lindex_basic_bit_types.h"
#include "lindex_vtable.h"
#include <string>

class _lindex_basic_type{
public:
    _lindex_basic_type(){}

    _lindex_basic_type(uint32_t type_id, std::string name){
        this->_type_id = type_id;
        this->name = name;
    };

public:
    uint32_t _type_id;
    std::string name;
    uint16_t bit_size;

public: //methods
    ///     parse и action - указатели на функции. Сами функции описыываются отдельно от описания типа.
    ///     План - один файл на один тип. В нем описывается функция parse и функция action. Для типов данных функция
    /// action просто возвращает значение.

    bool (*parse)(BitStr & stream, BitSeq & data_ptr);
    BitSeq (*action)(BitSeq & seq, BitSeq & data_ptr);
    uint32_t type_id();
    BitSeq data();
    bool id_check(BitStr & stream, int len = 2);
};


#define LINDEX_NONE 0x0FFF
class lindex_None_t : public _lindex_basic_type
{
public:
    lindex_None_t() : _lindex_basic_type(){
        this->bit_size = 0;
        this->name = "None";
        this->_type_id = LINDEX_NONE;
        this->action = 0;
        this->parse = 0;
        if(!type_vtable.add(LINDEX_NONE, this))
            this->~lindex_None_t();
    }
};

bool new_type(uint32_t type_id, std::string name, bool parse(BitStr &, BitSeq &),
              BitSeq action(BitSeq &, BitSeq &));

#endif
