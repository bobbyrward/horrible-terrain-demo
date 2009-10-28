#include "stdafx.h"
#include "logging.h"
#include <cstdio>
#include <cstdarg>

using d3ddfw::Logging;

#pragma warning(disable:4996) // SOOOO annoying...

#undef FAILED

void Logging::outputMessage(char *format, ... ) {
    va_list argp;
    va_start(argp, format);
    char buffer[1024];
    vsnprintf(buffer, 1024, format, argp);
    va_end(argp);
    OutputDebugStringA(buffer);
}

bool _FAILED(HRESULT hr, const char *filename, int lineno) {
    if(hr >= 0) {
        return false;
    }

    Logging::outputMessage("%s(%d): %s - %s\n", filename, lineno, 
        DXGetErrorString9A(hr),
        DXGetErrorDescription9A(hr));

    return true;
}
