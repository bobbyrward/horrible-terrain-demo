#pragma once

namespace d3ddfw {

    /*
    //TODO: Maybe finish this once I get a copy of boost downloaded
    //      I miss shared_ptr
    
    class LogOutput 
    {
    public:
        virtual void writeString(std::string const& msg) = 0;
    };

    class LogOutput_Debugger 
        : public LogOutput
    {
    public:
        virtual void writeString(std::string const& msg);
    };
    */


    class Logging 
    {
    public:
        static void outputMessage(char *format, ... );
    private:
    };

}

#undef FAILED
bool _FAILED(HRESULT hr, const char *filename, int lineno); 

#define FAILED(hr) (_FAILED(hr, __FILE__, __LINE__))

