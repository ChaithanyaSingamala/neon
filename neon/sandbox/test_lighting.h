#include <iostream>
#include "engine\application.h"
#include "glm\glm.hpp"

class Camera;
class Mesh;
class Shader;
class Texture;

class TestLighting : public Application
{

	Camera *camera = nullptr;
	Mesh* testModel = nullptr;
	Mesh* testPlaneModel = nullptr;
	Mesh* testModelLightSource = nullptr;
	Shader *shader = nullptr;
	Shader *shaderForLightSource = nullptr;
	Texture *texture1 = nullptr;

	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

public:
	virtual bool Init();
	virtual bool Update();
	virtual bool Render();
	virtual bool DeInit();

	virtual void HandleKeyInput(int key, int action) override;
	virtual void HandleMouseButtonInputs(int button, int action) override;
	virtual void HandleMouseScrollInputs(double xoffset, double yoffset) override;
	virtual void HandleMouseCursorInputs(double xpos, double ypos) override;

};
