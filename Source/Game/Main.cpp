#include <SDL3/SDL.h>
#include <iostream>
#include "../Engine/Renderer.h"  
#include "../Engine/Random.h"  

using namespace nu;

int main(int argc, char* argv[]) {
        
        Renderer renderer("Game Engine", 1920, 1080);

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
                renderer.SetDrawColor(nu::RandomInt(256), nu::RandomInt(256), nu::RandomInt(256), 255);
                renderer.DrawLine(nu::RandomInt(1920), nu::RandomInt(1080), nu::RandomInt(1920), nu::RandomInt(1080));
            }

            for (int i = 0; i < 20; ++i) {
                renderer.SetDrawColor(nu::RandomInt(256), nu::RandomInt(256), nu::RandomInt(256), 255);
                renderer.DrawPoint(nu::RandomInt(1920), nu::RandomInt(1080));
            }

            for (int i = 0; i < 5; ++i) {
                renderer.SetDrawColor(nu::RandomInt(256), nu::RandomInt(256), nu::RandomInt(256), 255);
                renderer.DrawRect(std::rand() % 1200, nu::RandomInt(1080), 50, 50);
            }

            renderer.Present();
        }

		renderer.Shutdown();

        return 0;
    }
