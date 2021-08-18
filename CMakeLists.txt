cmake_minimum_required(VERSION 3.17)
project(TankMasterClient)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(TankMasterClient main/TankMasterClient.cpp
        engine/Game/Game.cpp
        engine/entities/Tank/Tank.cpp
        engine/entities/MovableBlock/MovableBlock.cpp
        gui/GameDrawer/GameDrawer.cpp
        engine/entities/Block/Block.cpp
        engine/entities/Bullet/Bullet.cpp
        util/geometry/Vector/Vector.cpp
        util/geometry/general_functions/general_functions.cpp
        util/geometry/Segment/Segment.cpp
        util/geometry/Line/Line.cpp
        gui/Registry/Registry.cpp
        registry/API/RegistryApi.cpp
        gui/Button/Button.cpp
        gui/MainMenu/MainMenu.cpp
        gui/Window/Window.cpp
        gui/SingleGame/SingleGame.cpp
        gui/TcpMultiplayerGame/TcpMultiplayerGame.cpp
        registry/TcpGameHost/TcpGameHost.cpp)

target_link_libraries(TankMasterClient sfml-graphics sfml-audio sfml-network)

find_package(Threads)
add_executable(registry_server registry/server.cpp
        mongoose/mongoose.cpp
        engine/Game/Game.cpp
        engine/entities/Tank/Tank.cpp
        engine/entities/MovableBlock/MovableBlock.cpp
        engine/entities/Block/Block.cpp
        engine/entities/Bullet/Bullet.cpp
        util/geometry/Vector/Vector.cpp
        util/geometry/general_functions/general_functions.cpp
        util/geometry/Segment/Segment.cpp
        util/geometry/Line/Line.cpp
        registry/TcpGameHost/TcpGameHost.cpp)
target_link_libraries(registry_server ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(registry_server sfml-graphics sfml-audio sfml-network)
