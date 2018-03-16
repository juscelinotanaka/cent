//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "Time.h"
#include <SDL.h>

Uint64 NOW = SDL_GetPerformanceCounter();
Uint64 LAST = 0;
Uint64 FREQ = 0;

double Time::deltaTime = 0;
double Time::fps = 0;

void Time::UpdateTimer() {
    LAST = NOW;
    NOW = SDL_GetPerformanceCounter();
    FREQ = SDL_GetPerformanceFrequency();

    deltaTime = ((double)(NOW - LAST) / FREQ);
    fps = 1 / deltaTime;
}