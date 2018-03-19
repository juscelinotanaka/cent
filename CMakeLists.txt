cmake_minimum_required(VERSION 3.9)
project(Cent)

set(CMAKE_CXX_STANDARD 11)
include_directories(SDL2)
link_directories(lib)

file(GLOB LIBRARIES "./lib/*.dylib")
message("LIBRARIES = ${LIBRARIES}")

add_executable(Cent main.cpp CoreEngine/L.cpp CoreEngine/L.h CoreEngine/Input.cpp CoreEngine/Input.h CoreEngine/Vector2.cpp CoreEngine/Vector2.h CoreEngine/Time.cpp CoreEngine/Time.h CoreEngine/SceneObject.cpp CoreEngine/SceneObject.h CoreEngine/CoreEngine.cpp CoreEngine/CoreEngine.h PlayerObject.cpp PlayerObject.h CoreEngine/Math.cpp CoreEngine/Math.h BulletObject.cpp BulletObject.h MushroomObject.cpp MushroomObject.h GameManager.cpp GameManager.h)
target_link_libraries(Cent ${LIBRARIES})