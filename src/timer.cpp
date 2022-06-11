#include "./util.cpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <time.h>

class Timer {
    public:
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

        bool needsStart;

        int last;

        std::chrono::system_clock::time_point startTime;

        /**
         * An internal function for running the timer.
         */
        void run() {
            while (true) {
                if (stopped == false) {
                    if (current == total) {
                        shutdown();
                        exit(0);
                    }

                    if (needsStart) {
                        startTime = std::chrono::system_clock::now();
                        needsStart = false;
                    } else {
                        std::chrono::system_clock::time_point point =
                            std::chrono::system_clock::now();
                        std::chrono::duration<double> elapsed = point - startTime;
                        current = elapsed.count() * 1000;
                        remaining = total - current;

                        if ((current % 1000) == 0 && last != current) {
                            printf(
                                "------------------\nCurrent time: %is\nRemaining: "
                                "%is\nTotal time: %is\n------------------\n",
                                (current / 1000), (remaining / 1000),
                                (total / 1000));
                            last = current;
                        }
                    }
                }
            }
        }

        /**
         * Creates a new timer with the default settings.
         */
        Timer() {
            current = 0;
            total = 3600000;
            remaining = total;
            stopped = true;
            needsStart = true;
        }

        /**
         * Creates a new timer with the default settings
         * and a specified total time.
         *
         * @param totalTime The total time for the timer in milliseconds.
         */
        Timer(int totalTime) {
            current = 0;
            total = totalTime;
            remaining = total;
            stopped = true;
            needsStart = true;
        }

        /**
         * Get the current time.
         * Formats: 0 = milliseconds, 1 = seconds, 2 = minutes, 3 = hours
         *
         * @param format The format in which to return the current time. Default: 0
         * @return The current time in the specified format.
         */
        int getCurrentTime(int format = 0) {
            if (format == 1) {
                return current / 1000;
            } else if (format == 2) {
                return (current / 1000) / 60;
            } else if (format == 3) {
                return ((current / 1000) / 60) / 60;
            } else {
                return current;
            }
        }

        /**
         * Starts the timer.
         */
        void start() {
            stopped = false;

            run();
        }

        void setCurrent(int cur) { current = cur; }

        void setStartTime(std::chrono::system_clock::time_point p) {
            startTime = p;
        }
};
