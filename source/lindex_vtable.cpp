#include "lindex_vtable.h"
#include <map>

using namespace std;

lindex_virtual_table<uint32_t, _lindex_basic_type *> type_vtable;

//bool new_global_type(_lindex_basic_type *instance)
//{
//    uint32_t id = instance->type_id();
//    if(!type_vtable.contains(id)){
//        type_vtable[id] = instance;
//        return true;
//    }
//    cout << "Falied creating new type: already exists" << endl;
//    return false;
//}

//_lindex_basic_type *global_type(uint32_t type_id)
//{
//    if(type_vtable.contains(type_id))
//        return type_vtable[type_id];
//    else{
//        cout << "Global type does not exist" << endl;
//        return new _lindex_uint2_type(); // to change!!!
//    }
//}
