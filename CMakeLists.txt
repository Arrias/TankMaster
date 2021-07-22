cmake_minimum_required(VERSION 3.17)
project(TankMaster)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(TankMaster main/TankMaster.cpp
        engine/Game/Game.h engine/Game/Game.cpp
        engine/entities/Tank/Tank.h engine/entities/Tank/Tank.cpp
        engine/entities/MovableBlock/MovableBlock.h engine/entities/MovableBlock/MovableBlock.cpp
        engine/EntityType/EntityType.h engine/EntityType/EntityType.cpp
        gui/GameView/GameView.h gui/GameView/GameView.cpp
        gui/TextureLoader/TextureLoader.h gui/TextureLoader/TextureLoader.cpp
        gui/constants.h
        util/geometry_functions/geometry_functions.h util/geometry_functions/geometry_functions.cpp
        engine/entities/Block/Block.cpp engine/entities/Block/Block.h
        engine/entities/Bullet/Bullet.cpp engine/entities/Bullet/Bullet.h
        )

target_link_libraries(TankMaster sfml-graphics sfml-audio)