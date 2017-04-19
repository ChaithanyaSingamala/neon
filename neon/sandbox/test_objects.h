#include <iostream>

class Model;
class Shader;

Model *CreateModelCube(Shader *_shader);

Model *CreateModelPlaneXZ(Shader *_shader, float _size = 2.0f, float _yOffset = -1.0f);

char *ShaderCodeLightingVert();
char *ShaderCodeLightingFrag();


