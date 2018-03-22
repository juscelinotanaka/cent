//
// Created by Juscelino Tanaka on 15/03/18.
//

#include "L.h"

void L::d(const char* format, ...) {
    char buffer[512];
    va_list args;
    va_start (args, format);
    vsnprintf (buffer, 511, format, args);
    SDL_LogMessage(8, SDL_LOG_PRIORITY_VERBOSE, buffer);
    va_end(args);
}

void L::MessageBox(const char *title, const char *message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, NULL);
}