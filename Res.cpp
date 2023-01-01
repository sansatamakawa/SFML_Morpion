#include "Res.h"

using namespace std;

Res::Res() : folderTextures("Images/"), folderSounds("Sons/")
{
    cout << "Constructeur Res" << endl;
}

sf::Texture& Res::getTexture(const string _path)
{
    bool exists = false;

    // Vérifie si la texture n'est pas déjà chargée
    if (!mapTextures.empty())
    {
        for (const auto& a : mapTextures)
        {
            if (a.first == _path)
            {
                exists = true;
                break;
            }
        }
    }

    // Charge la texture puis la retourne si elle n'est pas chargée, sinon la texture est retournée
    if (!exists)
    {
        sf::Texture texture;
        texture.loadFromFile(folderTextures + _path);
        mapTextures.insert(std::make_pair(_path, texture));
        return mapTextures[_path];
    }
    else
    {
        return mapTextures[_path];
    }
}

sf::SoundBuffer& Res::getSoundBuffer(const std::string _path)
{
    bool exists = false;

    if (!mapSoundBuffers.empty())
    {
        for (const auto& a : mapSoundBuffers)
        {
            if (a.first == _path)
            {
                exists = true;
                break;
            }
        }
    }

    if (!exists)
    {
        sf::SoundBuffer soundBuffer;
        soundBuffer.loadFromFile(folderSounds + _path);
        mapSoundBuffers.insert(std::make_pair(_path, soundBuffer));
        return mapSoundBuffers[_path];
    }
    else
    {
        return mapSoundBuffers[_path];
    }
}
