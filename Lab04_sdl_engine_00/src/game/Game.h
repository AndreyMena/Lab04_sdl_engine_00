#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Game {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	size_t windowWidth = 0;
	size_t windowHeight = 0;

	bool isRunning = false;

	// Atributos de la imagen
	SDL_Texture* imgTexture = nullptr;


	void processInput();
	void update();
	void render();
public:
	Game();
	~Game();
	void init();
	void run();
	void destroy();
};


#endif // !GAME_H


