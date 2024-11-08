#include "entry.h"

#include "game/game.h" 

extern std::shared_ptr<slam::game> make_game();

namespace slam
{

    int entry_point(int argc, char* argv[])
    {
        // TODO add a console here

        std::shared_ptr<game> game = make_game();

       return game->run();
    }
};