#include <stdio.h>
#include <string>
#include <sstream>
#include <cstdint>
/**
 * This class abstracts multiple timing related mechanism in the game
 */

class LTimer
{
public:
    /**
     * The constructor of the class
    */
    LTimer();

    /**
     * Method to start the timer
    */
    void start();
    /**
     * Method to stop the timer
    */
    void stop();
    /**
     * Method to pause the timer
    */
    void pause();
    /**
     * Method to unpause the timer
    */
    void unpause();

    /**
     * Method to get the current ticks
    */
    uint32_t getTicks();
    /**
     * Method to get the current SDL ticks
    */
    uint32_t getSDLTicks();

    /**
     * Method to check if the timer is started
    */
    bool isStarted();
    /**
     * Method to check if the timer is paused
    */
    bool isPaused();

private:
    /**
     *  The clock time when the timer started
     */
    uint32_t mStartTicks;

    /**
     *  The ticks stored when the timer was paused
     */
    uint32_t mPausedTicks;

    /**
     * The timer status
     */
    bool mPaused;
    /**
     * The timer status
     */
    bool mStarted;

  
};