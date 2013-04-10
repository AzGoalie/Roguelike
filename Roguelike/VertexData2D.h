//
//  VertexData2D.h
//  Roguelike
//
//  Created by Travis McMahon on 4/9/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#ifndef VERTEX_DATA_2D
#define VERTEX_DATA_2D

#include "VertexPos2D.h"
#include "TextCoord.h"

struct VertexData2D
{
    VertexPos2D position;
    TexCoord texCoord;
};

#endif