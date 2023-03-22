#include <iostream>
#include <bitset>
#include <vector>
#include <sstream>

#include "lindex_basic_bit_types.h"
#include "lindex_construct_data_types.h"

#include "t_lindex_type.h"

#include <map>

using namespace std;

//map<BitSeq, _lindex_basic_type *> variables;

//class variables_space: public map<BitSeq, _lindex_basic_type*>
//{
//public:
//    variables_space(): map<BitSeq, _lindex_basic_type*>() {}
//    ~variables_space() {
//        for(auto v: *this)
//            delete v.second;
//    }
//public:
//    bool contains(BitSeq name){
//        return this->find(name) != this->end();
//    }
//};


//enum{
//    type_Cmd_new = 0,
//    type_Cmd_add = 2,
//    type_Cmd_in  = 1,
//    type_Cmd_out = 3
//};


//class Cmd_new : public _lindex_basic_type
//{
//public:
//    Cmd_new(variables_space & p_vars){
//        this->_type_id = type_Cmd_new;
//        this->vars = &p_vars;
//    }
//    variables_space * vars;

//public:
//    bool parse(BitStr & stream){
//        cout << "Cmd_new: ";
//        if (this->id_check(stream, 2)){
//            BitSeq name = stream.read(2);
//            if(!vars->contains(name)){
//                (*vars)[name] = new _lindex_uint2_type();
//                cout << "success" << endl;
//                stream.check_container();
//                return true;
//            }
//            else{
//                cout << "fail. variable exists" << endl;
//                stream.check_container();
//                return false;
//            }
//        }
//        cout << "wrong type_id" << endl;
//        stream.check_container();
//        return false;
//    }
//};

//class Cmd_add : public _lindex_basic_type
//{
//public:
//    Cmd_add(variables_space & p_vars){
//        this->_type_id = type_Cmd_add;
//        this->vars = &p_vars;
//    }
//    variables_space * vars;

//    bool parse(BitStr & stream){
//        cout << "Cmd_add: ";
//        if (this->id_check(stream, 2)){
//            BitSeq first = stream.read(2);
//            BitSeq second = stream.read(2);
//            BitSeq res = stream.read(2);

//            if(!vars->contains(first) || !vars->contains(second) || !vars->contains(res)){
//                cout << "fail. not all the variables are present" << endl;
//                stream.check_container();
//                return false;
//            }
//            cout << "success" << endl;
//            stream.check_container();
//            return uint2_add_uint2(vars->at(first), vars->at(second), vars->at(res));
//        }
//        cout << "wrong type_id" << endl;
//        stream.check_container();
//        return false;
//    }
//};

//class Cmd_in: public _lindex_basic_type
//{
//public:
//    Cmd_in(variables_space & p_vars){
//       this->_type_id = type_Cmd_in;
//       this->vars = &p_vars;
//    }
//    variables_space * vars;

//    bool parse(BitStr & stream){
//        cout << "Cmd_in: ";
//        if(this->id_check(stream, 2)){
//            BitSeq var = stream.read(2);
//            if(!vars->contains(var)){
//                cout << "fail. No variable to write in" << endl;
//                stream.check_container();
//                return false;
//            }
//            int n;
//            cin >> n;
//            *(vars->at(var)) = _lindex_uint2_type(n);
//            cout << "success" << endl;
//            stream.check_container();
//            return true;
//        }
//        cout << "wrong type_id" << endl;
//        stream.check_container();
//        return false;
//    }
//};

//class Cmd_out: public _lindex_basic_type
//{
//public:
//    Cmd_out(variables_space & p_vars){
//        this->_type_id = type_Cmd_out;
//        this->vars = &p_vars;
//    }
//    variables_space * vars;

//    bool parse(BitStr & stream){
//        cout << "Cmd_out: ";
//        if(!this->id_check(stream, 2)){
//            cout << "wrong typ_id" << endl;
//            stream.check_container();
//            return false;
//        }
//        BitSeq var = stream.read(2);
//        if(!vars->contains(var)){
//            cout << "fail. no variable" << endl;
//            stream.check_container();
//            return false;
//        }
//        int n = (int)*(vars->at(var)->data().begin().byte);
//        cout << n << endl;
//        cout << "success" << endl;
//        stream.check_container();
//        return true;
//    }
//};

//class Cmd: public Par
//{
//public:
//    Cmd(variables_space & p_vars){
//        this->vars = & p_vars;
//        this->included_count = 4;
//        this->included = new _lindex_basic_type * [4];
//        this->included[0] = new Cmd_new(p_vars);
//        this->included[1] = new Cmd_add(p_vars);
//        this->included[2] = new Cmd_in(p_vars);
//        this->included[3] = new Cmd_out(p_vars);
//    }
//    variables_space * vars;
//};

//void run(BitSeq bits){
//    BitStr stream;
//    stream.write(bits);
//    variables_space vars;

//    Cmd programm(vars);

//    while(!stream.eof())
//        programm.parse(stream);
//}

///*  type uint2:
// *      type_id = 0x1000
// *      name: string
// *      data: BitSeq;
// *
// *  class instance:
// *      type = _basic_type*
// *      name: string
// *
// *  type Struct Cmd_new:
// *      type_id = 0b0000
// *      action (string name) : return new uint2 named 'name'
// *  type Struct Cmd_add:
// *      type_id = 0b0001
// *      action (string name1, string name2) : return sum of variables name1 and name2
// *  type Struct Cmd_in:
// *      type_id = 0b0010
// *      action (string name) : input a value into the variable named 'name'
// *  type Struct Cmd_out:
// *      type_id = 0b0011
// *      action (string name) : output the variable named 'name'
// *
// *  type Union Cmd:
// *      type_id = 0b0100
// *      Cmd_new
// *      Cmd_add
// *      Cmd_in
// *      Cmd_out
// *
// *      parse(): return one of the fields depending on the type id
// *      action(): current.action
// *
// *  type Struct Programm:
// *      array * uint2
// *      array * Cmd
// *
// *
//*/

BitSeq BitSeq_from_str(string str){
    int len = str.size();
    BitSeq out(len);
    BitPtr p = out.begin();
    for(int i = 0; i < len; i++){
        if(str[i] == '0')
            p.w(0);
        else
            p.w(1);
        p++;
    }
    return out;
}

BitSeq seq = BitSeq_from_str("00010010001110011010010110111111");
BitSeq seq2 = BitSeq_from_str("00010001");

int main()
{
//   run(seq);


   return 0;
}
