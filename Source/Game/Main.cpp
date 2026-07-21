
#include "Engine.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include "Renderer.h"

using namespace nu;

int main(int argc, char* argv[]) {

    //Init
    engine.Initialize();
	Renderer& renderer = engine.GetRenderer();

    std::vector<Vector2> modelPoints{ Vector2{ -3.0f, 3.0f }, Vector2{ 3.0f, 3.0f }, Vector2{ 0.0f, -3.0f }, Vector2{ -3.0f, 3.0f } };


    std::vector<Vector2> tailPoints{
        Vector2{ -2.0f,  2.0f },
        Vector2{ -6.0f,  1.0f },  
        Vector2{ -3.0f,  0.0f },  
        Vector2{ -6.0f, -1.0f },  
        Vector2{ -2.0f, -2.0f }  
    };
    Mesh tailMesh{ tailPoints, Color{ 0.8f, 0.1f, 0.1f } }; 

    std::vector<Vector2> bodyPoints{
        Vector2{ -2.0f,  2.0f },
        Vector2{  2.0f,  2.0f },
        Vector2{  2.0f, -2.0f },
        Vector2{ -2.0f, -2.0f },
        Vector2{ -2.0f,  2.0f }
    };
    Mesh bodyMesh{ bodyPoints, Color{ 0.0f, 0.0f, 1.0f } }; 

    std::vector<Vector2> nosePoints{
        Vector2{ 2.0f,  2.0f },
        Vector2{ 6.0f,  0.0f },
        Vector2{ 2.0f, -2.0f },
        Vector2{ 2.0f,  2.0f }
    };
    Mesh noseMesh{ nosePoints, Color{ 1.0f, 0.85f, 0.0f } };

    Model model{ std::vector<Mesh>{ tailMesh, bodyMesh, noseMesh } };

    Actor player{ Transform{ Vector2 { 640.0f, 512.0f }, 0.0f, 50.0f }, model };

    std::vector<Vector2> points;
    std::vector<bool> startsNewShape;

    bool quit = false;


    while (!quit) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        engine.Update();

        player.Draw(renderer);


        renderer.Present();
    }
    engine.GetInput().Shutdown();
    engine.GetRenderer().Shutdown();
   

    return 0;
}