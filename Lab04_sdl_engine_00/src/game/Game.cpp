#include "Game.h"
#include <iostream>

Game::Game() {
	std::cout << "Se ejecuta el constructor de GAME" << std::endl;
}

Game::~Game() {
	std::cout << "Se ejecuta el destructor de GAME" << std::endl;
}

void Game::init() {
	// Inicializar SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Error al inicializar SDL" << std::endl;
		return;
	}

	this->windowWidth= 800;
	this->windowHeight = 600;

	// Crear la ventana
	this->window = SDL_CreateWindow(
		"Lab 04: Intro al motor de videojuegos",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->windowWidth,
		this->windowHeight,
		SDL_WINDOW_SHOWN
	);

	//Crear el renderer
	this->renderer = SDL_CreateRenderer(
		this->window,
		-1,
		0
	);

	this->isRunning = true;
}

void Game::processInput() {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT: 
			this->isRunning = false;
			break;
		case SDL_KEYDOWN: 
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				this->isRunning = false;
			}
			break;
		default:
			break;
		}
	}
}

void Game::render() {
	SDL_SetRenderDrawColor(this->renderer, 30, 30, 30, 255);
	SDL_RenderClear(this->renderer);
	SDL_RenderPresent(this->renderer);
}

void Game::run() {
	while (this->isRunning) {
		processInput();
		//update();
		render();
	}
}

void Game::destroy() {
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}