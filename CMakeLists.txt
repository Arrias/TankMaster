cmake_minimum_required(VERSION 3.17)
project(TankMaster)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(TankMaster main/TankMaster.cpp
        engine/Game/Game.h engine/Game/Game.cpp
        engine/entities/Tank/Tank.h engine/entities/Tank/Tank.cpp
        engine/entities/MovableBlock/MovableBlock.h engine/entities/MovableBlock/MovableBlock.cpp
        gui/GameDrawer/GameDrawer.h gui/GameDrawer/GameDrawer.cpp
        gui/TextureLoader/TextureLoader.h gui/TextureLoader/TextureLoader.cpp
        gui/constants.h
        engine/entities/Block/Block.cpp engine/entities/Block/Block.h
        engine/entities/Bullet/Bullet.cpp engine/entities/Bullet/Bullet.h
        util/geometry/Vector/Vector.cpp util/geometry/Vector/Vector.h
        util/geometry/general_functions/general_functions.cpp  util/geometry/general_functions/general_functions.h
        util/geometry/Segment/Segment.cpp util/geometry/Segment/Segment.h
        util/geometry/Line/Line.cpp util/geometry/Line/Line.h
        )

target_link_libraries(TankMaster sfml-graphics sfml-audio)