#include "MaterialLoader.h"

void MaterialLoader::LoadMaterial(std::string fileName_)
{
	std::ifstream in(fileName_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open MTL file: " + fileName_, __FILE__, __LINE__);
		return;
	}
	Material m = Material();
	std::string materialName = "";
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			if (m.diffuseMap != 0)
			{
				MaterialHandler::GetInstance()->AddMaterial(materialName, m);
				m = Material();
			}
			materialName = line.substr(7);
			m.diffuseMap = LoadTexture(materialName);
		}
		else if (line.substr(0, 4) == "	Ns ")
		{
			std::istringstream ns(line.substr(4));
			double value;
			ns >> value;
			m.shininess = value;
		}
		else if (line.substr(0, 3) == "	d ")
		{
			std::istringstream d(line.substr(3));
			double value;
			d >> value;
			m.transparency = value;
		}
		else if (line.substr(0, 4) == "	Ka ")
		{
			std::istringstream ka(line.substr(4));
			double x, y, z;
			ka >> x >> y >> z;
			m.ambient = glm::vec3(x, y, z);
		}
		else if (line.substr(0, 4) == "	Kd ")
		{
			std::istringstream kd(line.substr(4));
			double x, y, z;
			kd >> x >> y >> z;
			m.diffuse = glm::vec3(x, y, z);
		}
		else if (line.substr(0, 4) == "	Ks ")
		{
			std::istringstream ks(line.substr(4));
			double x, y, z;
			ks >> x >> y >> z;
			m.specular = glm::vec3(x, y, z);
		}
	}
	if (m.diffuseMap != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(materialName, m);
	}
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "Resources/Textures/" + fileName_ + ".jpg");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}
