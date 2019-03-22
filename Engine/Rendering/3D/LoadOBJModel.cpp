#include "LoadOBJModel.h"



LoadOBJModel::LoadOBJModel()
{
	currentMaterial = Material();
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	vertices.shrink_to_fit();
	normals.clear();
	normals.shrink_to_fit();
	textureCoords.clear();
	textureCoords.shrink_to_fit();
	indices.clear();
	indices.shrink_to_fit();
	normalIndices.clear();
	normalIndices.shrink_to_fit();
	textureIndices.clear();
	textureIndices.shrink_to_fit();
	meshVertices.clear();
	meshVertices.shrink_to_fit();
	meshes.clear();
	meshes.shrink_to_fit();
}

void LoadOBJModel::LoadModel(const std::string& fileName_)
{
	std::ifstream in(fileName_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open OBJ file " + fileName_, __FILE__, __LINE__);
		return;
	}
	else
	{
		std::string line;
		double maxX, minX, maxY, minY, maxZ, minZ;
		bool firstRunTrough = true;
		while (std::getline(in, line))
		{
			///Vertices
			if (line.substr(0, 2) == "v ")
			{
				std::istringstream v(line.substr(2));
				double x, y, z;
				v >> x >> y >> z;
				if (firstRunTrough)
				{
					maxX = minX = x;
					maxY = minY = y;
					maxZ = minZ = z;
					firstRunTrough = false;
				}
				if (x > maxX)
				{
					maxX = x;
				}
				else if (x < minX)
				{
					minX = x;
				}
				if (y > maxY)
				{
					maxY = y;
				}
				else if (y < minY)
				{
					minY = y;
				}
				if (z > maxZ)
				{
					maxZ = z;
				}
				else if (z < minZ)
				{
					minZ = z;
				}
				vertices.push_back(glm::vec3(x, y, z));
			}
			///Normals
			else if (line.substr(0, 3) == "vn ")
			{
				std::istringstream vn(line.substr(3));
				double x, y, z;
				vn >> x >> y >> z;
				normals.push_back(glm::vec3(x, y, z));
			}
			///Texture Coords
			else if (line.substr(0, 3) == "vt ")
			{
				std::istringstream vt(line.substr(3));
				double x, y, z;
				vt >> x >> y >> z;
				textureCoords.push_back(glm::vec2(x, y));
			}
			///Face Data
			else if (line.substr(0, 2) == "f ")
			{
				std::istringstream f(line.substr(2));
				int p1, t1, n1, p2, t2, n2, p3, t3, n3;
				char ignoreChar;

				f >> p1 >> ignoreChar >> t1 >> ignoreChar >> n1 >>
					p2 >> ignoreChar >> t2 >> ignoreChar >> n2 >> 
					p3 >> ignoreChar >> t3 >> ignoreChar >> n3;
				
				indices.push_back(p1); indices.push_back(p2); indices.push_back(p3);
				textureIndices.push_back(t1); textureIndices.push_back(t2); textureIndices.push_back(t3);
				normalIndices.push_back(n1); normalIndices.push_back(n2); normalIndices.push_back(n3);
			}
			///New Material
			else if (line.substr(0, 7) == "usemtl ")
			{
				if (indices.size() > 0)
				{
					PostProcessing();
				} 
				LoadMaterial(line.substr(7));
			}
		}
		boundingBox.maxVert = glm::vec3(maxX, maxY, maxZ);
		boundingBox.minVert = glm::vec3(minX, minY, minZ);
		PostProcessing();
	}
}

void LoadOBJModel::LoadModel(const std::string& fileName_, const std::string& matName_)
{
	LoadMaterialLibrary(matName_);
	LoadModel(fileName_);
}

std::vector<Vertex> LoadOBJModel::GetVertices()
{
	return meshVertices;
}

std::vector<GLuint> LoadOBJModel::GetIndinces()
{
	return indices;
}

std::vector<SubMesh> LoadOBJModel::GetMeshes()
{
	return meshes;
}

BoundingBox LoadOBJModel::GetBoundingBox()
{
	return boundingBox;
}

void LoadOBJModel::PostProcessing()
{
	for (int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i] - 1];
		vert.normal = normals[normalIndices[i] - 1];
		vert.texCoords = textureCoords[textureIndices[i] - 1];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;
	meshes.push_back(mesh);

	indices.clear();
	indices.shrink_to_fit();
	normalIndices.clear();
	normalIndices.shrink_to_fit();
	textureIndices.clear();
	textureIndices.shrink_to_fit();
	meshVertices.clear();
	meshVertices.shrink_to_fit();
	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& fileName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(fileName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& materialName_)
{
	MaterialLoader::LoadMaterial(materialName_);
}
