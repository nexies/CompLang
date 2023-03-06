#ifndef LINDEX_VTABLE_H
#define LINDEX_VTABLE_H

#include "lindex_basic_bit_types.h"
#include <map>

class _lindex_basic_type;

template<typename T1, typename T2>
class lindex_virtual_table: public std::map<T1, T2>
{
public:
    ~lindex_virtual_table(){
        for (auto cell: *this){
            delete cell.second;
        }
    }
public:
    bool contains(T1 name){
        return this->find(name) != this->end();
    }

    bool add(T1 name, T2 value){
        if(!contains(name)){
            this->emplace(name, value);
            return true;
        }
        else
            return false;
    }
public:
    T2 & operator[](T1 & name){
        if(this->contains(name))
            return this->at(name);
        else{
            std::cout << "lindex_virtual_table_error: no instance with such key" << std::endl;
            return T2();
        }
    }
};

extern lindex_virtual_table<uint32_t, _lindex_basic_type *> type_vtable;

bool new_global_type(_lindex_basic_type * instance);
_lindex_basic_type * global_type(uint32_t type_id);

#endif // LINDEX_VTABLE_H
