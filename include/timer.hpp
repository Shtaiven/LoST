#ifndef TIMER_HPP__
#define TIMER_HPP__

#include "SDL.h"


// Timer class to handle timed events
class Timer {
    public:
        //Initializes variables
        Timer();
        
        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();
        
        //Gets the timer's time
        Uint32 getTicks();
        
        //Checks the status of the timer
        bool isStarted();
        bool isPaused();
    
    private:
        //The clock time when the timer started
        Uint32 m_start_ticks;
        
        //The ticks stored when the timer was paused
        Uint32 m_paused_ticks;
        
        //The timer status
        bool m_paused;
        bool m_started;
};

#endif // TIMER_HPP__
