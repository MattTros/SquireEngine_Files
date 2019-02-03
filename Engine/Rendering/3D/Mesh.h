#ifndef MESH_H
#define MESH_H

#include <glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Graphics/Shader.h"
#include "../../Camera/Camera.h"
#include "../../Graphics/MaterialHandler.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct SubMesh
{
	std::vector<Vertex> vertexList;
	std::vector<GLuint> meshIndices;
	Material material;
};

class Mesh
{
public:
	Mesh(SubMesh subMesh_, GLuint shaderProgram_);
	~Mesh();
	void Render(std::vector<glm::mat4> instances_, Camera* camera_);
private:
	GLuint VAO, VBO;
	GLuint shaderProgram;
	///Model Locations
	GLuint modelLocation;
	GLuint viewLocation;
	GLuint projectionLocation;
	///Material Locations
	GLuint diffuseMapLocation;
	GLuint shineStrengthLocation;
	GLuint transparencyLocation;
	GLuint ambientLocation;
	GLuint diffuseLocation;
	GLuint specularLocation;
	///Light Locations
	GLuint viewPositionLocation;
	GLuint lightPositionLocation;
	GLuint lightAmbientLocation;
	GLuint lightDiffuseLocation;
	GLuint lightColorLocation;
	SubMesh subMesh;

	void GenerateBuffers();
};

#endif // !MESH_H


