
# Cent
Cent is an implementation of the game Centipede using Lib SDL. 
The game starts when the player clicks on the mouse.

# Project Parts
This project is divided into two parts - the `CoreEngine` and the gameplay itself (`GameManager` class). This division make the code on the main part be really clear and make each object behave independently from anything else - just by its own.

    while (!CoreEngine::QuitApplication()) {
        CoreEngine::UpdateEvents();
        CoreEngine::UpdateActions();
        CoreEngine::UpdateCollisions();
        CoreEngine::UpdateRendering();

		// not necessary - just to make life easier
        if (!GameManager::isGameStarted() && Input::GetMouseUp()) {
            GameManager::StartGame();
        }
    }

## Core Engine
Core Engine is a simple implementation of an game engine that I made from scratch. I took all my background on game development and created some important classes for making a game (i.e. `Time`, `Input`, `Vector2`, `Math` and a generical `SceneObject`). These classes are helpers to access some informations and process some datas more easily. `SceneObject` is one of the most important classes of the `CoreEngine` and require extra explanations.
### Scene Object
`SceneObject` is the main class for the core engine. It makes a generical abstraction for objects that can show up on screen. It means it handles all the visual parts and is also ready to handle events. It implements some methods that can be overriden to proccess informations on the core engine (i.e. `DetectCollision` and `Update/Tick`). It also has some important attributes like `name`, `tag`, `updateTick`,  `imageSize`, `scale`, `imageRealSize`,  `position` and some others.
If a `SceneObject` is added to the CoreEngine all informations of that object will be updated every frame. It means, all the gameplay object inherits from this class.
Just a reminder, it is also important to know that it implements two virtual methods that can be overriden by inherited classes to handle actions/updates and collision every frame.

## GameManager
It is the core of the game from memory management to gameplay itself – it handle game objects instantiation (spawn object on scene, create texture pools to save memory, create mushroom pools, etc) and it also handle the gameplay itself (bullet collision, mushroom destruction, ghost events, etc).
It is good to know that a lot of images are similar in this project and each object should not has its own instance of the image, for this reason it was implemented a shared texture pool.
The same happens for Mushroom creation/destruction. Since it can be a heavier process, because it involves surfaces and textures, as well as reading a file from disk, mushrooms have a list of mushrooms on scene and a pool of mushrooms that holds those mushrooms that were already destroyed. In case the game requests a new mushroom it will first check if there is any available on the pool before spending time on creating a new from disk.

## Other Classes
All the other classes are implementations of the SceneObject class with its own behaviour encapsulated. Each object should act by itself independently from the others. The gameplay classes are:
 - `Player`
 - `Bullet`
 - `Mushroom`
 - `Ghost`

# Time Spent
Times will be detailed by parts:
 - Lib SDL Studying and Code Examples Reading - 3-4 hours
 - Core Engine development - 5-6 hours
 - Gameplay development - 9-10 hours
 - Refactoring and Improvements - 2-3 hours
 - Necessary time to finish ghost refactoring 2-4
	 - Current ghost is not smooth and the "Atari-like" version was overriden on commit 711d1fb.
