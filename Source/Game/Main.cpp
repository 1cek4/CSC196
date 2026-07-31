#include "Engine.h"
#include "GDGame.h"

#include <iostream>

using namespace nu;

int main(int argc, char* argv[]) {
	SetWorkingDirectory("Assets");
	if (!engine.Initialize()) {
		std::cerr << "Engine failed to initialize.\n";
		return -1;
	}

	engine.GetAudio().LoadSound("bgmusic", "Sleepyhead.mp3");

	GDGame game;
	game.Initialize();

	bool quit = false;

	while (!quit) {
		SDL_Event e;

		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) quit = true;
		}

		engine.Update();

		float dt = engine.GetTime().GetDeltaTime();
		game.Update(dt);

		Renderer& renderer = engine.GetRenderer();
		renderer.SetColor(20, 20, 30, 255);
		renderer.Clear();

		game.Draw(renderer);

		renderer.Present();
	}

	engine.Shutdown();

	return 0;
}
