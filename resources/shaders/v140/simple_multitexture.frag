#version 140

out vec4 fragColor;
in vec3 vColor;
in vec2 vUV;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
	vec4 textureColor1 = texture(Texture1, vUV);
	vec4 textureColor2 = texture(Texture2, vUV);
	fragColor = textureColor1 * (1.0 -floor(vUV.x + 0.5)) + textureColor2 * floor(vUV.x + 0.5);
}