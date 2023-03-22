#ifndef LINDEX_INSTANCE_H
#define LINDEX_INSTANCE_H

#include "lindex_basic_bit_types.h"
#include "t_lindex_type.h"

#include <string>

class lindex_instance
{
public:
    lindex_instance();
    lindex_instance(std::string name, lindex_type * type_ptr, BitSeq data = BitSeq()){
        this->name= name;
        this->type_ptr = type_ptr;
        this->data = data;
    }

    bool parse(BitStr & stream){
        return this->type_ptr->parse(stream, this->data);
    }

    BitSeq action(BitSeq & seq){
        return this->type_ptr->action(seq, this->data);
    }
public:
    lindex_type * type_ptr;
    BitSeq data;
    std::string name;
};

#endif // LINDEX_INSTANCE_H
