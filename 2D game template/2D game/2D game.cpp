#include "Game.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/lib/SDL2.lib" )
#pragma comment( lib, "SDL/lib/SDL2main.lib" )

enum gamestate
{
    SETUP,
    START,
    UPDATE,
    CLEANUP,
    QUIT
};

Game* game = NULL;

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        std::cout << "Init -> Bad Thing, Error: " << SDL_GetError() << std::endl;

    gamestate state = SETUP;

    game = new Game();

    bool loop = true;
    while (loop)
    {
        switch (state)
        {
        case SETUP:
            if (!game->SetUp())
                state = CLEANUP;
            else
                state = START;
            break;
        case START:
            if (!game->Start())
                state = CLEANUP;
            else
                state = UPDATE;
            break;
        case UPDATE:
            if (!game->Update())
                state = CLEANUP;
            break;
        case CLEANUP:
            game->CleanUp();
            state = QUIT;
            break;
        case QUIT:
            loop = false;
            break;
        }
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}

