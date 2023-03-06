#include "lindex_basic_data_types.h"

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

bool new_type(uint32_t type_id, std::string name, bool parse(BitStr &, BitSeq &), BitSeq action(BitSeq &, BitSeq &))
{
    if (type_vtable.contains(type_id)) return false;
    _lindex_basic_type * ptr = new _lindex_basic_type;
    ptr->_type_id = type_id;
    ptr->name = name;
    ptr->parse = parse;
    ptr->action = action;
    type_vtable.add(type_id, ptr);
}
