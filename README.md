
# Cent
Cent is an implementation of the game Centipede using Lib SDL. 
The game starts when the player clicks on the mouse.

# Project Parts
This project is divided into two main parts - the `CoreEngine` and the gameplay itself (`GameManager` class). This division makes the code on the main part be really clear and make each object behave independently from anything else - just by its own.

    while (!CoreEngine::QuitApplication()) {
        CoreEngine::UpdateEvents();
        CoreEngine::UpdateActions();
        CoreEngine::UpdateCollisions();
        CoreEngine::UpdateRendering();

        // starts the game by the player's click
        if (!GameManager::isGameStarted() && Input::GetMouseUp()) {
            GameManager::StartGame();
        }
    }

## Core Engine
Core Engine is a simple implementation of an game engine that I made from scratch. I took all my background on game development and created some important classes for making and debuging a game (i.e. `Time`, `Input`, `Vector2`, `Math` and a generical `SceneObject`). These classes are helpers to access some informations and process some datas more easily. `SceneObject` is one of the most important classes of the `CoreEngine` and require extra explanations.

On the `CoreEngine` we have 4 core methods that are the minumum steps to any engine: `UpdateEvents`, `UpdateActions`, `UpdateCollisions` and `UpdateRendering`.

`UpdateCollisions` and `UpdateRendering` are kind of self explained – Update `UpdateCollisions` will check any collision between object and will trigger the overriden method `OnCollisionDetected` and the method will go over all registered object and print them on screen calling their `RenderOnScreen` method – it is important to remember that these methods will only be called if the variable `enable` is true on each object (and `enableCollision` on the case of the collision method).

The difference between the methods `UpdateEvents` and `UpdateActions` is that UpdateEvents reads and process external information (i.e. deltaTime, Input, etc) and then the actions can be processed after we have the right state of the system.

### Scene Object
`SceneObject` is the main class for the core engine. It makes a generical abstraction for objects that can show up on screen. It means it handles all the visual parts and is also ready to handle events. It implements some methods that can be overriden to proccess informations on the core engine (i.e. `DetectCollision` and `Update/Tick`). It also has some important attributes like `name`, `tag`, `updateTick`,  `imageSize`, `scale`, `imageRealSize`,  `position` and some others.

If a `SceneObject` is added to the CoreEngine (using `CoreEngine::AddSceneObject(*)`, for example) all informations of that object will be updated every frame. Since this is the main class of the engine, all the gameplay object inherits from this class.
Just a reminder, it is also important to know that it implements two virtual methods that can be overriden by inherited classes  to handle actions/updates and collision every frame. They are: `Update` and `OnCollisionDetected`.

## GameManager
It is the core of the game from memory management to gameplay itself – it handle game objects instantiation (spawn object on scene, create texture pools to save memory, create mushroom pools, etc) and it also handle the gameplay itself (bullet collision, mushroom destruction, ghost events, etc).

It is good to know that a lot of images are similar in this project and each object should not has its own instance of the image, for this reason it was implemented a shared texture pool.

On the `PrepareGame` method is created a copy/template of a mushroom and a ghost to hold their necessary textures. Each object has its own pool texture that will be shared with the objects when they are created later (on the `SpawnGame` method). It means the new objects will not need to instantiate textures again, they will just get a copy of the texture pool created previously. In this way a lot of memory is saved.

An extra pool is also created specifically for Mushrooms. Since its has a lot of creation/destruction actions that can be a heavier process (because it involves surfaces and textures, as well as reading a file from disk) mushrooms have a list of mushrooms on scene (`mushrooms`) and a pool of mushrooms that holds those mushrooms that were already destroyed (`mushroomPool`). In case the game requests a new mushroom it will first check if there is any available on the pool before spending time on creating a new from disk. Also, all mushrooms are created at the beginning of the vector to make them always be under the ghost when overlapping.

## Ghost Class
This was the trickiest class on the project. This class took almost half of the time of the project, since all the complexities are centered here and the game depends on it to behave correctly. A first implementation was done using a time-dependent model, were each ghost moved independently. It was not good because they lost sync and created some empty space between ghost parts. It was also hard to handle collision events and propagate it to the tail. Sometimes tail got lost and the game got crazy.

To fix this problem, a grid/frame-dependency was implemented. It means each part of the ghost were updated synchronously and the information was shared at the same time for every part of the ghost, but only a head handles what will happen every sync-time.  Each part of the ghosts gets the information from its previous ghost, in this way it knows where to go, and they never lose sync with the head - even a head changes in the middle of the process.


## Other Classes
All the other classes are implementations of the SceneObject class with its own behaviour encapsulated. Each object should act by itself independently from the others. The gameplay classes are:
 - `Player` - implements an updated method to move player on screen and a collision detection method to avoid overlapping mushrooms.
 - `Bullet` - implements an updated method to make the bullet move every frame and some extra events to start/stop firing, as well as detect collision with any mushroom.
 - `Mushroom` - it handles its textures to change whenever it gets a hit, and reset itself whenever the GameManager reuses it.

# Time Spent
Times will be detailed by parts:
 - Lib SDL Studying and Code Examples Reading - 3-4 hours
 - Core Engine development - 5-6 hours
 - Gameplay development - 9-10 hours
 - Refactoring and Improvements - 2-3 hours
 - Ghost refactoring - 8-10 hours
	 - Ghost was firstly implemented like the "Atari" version (moving the whole sprite to the next line), but it was buggy yet. It was overriden on commit 711d1fb.
- Logo, score and others - ~1 hours

### Compiling
This project was developed on MacOS using CLion (cmake-friendly) but a final version was run on Windows using Visual Studio 2017. Both IDEs should be able to open and run the project.

### Copyrights
This project cannot be copied or reused for any purpouse. The images rights are not mine, except the logo image.
