#ifndef T_LINDEX_TYPE_TABLE_H
#define T_LINDEX_TYPE_TABLE_H

#include "lindex_basic_bit_types.h"
#include <map>

class lindex_type;
class lindex_instance;

class lindex_type_table
{
public:
    lindex_type_table() {}

public:
    std::map<uint32_t, lindex_type *> table;
public:
    lindex_instance parse(BitStr & stream);
    bool register_type(lindex_type * new_type);
};

#endif // T_LINDEX_TYPE_TABLE_H
