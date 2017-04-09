#pragma once
#include <iostream>

class NeonInterface;

class NeonInterface
{
	static NeonInterface* CreateWindow();
	static NeonInterface *instance;
public:
	NeonInterface();
	virtual ~NeonInterface();

	virtual bool Init() = 0;
	virtual bool Update() = 0;
	virtual bool DeInit() = 0;

	virtual void ExitApplication();

	static NeonInterface *get();
	static void destroy();
};

