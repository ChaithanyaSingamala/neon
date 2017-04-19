#include <iostream>

class Mesh;
class Shader;

Mesh *CreateModelCube(Shader *_shader);

Mesh *CreateModelPlaneXZ(Shader *_shader, float _size = 2.0f, float _yOffset = -1.0f);

char *ShaderCodeLightingVert();
char *ShaderCodeLightingFrag();

char *ShaderCodeBaseVert();
char *ShaderCodeBaseFrag();

