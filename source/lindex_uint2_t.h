#ifndef LINDEX_UINT2_T_H
#define LINDEX_UINT2_T_H

#include "t_lindex_type.h"
#include "t_lindex_type_table.h"

bool lindex_uint2_parse(BitStr & stream, BitSeq & data_ptr);
BitSeq lindex_uint2_action(BitSeq & seq, BitSeq & data_ptr);


bool lindex_cmd_uint2_add_uint2_parse(BitStr & stream, BitSeq & data_ptr);
BitSeq lindex_cmd_uint2_add_uint2_action(BitSeq & seq, BitSeq & data_prt);

#define LINDEX_CMD_UINT2_ADD_UINT2 0x0001

#endif // LINDEX_UINT2_T_H
