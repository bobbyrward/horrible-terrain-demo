#include "stdafx.h"
#include "timer.h"

using d3ddfw::Timer;

/*
class Timer 
{
public:
    Timer();

    float elapsedTime();
    float appTime();
    void start();
    void stop();

private:
    bool        usingQPF_;
    LONGLONG    qpfTicksPerSec_;
    bool        stopped_;
};
*/

Timer::Timer()
    : usingQPF_(false)
    , qpfTicksPerSec_(0)
    , stopped_(false)
    , lastElapsedTime_(0)
    , stopTime_(0)
{
    LARGE_INTEGER ticksPerSec;
    usingQPF_ = QueryPerformanceFrequency(&ticksPerSec) == TRUE;

    if(usingQPF_) {
        qpfTicksPerSec_ = ticksPerSec.QuadPart; 
        QueryPerformanceCounter(&ticksPerSec);
        baseTime_ = ticksPerSec.QuadPart;
    }
}

float Timer::elapsedTime() {
    if(usingQPF_) {
        LARGE_INTEGER time;

        if(stopped_) {
            time.QuadPart = stopTime_;
        } else {
            QueryPerformanceCounter(&time);
        }

        float elapsed = (float)((time.QuadPart - lastElapsedTime_) / (double)qpfTicksPerSec_);
        
        lastElapsedTime_ = time.QuadPart;

        return elapsed;
    } else {
        return 0.f;
    }
}

float Timer::appTime() {
    if(usingQPF_) {
        LARGE_INTEGER time;

        QueryPerformanceCounter(&time);
        
        return (float)((time.QuadPart - baseTime_) / (double)qpfTicksPerSec_);
    } else {
        return 0.f;
    }
}

float Timer::absoluteTime() {
    if(usingQPF_) {
        LARGE_INTEGER time;

        QueryPerformanceCounter(&time);
        
        return (float)(time.QuadPart / (double)qpfTicksPerSec_);
    } else {
        return 0.f;
    }
}

void Timer::start() {
}

void Timer::stop() {
}


