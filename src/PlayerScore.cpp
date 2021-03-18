#include "PlayerScore.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL2/SDL_image.h>


PlayerScore::PlayerScore(Vec2 position, SDL_Renderer* renderer, TTF_Font* font)
    : renderer(renderer), font(font)
{
    surface = TTF_RenderText_Solid(font, "0", { 0xFF, 0xFF, 0xFF, 0xFF });
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = width;
    rect.h = height;
}

PlayerScore::~PlayerScore()
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void PlayerScore::Draw()
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void PlayerScore::SetScore(int score)
{
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), { 0xFF, 0xFF, 0xFF, 0xFF });
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    rect.w = width;
    rect.h = height;
}

void PlayerScore::SetHeart() {

    rect.w = 50;
    rect.h = 50;
    spriteSheet = IMG_Load("./assets/images/heart.png");
    if (spriteSheet == NULL) {
        SDL_Log("Failed to allocate surface");
    }
    else {
        //SDL_Log("Brick allocated at (%d,%d)",xpo,ypo);
        // Create a texture from our surface
        // Textures run faster and take advantage of hardware acceleration
        // SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(renderer, spriteSheet);
    }
}

void PlayerScore::setFlag(int language) {

    rect.w = 100;
    rect.h = 52;
    if (language == 1) {
        
        spriteSheet = IMG_Load("./assets/images/USA-en.png");
    }
    else if (language == 0) {
        spriteSheet = IMG_Load("./assets/images/France-fr.png");
    }
    if (spriteSheet == NULL) {
        SDL_Log("Failed to allocate surface");
    }
    else {
        //SDL_Log("Brick allocated at (%d,%d)",xpo,ypo);
        // Create a texture from our surface
        // Textures run faster and take advantage of hardware acceleration
        // SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(renderer, spriteSheet);
    }
}

void PlayerScore::SetStar() {

    rect.w = 50;
    rect.h = 50;
    spriteSheet = IMG_Load("./assets/images/star.png");
    if (spriteSheet == NULL) {
        SDL_Log("Failed to allocate surface");
    }
    else {
        //SDL_Log("Brick allocated at (%d,%d)",xpo,ypo);
        // Create a texture from our surface
        // Textures run faster and take advantage of hardware acceleration
        // SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 0xFF, 0xFF));
        texture = SDL_CreateTextureFromSurface(renderer, spriteSheet);
    }
}

void PlayerScore::SetText(const char* st){
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    surface = TTF_RenderText_Solid(font, st, { 0xFF, 0xFF, 0xFF, 0xFF });
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    rect.w = width;
    rect.h = height;
    
}