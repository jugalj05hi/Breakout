#include "Brick.h"
// #include <SDL_image.h>
#include <map>
#include <string>
#include <memory>
#include <iterator>
#include <iostream>
#include <string.h>
#include <SDL2/SDL_image.h>

/**
* Creates an object of Brick class
*/
/**
* Creates an object of Brick class
*/
Brick::Brick() {
	x = 0;
	y = 0;
	width = 1;
	height = 1;
}

/**
* Destructor for Brick class
*/
Brick::~Brick() {

}

/**
* Method to initialize a brick by loading it's image
* @param xpo x-coordinate of top left most corner of the brick
* @param ypo y-coordinate of top left most corner of the brick
* @param ren object of SDL_Renderer, used to render brick on screen
*/
void Brick::init(int xpo, int ypo, SDL_Renderer* ren, int rowNumber) {
	x = xpo;
	y = ypo;
	width = BRICK_WIDTH;
	height = BRICK_HEIGHT;
	selected = false;
	hit = false;

	// ResourceManager r = ResourceManager::instance();
	// spriteSheet = r.load("Assets/images/brick_blue_small.png");
	switch (rowNumber) {
	case 0: spriteSheet = resourceManager.loadTexture("./assets/images/brick_red.png");
			break;
	case 1: spriteSheet = resourceManager.loadTexture("./assets/images/brick_yellow.png");
			break;
	case 2: spriteSheet = resourceManager.loadTexture("./assets/images/brick_green.png");
			break;
	case 3: spriteSheet = resourceManager.loadTexture("./assets/images/brick_blue.png");
			break;
	case 4: spriteSheet = resourceManager.loadTexture("./assets/images/brick_orange.png");
			break;
	case 5: spriteSheet = resourceManager.loadTexture("./assets/images/brick_dark_green.png");
			break;
	case 6: spriteSheet = resourceManager.loadTexture("./assets/images/brick_brown.png");
			break;
	default:
		spriteSheet = resourceManager.loadTexture("./assets/images/brick_grey.png");break;
	}
	
	if (spriteSheet == NULL) {
		SDL_Log("Failed to allocate surface");
	}
	else {
		//SDL_Log("Brick allocated at (%d,%d)",xpo,ypo);
		// Create a texture from our surface
		// Textures run faster and take advantage of hardware acceleration
		// SDL_SetColorKey(spriteSheet, SDL_TRUE, SDL_MapRGB(spriteSheet->format, 0, 0xFF, 0xFF));
		
		texture = SDL_CreateTextureFromSurface(ren, spriteSheet);
	}
}

/**
* Method used to render ball on screen
* @param ren object of SDL_Renderer, used to render brick on screen
*/
void Brick::draw(SDL_Renderer* ren) {
	Dest.x = x;
	Dest.y = y;
	Dest.w = 75;
	Dest.h = 50;

	Src.x = 140; //140
	Src.y = 180; //180
	Src.w = 234; //234
	Src.h = 100; //100

	if (!hit && selected)
	SDL_RenderCopy(ren, texture, NULL, &Dest);
}

/**
* Method used to update brick
*/
void Brick::update() {
	//hit = true;
}

/**
* Method used to update whether brick is selected.
*/
void Brick::setSelected() {
	selected = true;
}

/**
* Method used to get whether brick is selected.
*/
bool Brick::getSelected() {
	return selected;
}

bool Brick::isUpperSideOfLine(Point* corner1, Point* corner2, Point* ballCenter) {
	
	return ((corner2->x - corner1->x) * (ballCenter->y - corner1->y) - (corner2->y - corner1->y) * (ballCenter->x - corner1->x)) > 0;
}
int Brick::getContactEdge(Ball& ball, float& dt) {
	Point brickA, brickB, brickC, brickD, ballCenter;
	brickA.x = x;
	brickA.y = y;

	//upper right corner
	brickB.x = x + BRICK_WIDTH;
	brickB.y = y;

	// bottom right corner
	brickC.x = x + BRICK_WIDTH;
	brickC.y = y + BRICK_HEIGHT;

	// bottom left corner
	brickD.x = x;
	brickD.y = y + BRICK_HEIGHT;

	ballCenter.x = ball.position.x + (BALL_WIDTH / 2);
	ballCenter.y = ball.position.y + (BALL_HEIGHT / 2);

	bool isAboveAC = isUpperSideOfLine(&brickC, &brickA, &ballCenter);
	bool isAboveBD = isUpperSideOfLine(&brickB, &brickD, &ballCenter);

	if (isAboveAC)
	{
		if (isAboveBD)
		{
			//top edge has intersected
			ball.FlipDirectionY();
			// ball.Update(dt);
		
			return 1;
		}
		else
		{
			//right edge intersected
			ball.FlipDirectionX();
			// ball.Update(dt);
			return 2;
		}
	}
	else
	{
		if (isAboveBD)
		{
			//left edge has intersected
			ball.FlipDirectionX();
			// ball.Update(dt);
			return 4;
		}
		else
		{
			//bottom edge intersected
			ball.FlipDirectionY();
			// ball.Update(dt);
			return 3;
		}
	}
	
}

bool Brick::CollisionWithBall(Ball& ball, float& dt) {

	if (!hit && selected) {

		float brickX = x;
		float brickY = y;

		float ballCenterX = ball.position.x + 0.5f * ball.width;
		float ballCenterY = ball.position.y + 0.5f * ball.height;

		float brickCenterX = brickX + 0.5f * BRICK_WIDTH;
		float brickCenterY = brickY + 0.5f * BRICK_HEIGHT;

		if (x + BRICK_WIDTH >= ball.position.x
			&& x <= ball.position.x + BALL_WIDTH
			&& y + BRICK_HEIGHT >= ball.position.y
			&& y <= ball.position.y + BALL_HEIGHT)
		{

			hit = true;			

			getContactEdge(ball, dt);
			ball.Update(dt);
			
			return true;
		}
		
	}
	return false;
}


