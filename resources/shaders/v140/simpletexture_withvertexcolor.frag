#version 140

out vec4 fragColor;
in vec3 vColor;
in vec2 vUV;

uniform sampler2D Texture;

void main()
{
	vec4 textureColor = texture(Texture, vUV);
	fragColor = vec4(textureColor.rgb + vColor, textureColor.a);
}