//
//  TMException.h
//  Roguelike
//
//  Created by Travis McMahon on 3/25/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#ifndef TMException_h
#define TMException_h

#include <iostream>
#include <stdexcept>

class TMException: public std::runtime_error
{
    explicit TMException(const std::string& msg):std::runtime_error(msg){};
};

#endif
