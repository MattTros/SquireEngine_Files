#include "SaveManager.h"

std::unique_ptr<SaveManager> SaveManager::saveManagerInstance = nullptr;
std::map<std::string, Save> SaveManager::saves = std::map<std::string, Save>();

SaveManager::SaveManager()
{
}

SaveManager::~SaveManager()
{
	if (saves.size() > 0)
	{
		saves.clear();
	}
}

void SaveManager::SaveInit()
{
	std::ofstream out;
	const char* path = "Engine/Saves/save1.txt";
	out.open(path, std::ios::out | std::ios::app);
	out.close();
}

SaveManager* SaveManager::GetInstance()
{
	if (saveManagerInstance.get() == nullptr)
	{
		saveManagerInstance.reset(new SaveManager);
	}
	return saveManagerInstance.get();
}

void SaveManager::AddSave(const std::string& name_, Save& save_)
{
	saves.insert(std::pair<std::string, Save>(name_, save_));
}

const Save SaveManager::GetSave(const std::string& saveName_)
{
	if (saves.find(saveName_) != saves.end())
	{
		return saves[saveName_];
	}
	return Save();
}

void SaveManager::CreateSave(const std::string& saveName_, Save save_)
{
	if (saves.find(saveName_) != saves.end())
	{
		std::printf("Save already exists.\n");
		return;
	}
	else if (CheckExists("Engine/Saves/" + saveName_ + ".txt"))
	{
		std::printf("Save already exists.\n");
		return;
	}

	//! Write to file:
	std::ofstream myfile;
	myfile.open(SAVE_PATH + saveName_ + ".txt", std::ios::out);
	if (myfile.is_open())
	{
		std::cout << "Opened file.";
		myfile << "name " << save_.name.c_str() << "\n";
		myfile << "info " << save_.info.c_str() << "\n";
		myfile.flush();
		myfile.close();

		AddSave(save_.name, save_);
	}
	else std::cout << "Unable to open file.\n";

	std::cout << "Save created.\n";
}

const Save SaveManager::LoadSave(const std::string& saveName_)
{
	if (saves.find(saveName_) != saves.end())
	{
		std::printf("Save doesn't exist.\n");
		return Save();
	}

	//! Read from file:
	std::string filePath = SAVE_PATH + saveName_ + ".txt";
	std::ifstream myfile(filePath.c_str(), std::ios::in);

	if (myfile.is_open())
	{
		std::cout << "Opened file.\n";
		std::string line;
		Save loadedSave;

		while (std::getline(myfile, line))
		{
			if (line.substr(0, 5) == "name ")
			{
				std::istringstream name(line.substr(5));
				name >> loadedSave.name;
			}

			if (line.substr(0, 5) == "info ")
			{
				std::istringstream info(line.substr(5));
				info >> loadedSave.info;
			}
		}
		std::cout << "Name: " << loadedSave.name << " Info: " << loadedSave.info << std::endl;
		return loadedSave;
	}
	else std::cout << "Unable to open file";

	return Save();
}