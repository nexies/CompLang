#ifndef LINDEX_CONSTRUCT_DATA_TYPES_H
#define LINDEX_CONSTRUCT_DATA_TYPES_H

#include "lindex_basic_data_types.h"

class Seq: public _lindex_basic_type
{
public:
    Seq() {}
    Seq(int p_included_count){
        this->included_count = p_included_count;
        this->included = new _lindex_basic_type* [p_included_count];
    }
protected:
    _lindex_basic_type ** included;
    int included_count;
public:
    bool parse(BitStr & stream);
};


class Par: public _lindex_basic_type
{
public:
    Par() {}
    ~Par() {
        for(int i = 0; i < included_count; i++)
            delete included[i];
        delete[] included;
    }
protected:
    _lindex_basic_type ** included;
    int included_count;
    _lindex_basic_type * current_type;
public:
    bool parse(BitStr & stream){
        for(int i = 0; i < included_count; i++){
            if(included[i]->parse(stream)){
                this->current_type = included[i];
                return true;
            }
        }
        return false;
    }
};

#endif // LINDEX_CONSTRUCT_DATA_TYPES_H
