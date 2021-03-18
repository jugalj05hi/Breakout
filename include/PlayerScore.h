#ifndef PLAYERSCORE
#define PLAYERSCORE
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Vec2.h"
#include <string>
/**
 * Represents various score displayed in the game
 */
class PlayerScore {
public:
    /**
     * The constructor for PlayerScore that takkes in Position, Renderer and font as an argument
     * @param position The x and y coordinates where the score would be rendered
     * @param ren The pointer to the SDL_Renderer for playerscore to be rendered
     * @param font The type of font to load into when rendering 
     *
    */
    PlayerScore(Vec2 position, SDL_Renderer* ren, TTF_Font* font);
    /**
     * The destructor for playerScore
    */
    ~PlayerScore();
    /**
     * The method to draw or render the score on the screen
    */
    void Draw();
    /**
     * The method to set and update score.
     * @param score the score to be set or updated
    */
    void SetScore(int score);
    /**
     * The method to set and update text.
     * @param text the text to be set or updated
    */
    void SetText(const char* text);
    /**
     *The method will load and set heart icon to indidcate lives left
    */
    void SetHeart();
    /**
     * This method will load and set star icon to indicate the points scored by the player
    */
    void SetStar();
    /**
     * This method will upload and set the flag icon for the language being used
     * @param language the code for the language. As of now 0 stands for french and 1 stands for english 
    */
    void setFlag(int language);
private:
    /**
     * The renderer to store the incoming pointer to the actual renderer of the game loop
    */
    SDL_Renderer* renderer;
    /**
     * The spirtesheet to hold different assets loaded for rendering 
    */
    SDL_Surface* spriteSheet;
    /**
     * We declare the font to hold the font type to be used while rendering 
    */
    TTF_Font* font;
    /**
     * The surface variable will hold the pointer to the surface loaded
    */
    SDL_Surface* surface{};
    /**
     * The texture variable will hold the pointer to the texture generated 
    */
    SDL_Texture* texture{};
    /**
     * The rect variable is responsible for positioning the texture
    */
    SDL_Rect rect{};

};
#endif