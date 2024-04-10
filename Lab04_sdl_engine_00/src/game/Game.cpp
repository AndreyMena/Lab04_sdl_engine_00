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

	if (TTF_Init() < 0) {
		std::cout << "Error al inicializar SDL_TTF" << std::endl;
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

	// Cargar texto
	this->fontSize = 12;
	this->font = TTF_OpenFont("./assets/fonts/press_start_2p.ttf",
		this->fontSize);

	this->isRunning = true;

	// Inicializar datos de la imagen
	this->imgWidth = 32;
	this->imgHeight = 32;
	this->pos.x = (this->windowWidth / 2) - (this->imgWidth / 2);
	this->pos.y = (this->windowHeight / 2) - (this->imgHeight / 2);
	SDL_Surface* imgSurface = IMG_Load("./assets/images/skull_00.png");
	this->imgTexture = SDL_CreateTextureFromSurface(this->renderer, imgSurface);
	SDL_FreeSurface(imgSurface);
	this->srcRect.x = 0;
	this->srcRect.x = 0;
	this->srcRect.w = this->imgWidth;
	this->srcRect.h = this->imgHeight;

	// Inicializardatos del texto
	this->message = "Lab 04: Intro al motor de videojuegos";
	this->fontColor.r = 255;
	SDL_Surface* txtSurface = TTF_RenderText_Solid(this->font,
		this->message.c_str(),
		this->fontColor
	);
	this->txtTexture = SDL_CreateTextureFromSurface(this->renderer, txtSurface);
	this->txtWidth = txtSurface->w;
	this->txtHeight = txtSurface->h;
	this->txtPos.x = (this->windowWidth / 2) - (this->txtWidth / 2);
	this->txtPos.y = 20;
	SDL_FreeSurface(txtSurface);
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

	SDL_Rect imgDstRect = {
		this->pos.x,
		this->pos.y,
		this->imgWidth,
		this->imgHeight
	};

	SDL_Rect txtDstRect = {
	this->txtPos.x,
	this->txtPos.y,
	this->txtWidth,
	this->txtHeight
	};

	// Dibujar imagen
	// https://wiki.libsdl.org/SDL2/SDL_RenderCopyEx
	SDL_RenderCopyEx(
		this->renderer,
		this->imgTexture,
		&this->srcRect,
		&imgDstRect,
		this->angle,
		NULL,
		SDL_FLIP_NONE
	);

	SDL_RenderCopyEx(
		this->renderer,
		this->txtTexture,
		NULL, // Si es NULL dibuja toda la textura
		&txtDstRect,
		this->txtAngle,
		NULL,
		SDL_FLIP_NONE
	);

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
	SDL_DestroyTexture(this->txtTexture);
	SDL_DestroyTexture(this->imgTexture);

	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);

	TTF_Quit();
	SDL_Quit();
}