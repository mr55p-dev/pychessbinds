//
//  test.hpp
//  PyChessBinds
//
//  Created by Ellis Lunnon on 04/12/2021.
//

#ifndef test_hpp
#define test_hpp

#include <iostream>

#define C_WHITE 1
#define C_BLACK 0

enum MoveType
{
    MT_passive,
    MT_capture,
    MT_attack,
    MT_defend,
    MT_pin
};

enum Allowedtype
{
    AT_empty,
    AT_blocked,
    AT_checking_attack,
    AT_capture,
    AT_disallowed
};

#endif /* test_hpp */
