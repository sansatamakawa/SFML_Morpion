#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>

// Gestion des ressources : Expérimental
class Res
{
public:
	Res();
	sf::Texture& getTexture(const std::string _path);
	sf::SoundBuffer& getSoundBuffer(const std::string _path);
private:
	const std::string folderTextures;
	const std::string folderSounds;
	std::map<std::string, sf::Texture> mapTextures;
	std::map<std::string, sf::SoundBuffer> mapSoundBuffers;
};