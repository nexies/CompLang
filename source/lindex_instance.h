#ifndef LINDEX_INSTANCE_H
#define LINDEX_INSTANCE_H

#include "lindex_basic_bit_types.h"
#include "lindex_basic_data_types.h"

#include <string>

class lindex_instance
{
public:
    lindex_instance();
    lindex_instance(std::string name, _lindex_basic_type * type_ptr, BitSeq data = BitSeq()){
        this->name= name;
        this->type_ptr = type_ptr;
        this->data = BitSeq(type_ptr->bit_size);
    }
public:
    _lindex_basic_type * type_ptr;
    BitSeq data;
    std::string name;
};

#endif // LINDEX_INSTANCE_H
