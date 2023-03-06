#include "lindex_uint2_t.h"


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

lindex_uint2_t making_uint2_type;
lindex_uint2_t making_uint2_type2;


