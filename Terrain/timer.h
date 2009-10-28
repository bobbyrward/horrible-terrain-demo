#pragma once


namespace d3ddfw {

    class Timer 
    {
    public:
        Timer();

        float elapsedTime();
        float appTime();
        float absoluteTime();
        void start();
        void stop();

    private:
        bool        usingQPF_;
        LONGLONG    qpfTicksPerSec_;
        bool        stopped_;
        LONGLONG    lastElapsedTime_;
        LONGLONG    stopTime_;
        LONGLONG    baseTime_;
    };

}

