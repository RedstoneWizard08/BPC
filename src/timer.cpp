#include <stdio.h>

class Timer {
    private:
        /**
         * The passed time in milliseconds. (default: 0)
         */
        int current;

        /**
         * The remaining time in milliseconds. (default: total time)
         */
        int remaining;

        /**
         * The total time in milliseconds. (default: 3600000 = 1 hour)
         */
        int total;

        /**
         * Whether or not the timer is stopped. (default: true)
         */
        bool stopped;

    public:
        /**
         * Creates a new timer with the default settings.
         */
        Timer() {
            current = 0;
            total = 3600000;
            remaining = total;
            stopped = true;
        }

        /**
         * Creates a new timer with the default settings
         * and a specified total time.
         */
        Timer(int totalTime) {
            current = 0;
            total = totalTime;
            remaining = total;
            stopped = true;
        }

        /**
         * Get the current time.
         * Formats: 0 = milliseconds, 1 = seconds, 2 = minutes, 3 = hours
         * 
         * @param format The format in which to return the current time. Default: 0
         * @return The current time in the specified format.
         */
        int getCurrentTime(int format = 0) {
            if(format == 1) {
                return current / 1000;
            } else if(format == 2) {
                return (current / 1000) / 60;
            } else if(format == 3) {
                return ((current / 1000) / 60) / 60;
            } else {
                return current;
            }
        }
};
