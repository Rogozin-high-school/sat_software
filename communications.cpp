#include "communications.hpp"

InMsg::InMsg(list_py lis, int offset = 0): _body(lis),
 _ptr(2 + offset), _type(lis[offset]), _status(lis[offset + 1]){
    
}
