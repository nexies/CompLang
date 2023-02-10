#ifndef LINDEX_BASIC_DATA_TYPES_CPP
#define LINDEX_BASIC_DATA_TYPES_CPP

#include "lindex_basic_bit_types.h"
#include <string>

enum{
    type_basic = 0x1000,
    type_Uint2 = 0x2000,
};

class _lindex_basic_type{
protected:
    uint32_t _type_id;
    BitSeq _data;
    std::string name;
public:

virtual bool parse(BitStr & stream) = 0;
//virtual BitSeq action() = 0;

    uint32_t type_id() { return this->_type_id; }
    BitSeq data() { return this->_data; }
    bool id_check(BitStr & stream, int len = 2){
        BitSeq t = BitSeq(this->_type_id, len);
        BitSeq c = stream.check(len);
        if (stream.check(len) == BitSeq(this->_type_id, len)){
            stream.skip(len);
            return true;
        }
        return false;
    }
};


class _lindex_uint2_type: public _lindex_basic_type
{
public:
    _lindex_uint2_type() {
        _type_id = type_Uint2;
    }
    _lindex_uint2_type(BitStr & stream);
    _lindex_uint2_type(uint8_t value){
        _type_id = type_Uint2;
        this->_data = BitSeq(value, 2);
    }

    BitSeq action() { return this->data(); }

    bool parse(BitStr & stream){
        this->_data = stream.read(2);
        return true;
    }

    operator int (){
        return (int)(*(_data.begin().byte));
    }
    operator char (){
        return (char)(*(_data.begin().byte));
    }
};

bool uint2_add_uint2(_lindex_basic_type *first, _lindex_basic_type *second, _lindex_basic_type *res);

#endif

