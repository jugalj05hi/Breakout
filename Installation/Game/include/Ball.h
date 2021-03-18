#ifndef BALL
#define BALL
#include "Vec2.h"
#include "Contact.h"
#include <SDL2/SDL.h>
#include "ResourceManager.h"



const int BALL_WIDTH = 15;
const int BALL_HEIGHT = 15;
const float BALL_SPEED = 0.6f;
/**
 * Represents Ball in the game
 */
class Ball {

public:
    /**
     * The constructor of ball class that will take in the initial ball position, velocity along with window height and window width
     * and also the renderer
     * @param position Vec2 object that holds the intital x and y position
     * @param velocity Vec2 object that holds the inital velocity of the ball in terms of x and y coordinates
     * @param WINDOW_HEIGHT The height of the window rendered
     * @param WINDOW_WIDTH The width of the window rendered
     * @param ren The pointer to the renderer of the game loop
    */
    Ball(Vec2 position, Vec2 velocity, int WINDOW_HEIGHT, int WINDOW_WIDTH, SDL_Renderer* ren);
    /**
     * This method will draw/ render the ball to the screen
    */
    void Draw();
    /**
     * This method will update the position of the ball based on the time passed i.e. dt
     * @param dt The amount of time passed between each frame
    */
    void Update(float dt);
    /**
     * This method wil check for collision with paddle and change the ball's position and velocity accordingly
     * @param contact The type of contact made by the ball 
    */
    void CollideWithPaddle(Contact const& contact);
    /**
     * This method wil check for collision with the wall and change the ball's position and velocity accordingly
     * @param contact The type of contact made by the ball
    */
    void CollideWithWall(Contact const& contact);
    /**
     * This method wil check for collision with the wall and return which wall was hit
     * @return The type of contact made by the ball i.e. which wall was hit by the ball
    */
    Contact CheckWallCollision();
    /**
     * This method will reset the ball to it's original position
    */
    void Reset();
    /**
     * This method will change the Ball's x direction direction 
    */
    void FlipDirectionX();
    /**
     *This method will change the Ball's y direction direction 
    */
    void FlipDirectionY();
    /**
     * The resource manager instance to load and unload resources
    */
    ResourceManager resourceManager = ResourceManager::getInstance();
    /**
     * The Vec2 object to hold the position for the ball
    */
    Vec2 position;
    /**
     * The Vec2 object to hold the velocity of the ball
    */
    Vec2 velocity;
    /**
     * The Vec2 object to hold the initial position of the ball so we can use it to reset it 
    */
    Vec2 defaultPosition;
    /**
     * The Vec2 object to hold the initial velocity of the ball so we can use it to reset it
    */
    Vec2 defaultVelocity;
    /**
     * Variable to hold the height of the ball 
    */
    int height;
    /**
     * The variable to hold the width of the ball
    */
    int width;
    /**
     * The rect object to render the the ball on screnn
    */
    SDL_Rect rect{};
    /**
     * The height of the window 
    */
    int WINDOW_HEIGHT;
    /**
     * The width of the window 
    */
    int WINDOW_WIDTH;
    /**
     * The renderer object to store the pointer to the to actual renderer of the game loop
    */
    SDL_Renderer* renderer;
    /**
     * The spritesheet of the Ball
    */
    SDL_Surface* spriteSheet;
    /**
     * The texture of the ball
    */
    SDL_Texture* texture;
};

#endif