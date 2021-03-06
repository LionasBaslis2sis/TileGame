#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "src/game.hpp"

int main(int argc, char** argv) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Could not init SDL, error: %s", SDL_GetError());
    }

    // This is weird
    Uint32 img_flags = IMG_INIT_PNG | IMG_INIT_TIF;
    if((IMG_Init(img_flags) & img_flags) != img_flags) {
        SDL_Log("Could not init IMG, error: %s", IMG_GetError());
    }
    
    Game* game = new Game("Tile Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 768, 512);
    Uint32 last_time = 0, current_time = 0;
    while(game->running) {
        last_time = current_time;
        current_time = SDL_GetTicks();
        float delta = current_time - last_time;
        game->update(delta);
        game->draw();
    }

    delete game;

    SDL_Quit();
    IMG_Quit();

    return EXIT_SUCCESS;
}