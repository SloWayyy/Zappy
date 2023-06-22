/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Sound.cpp
*/

#include "encapsulation/Raylibcpp.hpp"

void Raylibcpp::RaySound::initAudioDevice() const
{
    InitAudioDevice();
}

Sound Raylibcpp::RaySound::loadSound(const std::string &fileName)
{
    Music music = LoadMusicStream(fileName.c_str());
    Sound sound;

    if (music.ctxData == NULL)
        throw Error("Error: Cannot load Sound");
    UnloadMusicStream(music);
    sound = LoadSound(fileName.c_str());

    return sound;
}

void Raylibcpp::RaySound::unloadSound(Sound sound)
{
    UnloadSound(sound);
}

void Raylibcpp::RaySound::playSound(Sound sound)
{
    PlaySound(sound);
}

void Raylibcpp::RaySound::stopSound(Sound sound)
{
    StopSound(sound);
}

void Raylibcpp::RaySound::setSoundVolume(Sound sound, float volume)
{
    SetSoundVolume(sound, volume);
}
