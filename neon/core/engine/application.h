#pragma once

class Application
{
public:
	Application() {}
	virtual ~Application() {}

	virtual bool Init() = 0;
	virtual bool Update() = 0;
	virtual bool Render() = 0;

	static 	Application *RegisterApplication();
};
