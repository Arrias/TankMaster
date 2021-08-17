#include <SFML/Network.hpp>
#include <memory>
#include "../engine/entities/Tank/Tank.h"
#include "../engine/Game/Game.h"
#include "../server/UdpRoom.h"
#include "../server/TcpRoom.h"

int main() {
    UdpRoom my_room(2010);
    my_room.launch();
    return 0;
}