//
// Created by Juscelino Tanaka on 15/03/18.
//

#include "Input.h"
#include "L.h"

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
Vector2 Input::mouseDelta = Vector2();


void Input::HandleEvents() {
    SDL_Event event;

    bool mouseStateChanged = false;
    bool mousePosChanged = false;
    bool escChanged = false;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;

            case SDL_MOUSEMOTION:
                mousePosChanged = true;
                mousePosition = Vector2(event.motion.x, event.motion.y);
                mouseDelta = Vector2(event.motion.xrel, event.motion.yrel);
                break;

            case SDL_MOUSEBUTTONDOWN:
                mouseStateChanged = true;
                mouseState = Down;
                mouseIsDown = true;
                break;

            case SDL_MOUSEBUTTONUP:
                mouseStateChanged = true;
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

    if (!mousePosChanged)
        mouseDelta = Vector2::zero;

    if (!mouseStateChanged)
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


