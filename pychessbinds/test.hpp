//
//  test.hpp
//  PyChessBinds
//
//  Created by Ellis Lunnon on 04/12/2021.
//
#pragma once

#include <iostream>

#define C_WHITE 1
#define C_BLACK 0

enum Allowedtype
{
    AT_empty,
    AT_blocked,
    AT_checking_attack,
    AT_capture,
    AT_disallowed,
    AT_attacks
};
