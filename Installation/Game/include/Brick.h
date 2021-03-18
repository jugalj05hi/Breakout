#ifndef BRICK
#define BRICK
#include <SDL2/SDL.h>
#include "Ball.h"
#include "ResourceManager.h"

#define BRICK_WIDTH 75
#define BRICK_HEIGHT 25
#define SPACING 16

/**
 * Represents a single point in the 2D plane
 */
struct Point {
    float x, y;
};
/**
 *Represents the a single brick
*/
class Brick{

public:
    /**
    * Constructor of the Brick Class
    */
    Brick();

    /**
    * Destructor for Brick class
    */
    ~Brick();

    /**
    * Variable to keep state of whether brick was hit or not
    * Initialized to false by default
    */
    bool hit = false;

    /**
    * Method to initialize a brick by loading it's image
    * @param x x-coordinate of top left most corner of the brick
    * @param y y-coordinate of top left most corner of the brick
    * @param ren object of SDL_Renderer, used to render brick on screen
    * @param rowNumber The current row number to be rendered, helps in sorting out color
    */
    void init(int x, int y, SDL_Renderer* ren, int rowNumber);

    /**
    * Method used to render ball on screen
    * @param ren object of SDL_Renderer, used to render brick on screen
    */
    void draw(SDL_Renderer* ren);

    /**
    * Method used to update brick
    */
    void update();

    /**
    * Method used to update whether brick is selected.
    */
    void setSelected();

    /**
    * Method used to get whether brick is selected.
    */
    bool getSelected();

    /**
     * Method used to update brick and ball after a collision 
    */
    bool CollisionWithBall(Ball& ball, float& dt);
    /**
     * This method returns which edge of the brick is hit by the ball
    */
    int getContactEdge(Ball& ball, float& dt);
    /**
     * This Method is used determie if the ball hit the upper side of the brick
    */
    bool isUpperSideOfLine(Point*, Point*, Point*);

    

private:
    /**
    * Spritesheet of brick
    */
    SDL_Surface* spriteSheet;

    /**
    * Texture obtained from brick image
    */
    SDL_Texture* texture;

    /**
    * Destination rectangle where brick should be rendered on screen
    */
    SDL_Rect Dest;

    /**
    * Source rectangle from where brick is rendered on screen
    */
    SDL_Rect Src;

    /**
    * Boolean variable to keep state of whether brick is selected or not
    */
    bool selected;
    /**
     * The resource manager instance to load and unload resources
    */
    ResourceManager resourceManager = ResourceManager::getInstance();
    /**
     * To store the x coordinate of the brick 
    */
    int x;
    /**
     * To store the y coordinate of the brick
    */
    int y;
    /**
     * To store the width of the brick
    */
    int width;
    /**
     * To store the height of the brick
    */
    int height;
};


#endif