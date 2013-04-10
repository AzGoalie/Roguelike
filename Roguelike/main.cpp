//
//  main.cpp
//  Roguelike
//
//  Created by Travis McMahon on 3/22/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#include <stdio.h>
#include "Game.h"

int main() {
    Game game;
    
    try {
        if (!game.init())
            printf("Error in initializing");
        game.start();
    } catch(TMException &e) {
        printf("error initializing: %s", e.what());
    }
    
    return 0;
}