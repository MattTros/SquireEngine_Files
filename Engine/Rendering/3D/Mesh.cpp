#include "Mesh.h"

Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_)
{
	VAO = 0;
	VBO = 0;
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	subMesh.vertexList.clear();
	subMesh.vertexList.shrink_to_fit();
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	///POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	///NORMALS
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	///TEXTURE COORDINATES
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLocation = glGetUniformLocation(shaderProgram, "model");
	viewLocation = glGetUniformLocation(shaderProgram, "view");
	projectionLocation = glGetUniformLocation(shaderProgram, "projection");
	
	diffuseMapLocation = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shineStrengthLocation = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLocation = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLocation = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLocation = glGetUniformLocation(shaderProgram, "material.diffuse");
	specularLocation = glGetUniformLocation(shaderProgram, "material.specular");

	viewPositionLocation = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPositionLocation = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbientLocation = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuseLocation = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightColorLocation = glGetUniformLocation(shaderProgram, "light.lightColor");

	iFramesID = glGetUniformLocation(shaderProgram, "iFrames");
	transparencyID = glGetUniformLocation(shaderProgram, "transparency");
	timerID = glGetUniformLocation(shaderProgram, "time");
}

void Mesh::Render(std::vector<glm::mat4> instances_, Camera* camera_)
{
	glUniform1i(diffuseMapLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);
	glUniform1f(shineStrengthLocation, subMesh.material.shininess);
	glUniform1f(transparencyLocation, subMesh.material.transparency);
	glUniform3f(ambientLocation, subMesh.material.ambient.x, subMesh.material.ambient.y, subMesh.material.ambient.z);
	glUniform3f(diffuseLocation, subMesh.material.diffuse.x, subMesh.material.diffuse.y, subMesh.material.diffuse.z);
	glUniform3f(specularLocation, subMesh.material.specular.x, subMesh.material.specular.y, subMesh.material.specular.z);

	glUniform3f(viewPositionLocation, camera_->GetPosition().x, camera_->GetPosition().y, camera_->GetPosition().z);
	glUniform3f(lightPositionLocation, camera_->GetLightSources()[0]->GetPosition().x, camera_->GetLightSources()[0]->GetPosition().y, camera_->GetLightSources()[0]->GetPosition().z);
	glUniform1f(lightAmbientLocation, camera_->GetLightSources()[0]->GetAmbient());
	glUniform1f(lightDiffuseLocation, camera_->GetLightSources()[0]->GetDiffuse());
	glUniform3f(lightColorLocation, camera_->GetLightSources()[0]->GetLightColor().x, camera_->GetLightSources()[0]->GetLightColor().y, camera_->GetLightSources()[0]->GetLightColor().z);
	
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));
	glBindVertexArray(VAO);

	glUniform1f(iFramesID, iFramesBool);
	glUniform1f(transparencyID, transparency);
	glUniform1f(timerID, time);

	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
