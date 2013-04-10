//
//  Timer.h
//  Roguelike
//
//  Created by Travis McMahon on 3/22/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#ifndef Timer_h
#define Timer_h

class Timer {
private:
    //The clock time when the timer started
    double startTicks;
    
    //The ticks stored when the timer was paused
    double pausedTicks;
    
    //The timer status
    bool paused;
    bool started;
    
public:
    //Initializes variables
    Timer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    double getTicks();
    double getTicksInMS();
    
    //Checks the status of the timer
    bool isStarted();
    bool isPaused();
};

#endif
