
#include "Engine.h"
#include "Player.h"

#include <iostream>
#include <vector>
#include "Renderer.h"

#include <fmod.hpp>

using namespace nu;

int main(int argc, char* argv[]) {

    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

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

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("alert.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("duck-toy.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("error.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("hee-hee.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("mario.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("oof.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("scream.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("whistle.mp3", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    // main
    while (!quit) {

        audio->update();
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quit = true;
        }

        engine.Update();

        player.Draw(renderer);
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_6))
        {
            audio->playSound(sounds[5], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_7))
        {
            audio->playSound(sounds[6], nullptr, false, nullptr);
        }
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_8))
        {
            audio->playSound(sounds[7], nullptr, false, nullptr);
        }


        renderer.Present();
    }
    engine.GetInput().Shutdown();
    engine.GetRenderer().Shutdown();
   

    return 0;
}