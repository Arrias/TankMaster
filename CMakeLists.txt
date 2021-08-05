cmake_minimum_required(VERSION 3.17)
project(TankMaster)

set(CMAKE_CXX_STANDARD 20)

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
        gui/Button/Button.cpp gui/Button/Button.h gui/MainMenu/MainMenu.cpp gui/MainMenu/MainMenu.h gui/Window/Window.cpp gui/Window/Window.h gui/SingleGame/SingleGame.cpp gui/SingleGame/SingleGame.h)

target_link_libraries(TankMaster sfml-graphics sfml-audio)

find_package( Threads )
add_executable(Registry registry/main.cpp mongoose/mongoose.cpp mongoose/mongoose.h web/User/User.cpp web/User/User.h)
target_link_libraries( Registry ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries(Registry sfml-graphics sfml-audio)

add_executable(TestWs registry/test_ws.cpp mongoose/mongoose.cpp mongoose/mongoose.h)