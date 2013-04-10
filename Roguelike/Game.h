//
//  Game.h
//  Roguelike
//
//  Created by Travis McMahon on 3/22/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "TMConsole.h"
#include "Timer.h"
#include "TMException.h"

const int FRAMES_PER_SECOND = 20;

class Game {
private:
    TMConsole* console;
    Timer timer;
    
    void mainLooop();
    void handleInput();
    void update(int dt);
    void render();
    
    // Test code
    Texture t;
    
public:
    Game();
    ~Game();
    
    bool init() throw(TMException);
    void start();
    
};

#endif
