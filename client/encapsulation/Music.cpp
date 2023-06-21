/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Music
*/

#include "encapsulation/Raylibcpp.hpp"

void Raylibcpp::RayMusic::initAudioDevice() const
{
    InitAudioDevice();
}

Music Raylibcpp::RayMusic::loadMusicStream(const std::string &fileName)
{
    Music music = LoadMusicStream(fileName.c_str());
    if (music.ctxType == 0)
        throw Error("Error: Cannot load music");
    return music;
}

void Raylibcpp::RayMusic::unloadMusicStream(Music music)
{
    UnloadMusicStream(music);
}

void Raylibcpp::RayMusic::playMusicStream(Music music)
{
    PlayMusicStream(music);
}

void Raylibcpp::RayMusic::updateMusicStream(Music music)
{
    UpdateMusicStream(music);
}

void Raylibcpp::RayMusic::stopMusicStream(Music music)
{
    StopMusicStream(music);
}

void Raylibcpp::RayMusic::pauseMusicStream(Music music)
{
    PauseMusicStream(music);
}

void Raylibcpp::RayMusic::resumeMusicStream(Music music)
{
    ResumeMusicStream(music);
}

void Raylibcpp::RayMusic::setMusicVolume(Music music, float volume)
{
    SetMusicVolume(music, volume);
}

void Raylibcpp::RayMusic::setMusicPitch(Music music, float pitch)
{
    SetMusicPitch(music, pitch);
}

float Raylibcpp::RayMusic::getMusicTimeLength(Music music)
{
    return GetMusicTimeLength(music);
}

float Raylibcpp::RayMusic::getMusicTimePlayed(Music music)
{
    return GetMusicTimePlayed(music);
}

void Raylibcpp::RayMusic::closeAudioDevice() const
{
    CloseAudioDevice();
}