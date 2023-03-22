#ifndef LINDEX_BASIC_DATA_TYPES_CPP
#define LINDEX_BASIC_DATA_TYPES_CPP

#include "lindex_basic_bit_types.h"
#include "t_lindex_type_table.h"
#include <string>

class lindex_type{
public:
    lindex_type(){}

    lindex_type(uint32_t type_id, std::string name)
    {
        this->type_id = type_id;
        this->name = name;
    }

    lindex_type(uint32_t type_id, std::string name, uint16_t bit_size,
                       bool parse(BitStr&, BitSeq&), BitSeq action(BitSeq&, BitSeq&))
    {
        this->type_id = type_id;
        this->name = name;
        this->bit_size = bit_size;
        this->parse = parse;
        this->action = action;
    }

    ~lindex_type(){}
public: //data
    uint32_t type_id;
    std::string name;
    uint16_t bit_size;

public: //methods
    bool (*parse)(BitStr & stream, BitSeq & data_ptr);
    BitSeq (*action)(BitSeq & seq, BitSeq & data_ptr);
    BitSeq data();
    bool id_check(BitStr & stream, int len = 2);
};

//=====================================================================================


#define LINDEX_UINT2 0x1000
bool lindex_uint2_parse(BitStr &stream, BitSeq &data_ptr);
BitSeq lindex_uint2_action(BitSeq &seq, BitSeq &data_ptr);




#define LINDEX_NONE  0x0FFF
#define LINDEX_UINT2 0x1000
#define LINDEX_CMD_UINT2_ADD_UINT2 0x0001



#endif
