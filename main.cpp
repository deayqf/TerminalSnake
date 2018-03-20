#include "game.h"

int main()
{
    Game* game = new Game();
    game->loop();
    game->~Game();
    return 0;
}
