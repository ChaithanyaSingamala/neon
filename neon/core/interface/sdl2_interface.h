#pragma once
#include "neon_interface.h"
#include <string>

struct SDL_Window;
class SDL2Interface: public NeonInterface
{
	unsigned short width = 800;
	unsigned short height = 600;
	std::string title = "Neon Engine";

	SDL_Window* window = nullptr;
	void *sdlGL = nullptr;
	double deltaTime = 0.0;
	virtual void CalculateUpdateDeltaTime();
	virtual double GetDeltaTime() override;

public:
	SDL2Interface();
	virtual ~SDL2Interface();

	virtual bool Init();
	virtual bool Update();
	virtual bool DeInit();

	virtual unsigned short Width(unsigned short _width = 0) { return width = (_width == 0) ? width : _width; }
	virtual unsigned short Height(unsigned short _height = 0) { return height = (_height == 0) ? height : _height; }
};

