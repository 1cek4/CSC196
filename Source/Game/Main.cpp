#include <SDL3/SDL.h>
#include <iostream>
#include "../Engine/Renderer.h"  

int main(int argc, char* argv[]) {
    Renderer renderer("SDL3 Project", 1920, 1080);

    if (!renderer.IsValid()) return 1;

    SDL_Event e;
    bool quit = false;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        renderer.SetDrawColor(0, 0, 0, 255);
        renderer.Clear();

        for (int i = 0; i < 10; ++i) {
            renderer.SetDrawColor(std::rand() % 256, std::rand() % 256, std::rand() % 256, 255);
            renderer.DrawLine(std::rand() % 1920, std::rand() % 1080, std::rand() % 1920, std::rand() % 1080);
        }

        for (int i = 0; i < 20; ++i) {
            renderer.SetDrawColor(std::rand() % 256, std::rand() % 256, std::rand() % 256, 255);
            renderer.DrawPoint(std::rand() % 1920, std::rand() % 1080);
        }

        for (int i = 0; i < 5; ++i) {
            renderer.SetDrawColor(std::rand() % 256, std::rand() % 256, std::rand() % 256, 255);
            renderer.DrawRect(std::rand() % 1200, std::rand() % 1080, 50, 50);
        }

        renderer.Present();
    }

    return 0;
}