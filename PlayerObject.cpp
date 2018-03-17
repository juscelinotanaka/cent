//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "PlayerObject.h"

Vector2 lastMousePos;

void PlayerObject::Update() {

    Vector2 deltaMouse = Input::mousePosition - lastMousePos;
    deltaMouse *= Time::deltaTime;

    auto x = Math::Clamp(this->position.x + deltaMouse.x, 0, CoreEngine::getScreenSize().x - this->getRealSize().x);
    auto y = Math::Clamp(this->position.y + deltaMouse.y,
                         CoreEngine::getScreenSize().y - 16 * 4,
                         CoreEngine::getScreenSize().y - this->getRealSize().y);

    this->position = Vector2(x, y);

    if (Input::GetMouseDown()) {
        Vector2 bulletOffset = Vector2(6, -8);
        bullet.Fire(position + bulletOffset);
    }

    lastMousePos = Input::mousePosition;
}

PlayerObject::PlayerObject(const char *string) {
    this->tickUpdate = true;
    this->name = string;
    SetImage("data/Player.bmp");
    CoreEngine::AddSceneObject(&bullet);
}

