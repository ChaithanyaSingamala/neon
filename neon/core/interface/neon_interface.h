#pragma once
#include <iostream>

class NeonInterface;

class NeonInterface
{
	static NeonInterface* CreateNeonWindow();
	static NeonInterface *instance;
public:
	NeonInterface();
	virtual ~NeonInterface();

	virtual bool Init() = 0;
	virtual bool Update() = 0;
	virtual bool DeInit() = 0;
	virtual unsigned short Width(unsigned short _width = 0) = 0;
	virtual unsigned short Height(unsigned short _height = 0) = 0;

	virtual void ExitApplication();
	virtual double GetDeltaTime();

	static NeonInterface *get();
	static void destroy();
};

