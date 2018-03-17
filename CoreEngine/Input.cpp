//
// Created by Juscelino Tanaka on 15/03/18.
//

#include "Input.h"
#include "L.h"
#include <SDL.h>

enum KeyState {
    Idle,
    Down,
    Pressed,
    Up
};

KeyState mouseState;
bool mouseIsDown = false;
bool escIsDown = false;
bool quit;
KeyState escape;
Vector2 Input::mousePosition = Vector2();


void Input::HandleEvents() {
    SDL_Event event;

    bool mouseChanged = false;
    bool escChanged = false;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEMOTION:
                mousePosition = Vector2(event.motion.x, event.motion.y);
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseChanged = true;
                mouseState = Down;
                mouseIsDown = true;
                break;

            case SDL_MOUSEBUTTONUP:
                mouseChanged = true;
                mouseState = Up;
                mouseIsDown = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        escChanged = escIsDown = true;
                        escape = Down;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        escChanged = true;
                        escIsDown = false;
                        escape = Up;
                }
                break;
        }
    }

    if (!mouseChanged)
        mouseState = mouseIsDown ? Pressed : Idle;

    if (!escChanged)
        escape = escIsDown ? Pressed : Idle;
}

bool Input::Quit() {
    return quit;
}

bool Input::GetMouseDown() {
    return mouseState == Down;
}

bool Input::GetMousePressed() {
    return mouseState == Down || mouseState == Pressed;
}

bool Input::GetMouseUp() {
    return mouseState == Up;
}

bool Input::GetEscape() {
    return escape == Down;
}


