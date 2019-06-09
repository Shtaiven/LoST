#include "LGE_timer.hpp"


LGE::Timer::Timer() {
    //Initialize the variables
    m_start_ticks = 0;
    m_paused_ticks = 0;
    m_paused = false;
    m_started = false;
}

void LGE::Timer::start() {
    //Start the timer
    m_started = true;
    
    //Unpause the timer
    m_paused = false;
    
    //Get the current clock time
    m_start_ticks = SDL_GetTicks();
    m_paused_ticks = 0;
}

void LGE::Timer::stop() {
    //Stop the timer
    m_started = false;
    
    //Unpause the timer
    m_paused = false;
    
    //Clear tick variables
    m_start_ticks = 0;
    m_paused_ticks = 0;
}

void LGE::Timer::unpause() {
    //If the timer is running and paused
    if(m_started && m_paused) {
        //Unpause the timer
        m_paused = false;
        
        //Reset the starting ticks
        m_start_ticks = SDL_GetTicks() - m_paused_ticks;
        
        //Reset the paused ticks
        m_paused_ticks = 0;
    }
}

Uint32 LGE::Timer::getTicks() {
    //The actual timer time
    Uint32 ticks = 0;
    
    //If the timer is running
    if(m_started) {
        //If the timer is paused
        if(m_paused) {
            //Return the number of ticks when the timer was paused
            ticks = m_paused_ticks;
        } else {
            //Return the current time minus the start time
            ticks = SDL_GetTicks() - m_start_ticks;
        }
    }
    
    return ticks;
}

bool LGE::Timer::isStarted() {
    //Timer is running and paused or unpaused
    return m_started;
}

bool LGE::Timer::isPaused() {
    //Timer is running and paused return
    return m_paused && m_started;
}
