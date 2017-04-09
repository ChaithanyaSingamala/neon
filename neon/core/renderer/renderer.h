#pragma once
class Renderer
{
	static Renderer *instance;

	void Init();
	void DeInit();

public:
	Renderer();
	virtual ~Renderer();

	static Renderer *get();
	static void destroy();
};

