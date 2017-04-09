#include <iostream>
#include "engine\application.h"

class TestSimpleTriangle : public Application
{
public:
	bool Init();
	bool Update();
	bool Render();
};
