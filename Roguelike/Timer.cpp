//
//  Timer.cpp
//  Roguelike
//
//  Created by Travis McMahon on 3/29/13.
//  Copyright (c) 2013 Travis McMahon. All rights reserved.
//

#include "Timer.h"
#include "GLHeaders.h"

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;
    
    //Unpause the timer
    paused = false;
    
    //Get the current clock time
    startTicks = glfwGetTime();
}

void Timer::stop()
{
    //Stop the timer
    started = false;
    
    //Unpause the timer
    paused = false;
}

double Timer::getTicks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return glfwGetTime() - startTicks;
        }
    }
    
    //If the timer isn't running
    return 0;
}

double Timer::getTicksInMS() {
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return (glfwGetTime() - startTicks)/1000;
        }
    }
    
    //If the timer isn't running
    return 0;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;
        
        //Calculate the paused ticks
        pausedTicks = glfwGetTime() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;
        
        //Reset the starting ticks
        startTicks = glfwGetTime() - pausedTicks;
        
        //Reset the paused ticks
        pausedTicks = 0;
    }
}

bool Timer::isStarted()
{
    return started;
}

bool Timer::isPaused()
{
    return paused;
}