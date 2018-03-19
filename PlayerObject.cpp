//
// Created by Juscelino Tanaka on 16/03/18.
//

#include "PlayerObject.h"

Vector2 lastMousePos;

PlayerObject::PlayerObject(const char *name) {
    this->tickUpdate = true;
    enableCollision = true;

    this->name = name;
    this->tag = "Player";

    SetImage("data/Player.bmp");

    CoreEngine::AddSceneObject(&bullet);
}

void PlayerObject::Update() {

    bool useDelta = true;
    double x, y;
    if (useDelta) {
        Vector2 deltaMouse = Input::mouseDelta;

        // clamp delta to 13 to it dont pass over the sprite which has 14 width
        deltaMouse.x = Math::clamp(deltaMouse.x, -13, +13);
        deltaMouse.y = Math::clamp(deltaMouse.y, -13, +13);

        x = Math::clamp(this->position.x + deltaMouse.x, 0, CoreEngine::getScreenSize().x - this->getRealSize().x);
        y = Math::clamp(this->position.y + deltaMouse.y,
                             CoreEngine::getScreenSize().y - 16 * 4,
                             CoreEngine::getScreenSize().y - this->getRealSize().y);



        lastMousePos = Input::mousePosition;
    } else {
        x = Math::clamp(Input::mousePosition.x, 0, CoreEngine::getScreenSize().x - this->getRealSize().x);
        y = Math::clamp(Input::mousePosition.y,
                             CoreEngine::getScreenSize().y - 16 * 4,
                             CoreEngine::getScreenSize().y - this->getRealSize().y);
    }

    this->position = Vector2(x, y);

    if (Input::GetMousePressed()) {
        Vector2 bulletOffset = Vector2(6, -8);
        bullet.Fire(position + bulletOffset);
    }

}

void PlayerObject::OnCollisionDetected(SceneObject *other) {
    if (!strcmp(other->tag, "Mushroom")) {
        Vector2 overlaping = CoreEngine::overlapAmount(this, other);

        if (abs(overlaping.x) < abs(overlaping.y)) {
            position.x += overlaping.x;
        } else {
            position.y += overlaping.y;
        }
    }
}

