#ifndef MODEL_H
#define MODEL_H

#include <glm/gtc/matrix_transform.hpp>
#include "Mesh.h"
#include "LoadOBJModel.h"

class Model
{
public:
	Model(const std::string& objFile_, const std::string& matFile_, GLuint shaderProgram_);
	~Model();
	void Render(Camera* camera_);
	void AddMesh(Mesh* mesh_);
	GLuint CreateInstance(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void UpdateInstance(GLuint index_, glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	glm::mat4 GetTransform(GLuint index_) const;

	BoundingBox GetBoundingBox();
	GLuint GetShader();
	Mesh* GetMesh(GLuint shaderProg_);
private:
	std::vector<Mesh*> subMeshes;
	GLuint shaderProgram;
	std::vector<glm::mat4> modelInstances;

	glm::mat4 GetTransform(glm::vec3 position_, float angle_, glm::vec3 rotation_, glm::vec3 scale_);
	void LoadModel();

	LoadOBJModel* obj;
	BoundingBox boundingBox;
};

#endif // !MODEL_H



