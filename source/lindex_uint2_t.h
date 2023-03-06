#ifndef LINDEX_UINT2_T_H
#define LINDEX_UINT2_T_H

#include "lindex_basic_data_types.h"
#include "lindex_vtable.h"

bool lindex_uint2_parse(BitStr & stream, BitSeq & data_ptr);
BitSeq lindex_uint2_action(BitSeq & seq, BitSeq & data_ptr);

#define LINDEX_UINT2 0x1000
class lindex_uint2_t : public _lindex_basic_type
{
public:
    lindex_uint2_t() : _lindex_basic_type()
    {
        this->_type_id = LINDEX_UINT2;
        this->bit_size = 2;
        this->name = "uint2_t";
        this->parse = lindex_uint2_parse;
        this->action = lindex_uint2_action;
        if (!type_vtable.add(LINDEX_UINT2, this))
            this->~lindex_uint2_t();
    }
};


#endif // LINDEX_UINT2_T_H
