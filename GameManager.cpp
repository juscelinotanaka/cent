//
// Created by Juscelino Tanaka on 16/03/18.
//

#include <sstream>
#include "GameManager.h"
#include <time.h>

Mushroom * GameManager::mushroomTemplate;
int GameManager::mushroomsDestroyed = 0;
std::vector<Mushroom *> GameManager::mushrooms;
std::vector<Mushroom *> GameManager::mushroomPool;

Ghost * GameManager::ghostTemplate;
int GameManager::partsDestroyed = 0;
std::vector<Ghost *> GameManager::ghosts;

int GameManager::deaths = 0;
int GameManager::ghostKills = 0;

bool GameManager::gameStarted = false;
Player * GameManager::player;

bool GameManager::grid[30][30];
Logo * GameManager::logo;

int totalMush = 0;

void GameManager::PrepareGame() {

    logo = new Logo("Logo");
    CoreEngine::AddSceneObject(logo);

    // create player object and add it to the scene
    player = new Player("Main Char");
    player->position = Vector2((int) 15.5 * 16, 27 * 16);
    player->scale = Vector2::one * 2;
    CoreEngine::AddSceneObject(player);

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
    logo->FadeOut(SpawnGame);
}

void GameManager::SpawnGame() {
    srand(time(NULL));

    gameStarted = true;

    // since we wont create new ghost beyond these, we dont need a CreateGhost method
    int totalGhosts = 12;
    for (int i = 0; i < totalGhosts; ++i) {
        auto *g = new Ghost("Ghostus");

        // avoid reallocating new textures to save memory
        g->tag = "Ghost";
        g->imageSize = ghostTemplate->imageSize;
        g->setSharedTexture(ghostTemplate->getSharedTexture());
        g->setImageFromPool(0);
        g->scale = Vector2::one * 2;

        auto pos = Vector2(16 + i, 0);
        g->setStartPos(pos.x, pos.y);

        ghosts.push_back(g);

        CoreEngine::AddSceneObject(g);
    }

    // skip first line to avoid conflicts with ghost spawn
    // skip the last two lines, because player will not be able to kill the mushroom on the 30th line
    // and it can be tricky to pass under the mushroom on the 29th line
    for (int i = 1; i < 28; ++i) {
        Mushroom *m = CreateNewMushroom();

        mushrooms.push_back(m);

        int column = rand() % 30;
        auto gridPos = Vector2(column, i);

        // debug - force mushrooms at specific spots
//        switch (i) {
//            case 1: gridPos = Vector2(1, 0); break;
//            case 2: gridPos = Vector2(3, 1); break;
//            case 3: gridPos = Vector2(1, 2); break;
//        }

        grid[(int)gridPos.x][(int)gridPos.y] = true;
        m->position = gridPos * 16;
    }



    ResetHead();

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

// remove a mushroom from the scene and add a score point if the skipScore is not true
void GameManager::MushroomDestroyed(Mushroom *m, bool skipScore) {
    m->enable = false;
    grid[(int)m->getGridPosition().x][(int)m->getGridPosition().y] = false;
    mushrooms.erase(std::remove(mushrooms.begin(), mushrooms.end(), m), mushrooms.end());
    mushroomPool.push_back(m);
    if (!skipScore) {
        mushroomsDestroyed++;
    }
}

Mushroom * GameManager::CreateNewMushroom() {
    auto * m = new Mushroom("Mush");

    m->id = ++totalMush;

    // avoid reallocating new textures to save memory
    m->setSharedTexture(mushroomTemplate->getSharedTexture());
    m->tag = "Mushroom";
    m->setImageFromPool(0);
    m->imageSize = mushroomTemplate->imageSize;
    m->scale = Vector2::one * 2;
    CoreEngine::AddSceneObjectAtBegin(m);

    return m;
}

Ghost * GameManager::getPreviousGhost(Ghost *me) {
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

Ghost* GameManager::getHeadFor(Ghost *pGhost) {
    Ghost * lastHead = nullptr;
    bool foundMe = false;
    for (int i = 0; i < ghosts.size(); ++i) {
        if (ghosts[i]->IsHead()) {
            lastHead = ghosts[i];
        }

        if (ghosts[i] == pGhost) {
            return lastHead;
        }
    }

    return nullptr;
}


void GameManager::GhostShot(Ghost *ghost) {
    player->bullet.StopFire();

    auto head = getHeadFor(ghost);

    for (int i = 0; i < ghosts.size(); ++i) {
        auto found = ghosts[i];
        if (found == ghost) {
            found->enable = false;
            if (i < ghosts.size() - 1 && ghosts[i + 1]->enable) {
                ghosts[i + 1]->setAsHead(head);
            }
            break;
        }
    }

    partsDestroyed++;

    auto newMushroom = GetMushroomFromPool();
    auto pos = ghost->getToPos();
    newMushroom->position = pos * 16;
//    L::d("New Mush at: %s", pos.toStr());
    grid[(int)pos.x][(int)pos.y] = true;

    CheckWinningCondition();
}

Mushroom * GameManager::GetMushroomFromPool() {
    Mushroom * m;
    if (mushroomPool.size() > 0) {
        m = mushroomPool[mushroomPool.size() - 1];
        m->resetMushroom();
        mushroomPool.pop_back();
//        L::d("Mushroom from pool: %s - on pool: %d", m->tag, mushroomPool.size());

    } else {
        m = CreateNewMushroom();
//        L::d("new Mushroom created: %s", m->tag);

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
        ghostKills++;
        RespawnGhost();
    }
}

void GameManager::RespawnGhost() {
    for (int i = 0; i < ghosts.size(); ++i) {
        ghosts[i]->resetGhost();
        ghosts[i]->setStartPos((16+i), 0);

    }

    ResetHead();
}

void GameManager::PlayerDies() {
    deaths++;
    RespawnGhost();
}

void GameManager::ResetHead() {
    ghosts[0]->name = "Head";
    ghosts[0]->setImageFromPool(1);
    ghosts[0]->setHead();
}

bool GameManager::hasMushroomAt(Vector2 pos, bool showLog) {
    if (pos.x < 0 || pos.x > 29 || pos.y < 0 || pos.y > 29)
        return false;

    if (showLog)
        L::d("(%d, %d) - %d", (int)pos.x, (int)pos.y, grid[(int)pos.x][(int)pos.y]);

    return grid[(int)pos.x][(int)pos.y];
}

void GameManager::PrintGrid() {
    for (int i = 0; i < 30; ++i) {
        char line[30];
        for (int j = 0; j < 30; ++j) {
            line[j] = grid[j][i] == 1 ? '1' : '0';
        }
        L::d("%s", line);
    }
}

int GameManager::getTotalScore() {
    return std::max(ghostKills * 1000 + partsDestroyed * 100 + mushroomsDestroyed * 50 - deaths * 1000, 0);
}
