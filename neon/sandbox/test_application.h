#include <iostream>
#include "engine\application.h"

class TestApplication : public Application
{
public:
	bool Init();
	bool Update();
	bool Render();
};
