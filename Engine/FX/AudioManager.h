#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL_mixer.h>
#include <iostream>
#include <map>

class Debug;

class AudioManager
{
public:
	AudioManager(const AudioManager&) = delete;
	AudioManager(AudioManager&&) = delete;
	AudioManager& operator = (const AudioManager&) = delete;
	AudioManager& operator = (AudioManager&&) = delete;

	static AudioManager* GetInstance();

	void SetAudioVolume(int channel_, int volume_);
	void SetMusicVolume(int volume_);

	void LoadSoundFXFile(const std::string& audioName_, const std::string& fileName_);
	void LoadMusicFile(const std::string& audioName_, const std::string& fileName_);

	void PlaySoundFX(std::string audioName_, int loops_ = 0, int channel_ = 0);
	void PlayMusic(std::string musicName_, int loops_ = -1);
	void PauseMusic();
	void ResumeMusic();
private:
	AudioManager();
	~AudioManager();

	static std::unique_ptr<AudioManager> audioManagerInstance;
	friend std::default_delete<AudioManager>;

	static std::map<std::string, Mix_Chunk*> soundFX;
	static std::map<std::string, Mix_Music*> music;
};

#endif // !AUDIOMANAGER_H



