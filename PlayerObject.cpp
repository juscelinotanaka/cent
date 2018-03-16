//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "PlayerObject.h"

void PlayerObject::Update() {
    this->position = Input::mousePosition;

    if (Input::GetMouseDown()) {
    }
}

PlayerObject::PlayerObject(const char *string) {
    this->tickUpdate = true;
    this->name = string;
}
