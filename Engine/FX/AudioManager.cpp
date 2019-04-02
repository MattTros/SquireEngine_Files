#include "AudioManager.h"
#include "../Core/Debug.h"

std::unique_ptr<AudioManager> AudioManager::audioManagerInstance = nullptr;
std::map<std::string, Mix_Chunk*> AudioManager::soundFX = std::map<std::string, Mix_Chunk*>();
std::map<std::string, Mix_Music*> AudioManager::music = std::map<std::string, Mix_Music*>();

AudioManager::AudioManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		Debug::Error("Failed to initialize mixer", __FILE__, __LINE__);
	}
}


AudioManager::~AudioManager()
{
	Mix_Quit();
	if (soundFX.size() > 0)
	{
		soundFX.clear();
	}
	if (music.size() > 0)
	{
		music.clear();
	}
}

AudioManager* AudioManager::GetInstance()
{
	if (audioManagerInstance.get() == nullptr)
	{
		audioManagerInstance.reset(new AudioManager);
	}
	return audioManagerInstance.get();
}

void AudioManager::SetAudioVolume(int channel_, int volume_)
{
	Mix_Volume(channel_, volume_);
}

void AudioManager::SetMusicVolume(int volume_)
{
	Mix_VolumeMusic(volume_);
}

void AudioManager::LoadSoundFXFile(const std::string& audioName_, const std::string& fileName_)
{
	std::string filePath = "Resources/Audio/" + fileName_;

	if (soundFX[audioName_] == nullptr)
	{
		soundFX[audioName_] = Mix_LoadWAV(filePath.c_str());
		if (soundFX[audioName_] == NULL)
		{
			Debug::Error("SoundFX file: " + filePath + " failed to load", __FILE__, __LINE__);
		}
	}
}

void AudioManager::LoadMusicFile(const std::string& audioName_, const std::string& fileName_)
{
	std::string filePath = "Resources/Audio/" + fileName_;

	if (music[audioName_] == nullptr)
	{
		music[audioName_] = Mix_LoadMUS(filePath.c_str());
		if (music[audioName_] == NULL)
		{
			Debug::Error("Music file: " + filePath + " failed to load", __FILE__, __LINE__);
		}
	}
}

void AudioManager::PlaySoundFX(std::string audioName_, int loops_, int channel_)
{
	Mix_PlayChannel(channel_, soundFX[audioName_], loops_);
}

void AudioManager::PlayMusic(std::string audioName_, int loops_)
{
	Mix_PlayMusic(music[audioName_], loops_);
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}

void AudioManager::StopAudioChannel(int channel_)
{
	Mix_HaltChannel(channel_);
}

