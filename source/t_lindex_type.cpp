#include "t_lindex_type.h"

lindex_None_t making_None_type;

/*
bool uint2_add_uint2(_lindex_basic_type *first, _lindex_basic_type *second, _lindex_basic_type *res)
{
    if(first->type_id() != type_Uint2 ||
        second->type_id() != type_Uint2 ||
        res->type_id() != type_Uint2)
        return false;

    int f = *(first->data().begin().byte);
    int s = *(second->data().begin().byte);
    *res = _lindex_uint2_type((f + s)&0b11);
    return true;
}

uint32_t _lindex_basic_type::type_id() { return this->_type_id; }

BitSeq _lindex_basic_type::data() { return this->_data; }

bool _lindex_basic_type::id_check(BitStr &stream, int len){
    BitSeq t = BitSeq(this->_type_id, len);
    BitSeq c = stream.check(len);
    if (stream.check(len) == BitSeq(this->_type_id, len)){
        stream.skip(len);
        return true;
    }
    return false;
}

BitStr &operator>>(BitStr &stream, _lindex_uint2_type &uint2)
{
}
*/

bool lindex_uint2_parse(BitStr &stream, BitSeq &data_ptr)
{
    if(stream.check(32) == BitSeq(LINDEX_UINT2, 32)){
        data_ptr = stream.read(2);
        return true;
    }
    return false;
}

BitSeq lindex_uint2_action(BitSeq &seq, BitSeq &data_ptr)
{
    return BitSeq(LINDEX_UINT2, 32) + data_ptr;
}
