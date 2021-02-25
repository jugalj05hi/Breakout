#include "ResourceManager.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>


ResourceManager& ResourceManager::getInstance() {
    static ResourceManager* instance = new ResourceManager();
    return *instance;
}

SDL_Surface* ResourceManager::loadTexture(const char* filePath) {
    if (map.find(filePath) != map.end()) {
        return map.at(filePath);
    }
    else {
        // create resource
        SDL_Surface* spriteSheet = IMG_Load(filePath);
        // store in dict
        map[filePath] = spriteSheet;
        if (map[filePath] == NULL)
            SDL_Log("Failed to insert into map");
        return spriteSheet;
    }
}


TTF_Font* ResourceManager::loadFont(const char* filePath) {
    if (fontMap.find(filePath) != fontMap.end()) {
        return fontMap.at(filePath);
    }
    else {
        //Initialize SDL_ttf
        if (TTF_Init() == -1)
        {
            SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        }
        // create resource
        TTF_Font* font = TTF_OpenFont(filePath, 40);
        // store in dict
        fontMap.insert({ filePath, font });
        if (fontMap.at(filePath) != font)
            SDL_Log("Failed to insert into map");
        return font;
    }
}


Mix_Music* ResourceManager::loadMusic(const char* filePath) {
    if (soundMap.find(filePath) != soundMap.end()) {
        return soundMap.at(filePath);
    }
    else {
        // create resource
        Mix_Music* sound = Mix_LoadMUS(filePath);
        // store in dict
        soundMap[filePath] = sound;
        return sound;
    }
}

Mix_Chunk* ResourceManager::loadWAV(const char* filePath) {
    if (soundEffectMap.find(filePath) != soundEffectMap.end()) {
        return soundEffectMap.at(filePath);
    }
    else {
        // create resource
        Mix_Chunk* sound = Mix_LoadWAV(filePath);
        // store in dict
        soundEffectMap[filePath] = sound;
        return sound;
    }
}

void ResourceManager::setWords(std::string english, std::string french) {

    languageMap.insert({ english, french });
    
}

const char* ResourceManager::getWords(const char* word) {
    if (!language) {
        std::string s = word;
        try {
            return languageMap.find(s)->second.c_str();
        }
        catch (std::out_of_range& e) {
            std::cout << "Something broke in getwords" << std::endl;
        }
    }
    return word;
}

void ResourceManager::setLanguage(int languageCode) {
    language = languageCode;
}

void ResourceManager::loadWords() {
    std::ifstream english("./assets/scripts/english.txt");
    std::ifstream french("./assets/scripts/french.txt");
    // const char* en;
    // const char* fr;
    std::string en;
    std::string fr;
    if (english && french) {

        while (std::getline(english, en, '\n') && std::getline(french, fr, '\n')) {
           
            setWords(en, fr);
            
        }
    }

    
}



