#include "lindex_basic_data_types.h"

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
