//
// Created by Juscelino Tanaka on 16/03/18.
//

#include <sstream>
#include "GameManager.h"
#include "Player.h"

Mushroom * GameManager::mushroomTemplate;
int GameManager::mushroomsDestroyed = 0;
std::vector<Mushroom *> GameManager::mushrooms;
std::vector<Mushroom *> GameManager::mushroomPool;

Ghost * GameManager::ghostTemplate;
int GameManager::ghostsDestroyed;
std::vector<Ghost *> GameManager::ghosts;

bool GameManager::gameStarted = false;
Player * GameManager::player;

void GameManager::PrepareGame() {

    // create player object and add it to the scene
    player = new Player("Main Char");
    player->scale = Vector2::one * 2;
    CoreEngine::AddSceneObject(player);

    SceneObject * l = new SceneObject("Left Wall");
    l->setImage("data/Laser.bmp");
    l->tag = "Wall";
    l->scale = Vector2(32, 60);
    l->position = Vector2(-32, 0);
    CoreEngine::AddSceneObject(l);

    l = new SceneObject("Right Wall");
    l->setImage("data/Laser.bmp");
    l->tag = "Wall";
    l->scale = Vector2(32, 60);
    l->position = Vector2(CoreEngine::getScreenSize().x, 0);
    CoreEngine::AddSceneObject(l);

    // prepare one mushroom to share texture with all others
    mushroomTemplate = new Mushroom("Mushroom Template");
    mushroomTemplate->setImage("data/Mushroom1.bmp");
    mushroomTemplate->setImage("data/Mushroom2.bmp", true);
    mushroomTemplate->setImage("data/Mushroom3.bmp", true);
    mushroomTemplate->setImage("data/Mushroom4.bmp", true);

    // prepare one ghost to share textures
    ghostTemplate = new Ghost("Ghost Template");
    ghostTemplate->setImage("data/Body.bmp");
    ghostTemplate->setImage("data/Head.bmp", true);
}

void GameManager::StartGame() {

    srand(time(NULL));

    gameStarted = true;

    // skip first line to avoid conflicts with ghost spawn
    // skip the last two lines, because player will not be able to kill the mushroom on the 30th line
    // and it can be tricky to pass under the mushroom on the 29th line
    for (int i = 1; i < 28; ++i) {
        Mushroom * m = CreateNewMushroom();

        mushrooms.push_back(m);

        int column = rand() % 30;
        m->position = Vector2(column, i) * 16;

        CoreEngine::AddSceneObject(m);
    }
//    MushroomDestroyed(mushrooms[0]);
//    mushrooms[0]->position = Vector2(29, 2) * 16;

    // since we wont create new ghost beyond these, we dont need a CreateGhost method
    for (int i = 16; i < 16 + 12; ++i) {

        Ghost * g = new Ghost("Ghosturus");

        // avoid reallocating new textures to save memory
        g->tag = "Ghost";
        g->imageSize = ghostTemplate->imageSize;
        g->setSharedTexture(ghostTemplate->getSharedTexture());
        g->setImageFromPool(0);
        g->scale = Vector2::one * 2;
        g->position = Vector2(i, 0) * 16;

        ghosts.push_back(g);

        CoreEngine::AddSceneObject(g);
    }

    ghosts[0]->name = "Head";
    ghosts[0]->setImageFromPool(1);

    ghosts[1]->name = "Ghost_1";
    ghosts[2]->name = "Ghost_2";
    ghosts[3]->name = "Ghost_3";
    ghosts[4]->name = "Ghost_4";
    ghosts[5]->name = "Ghost_5";
    ghosts[6]->name = "Ghost_6";
    ghosts[7]->name = "Ghost_7";
    ghosts[8]->name = "Ghost_8";
    ghosts[9]->name = "Ghost_9";
    ghosts[10]->name = "Ghost_10";
    ghosts[11]->name = "Ghost_11";
}

void GameManager::MushroomDestroyed(Mushroom *m) {
    m->enable = false;
    mushrooms.erase(std::remove(mushrooms.begin(), mushrooms.end(), m), mushrooms.end());
    mushroomPool.push_back(m);
    mushroomsDestroyed++;
}

Mushroom * GameManager::CreateNewMushroom() {
    Mushroom * m = new Mushroom("Mushrumor");

    // avoid reallocating new textures to save memory
    m->setSharedTexture(mushroomTemplate->getSharedTexture());
    m->tag = "Mushroom";
    m->setImageFromPool(0);
    m->imageSize = mushroomTemplate->imageSize;
    m->scale = Vector2::one * 2;

    return m;
}

Ghost * GameManager::GetPreviousGhost(Ghost *me) {
    for (int i = 0; i < ghosts.size(); ++i) {
        if (ghosts[i] == me) {
            return i == 0 || !ghosts[i]->enable ? nullptr : ghosts[i - 1];
        }
    }

    return nullptr;
}

bool GameManager::isGameStarted() {
    return gameStarted;
}

void GameManager::GhostShot(Ghost *ghost) {
    player->bullet.StopFire();

    for (int i = 0; i < ghosts.size(); ++i) {
        auto found = ghosts[i];
        if (found == ghost) {
            found->enable = false;
            if (i < ghosts.size() - 1 && ghosts[i + 1]->enable) {
                ghosts[i + 1]->setImageFromPool(1);
            }
            break;
        }
    }

    auto newMushroom = GetMushroomFromPool();
    newMushroom->position = ghost->position;

    CheckWinningCondition();
}

Mushroom * GameManager::GetMushroomFromPool() {
    Mushroom * m;
    if (mushroomPool.size() > 0) {
        m = mushroomPool[mushroomPool.size() - 1];
        m->resetMushroom();
        mushroomPool.pop_back();
        L::d("Mushroom from pool: %s - on pool: %d", m->tag, mushroomPool.size());

    } else {
        m = CreateNewMushroom();
        L::d("new Mushroom created: %s", m->tag);
        CoreEngine::AddSceneObject(m);
    }
    return m;
}

void GameManager::CheckWinningCondition() {
    bool anyEnable = false;
    for (int i = 0; i < ghosts.size(); ++i) {
        if (ghosts[i]->enable) {
            anyEnable = true;
            break;
        }
    }

    if (!anyEnable) {
        RespawnGhost();
    }
}

void GameManager::RespawnGhost() {
    for (int i = 0; i < mushrooms.size(); ++i) {
        auto m = mushrooms[i];
        if (0 == (int)round(m->position.y)) {
            m->enable = false;
        }
    }
    for (int i = 0; i < 12; ++i) {
        ghosts[i]->resetGhost();
        ghosts[i]->position = Vector2((16+i), 0) * 16;
    }

    ghosts[0]->setImageFromPool(1);
}
