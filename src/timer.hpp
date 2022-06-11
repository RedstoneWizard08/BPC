class Timer {
    public:
        /**
         * Creates a new timer with the default settings.
         */
        Timer();

        /**
         * Creates a new timer with the default settings
         * and a specified total time.
         *
         * @param totalTime The total time for the timer in milliseconds.
         */
        Timer(int totalTime);

        /**
         * Get the current time.
         * Formats: 0 = milliseconds, 1 = seconds, 2 = minutes, 3 = hours
         * 
         * @param format The format in which to return the current time. Default: 0
         * @return The current time in the specified format.
         */
        int getCurrentTime(int format = 0);

        /**
         * Starts the timer.
         */
        void start();
};
