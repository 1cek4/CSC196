#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "../Engine/Renderer.h"
#include "../Engine/Random.h"
#include "../Engine/Input.h"
#include "../Engine/Vector2.h"

using namespace nu;

int main(int argc, char* argv[]) {

    Renderer renderer("Game Engine", 1920, 1080);
    Input input;

    if (!renderer.IsValid()) return 1;

    SDL_Event e;
    bool quit = false;

    std::vector<Vector2> points;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        input.Update();

        if (input.GetButtonPressed(Input::Left)) std::cout << "button pressed\n";
        if (input.GetButtonDown(Input::Left)) std::cout << "button down\n";

        if (input.GetButtonDown(Input::Left)) {
            Vector2 position = input.GetMousePosition();

            if (points.empty()) {
                points.push_back(position);
            }
            else if ((position - points.back()).Length() > 10.0f) {
                points.push_back(position);
            }
        }

        renderer.SetDrawColor(0, 0, 0, 255);
        renderer.Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            renderer.SetDrawColor(nu::RandomInt(256), nu::RandomInt(256), nu::RandomInt(256), 255);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        renderer.Present();
    }

    renderer.Shutdown();

    return 0;
}