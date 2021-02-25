#ifndef PADDLE
#define PADDLE
#include "Vec2.h"
#include "Ball.h"
#include "Contact.h"
#include <SDL2/SDL.h>
#include "ResourceManager.h"
const int PADDLE_WIDTH = 150;
const int PADDLE_HEIGHT = 30;
const float PADDLE_SPEED = 1.0f;
/**
 * Represents Paddle in the game
 */

class Paddle {
public:
    /**
     * The constructor of the Paddle class that takes in initial position and velocity along with renderer as arguments
     * @param position The Vec2 object that represents paddle's initial position
     * @param velocity The Vec2 object that represents paddle's initial velocity
     * @param renderer The renderer to help render the paddle
    */
    Paddle(Vec2 position, Vec2 velocity, SDL_Renderer* renderer);
    /**
     * This Method helps the paddle to be rendered on the screen
    */
    void Draw();
    /**
     * This Method checks the collision of Paddle with ball and returns where the ball hit the paddle
     * @param ball The object of the ball
     * @return The type of contact 
    */
    Contact checkCollision(Ball const& ball);
    /**
     * This method will reset the padddle to it's inital position and velocity
    */
    void Reset();
    /**
     * This method will update the position of the paddle
     * @param dt The time passed between each frame
     * @param WINDOW_WIDTH The width of the game window
    */
    void Update(float dt, int WINDOW_WIDTH);

    /**
     * The velocity of the paddle
    */
    Vec2 velocity;


private:
    /**
     * The position of the paddle 
    */
    Vec2 position;
    /**
     * The default position to be used to reset 
    */
    Vec2 defaultPosition;
    /**
     * The rect object to render 
    */
    SDL_Rect rect{};
    /**
     * The default velocity to be used to reset the paddle
    */
    Vec2 defaultVelocity;
    /**
     * Spritesheet of the Paddle class
    */
    SDL_Surface* spriteSheet;
    /**
     * Texture of the Paddle class
    */
    SDL_Texture* texture;
    /**
     * Holds the pointer to the renderer of the game loop
    */
    SDL_Renderer* renderer;
    /**
     * The instance of ResourceManager to load and unload resources. 
    */
    ResourceManager resourceManager = ResourceManager::getInstance();

};

#endif