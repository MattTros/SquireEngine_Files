#version 330 core

struct Material
{
	sampler2D diffuseMap;
	float shininess;
	float transparency;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Light
{
	vec3 lightPos;
	float ambient;
	float diffuse;
	vec3 lightColor;
};

in vec3 Normal;
in vec2 TexCoords;
in vec3 FragPosition;

uniform sampler2D inputTexture;
uniform Light light;
uniform Material material;
uniform vec3 viewPosition;

out vec4 color;

void main()
{

	vec3 viewDir = normalize(viewPosition - FragPosition);

	//! color gradient:

	//! Outside
	if (dot(viewDir, Normal) < 0.5f)
	{ 
		//! Darker:
		color = vec4(0.4f, 0.4f, 0.4f, 1.0f);
	}
	//! Inside
	else
	{
		//! Dark:
		color = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	}
}