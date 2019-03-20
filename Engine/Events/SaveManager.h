#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define SAVE_PATH "Engine/Saves/"

struct Save
{
	inline Save()
	{
		name = "";
		info = "";
	}
	std::string name;
	std::string info;
};

class SaveManager
{
public:
	SaveManager(const SaveManager&) = delete;
	SaveManager(SaveManager&&) = delete;
	SaveManager& operator = (const SaveManager&) = delete;
	SaveManager& operator = (SaveManager&&) = delete;

	SaveManager();
	~SaveManager();

	static SaveManager* GetInstance();

	void SaveInit();
	void CreateSave(const std::string& name_, Save info_);
	void AddSave(const std::string& name_, Save& info_);
	const Save GetSave(const std::string& saveName_);
	const Save LoadSave(const std::string& saveName_);

	inline bool CheckExists(const std::string& name)
	{
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

private:
	static std::unique_ptr<SaveManager> saveManagerInstance;
	friend std::default_delete<SaveManager>;

	static std::map<std::string, Save> saves;
};

#endif // !SAVEMANAGER_H