#include "Paddle.h"
#include <SDL2/SDL_image.h>
Paddle::Paddle(Vec2 position, Vec2 velocity, SDL_Renderer* renderer)
    : position(position), velocity(velocity), renderer(renderer)
{
    defaultPosition = position;
    defaultVelocity = velocity;
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = PADDLE_WIDTH;
    rect.h = PADDLE_HEIGHT;

    spriteSheet = resourceManager.loadTexture("./assets/images/paddle.png");
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

void Paddle::Draw()
{
    rect.x = static_cast<int>(position.x);

    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Paddle::Update(float dt, int WINDOW_WIDTH)
{
    position += velocity * dt;

    if (position.x < 0)
    {
        // Restrict to top of the screen
        position.x = 0;
    }
    else if (position.x > (WINDOW_WIDTH - PADDLE_WIDTH))
    {
        // Restrict to bottom of the screen
        position.x = WINDOW_WIDTH - PADDLE_WIDTH;
    }
}

Contact Paddle::checkCollision(Ball const& ball) {
    
    float ballLeft = ball.position.y;
    float ballRight = ball.position.y + BALL_WIDTH;
    float ballTop = ball.position.x;
    float ballBottom = ball.position.x + BALL_HEIGHT;
    
    // float ballLeft = ball.position.y;
    // float ballRight = ball.position.y + BALL_HEIGHT;
    // float ballTop = ball.position.x + BALL_WIDTH;
    // float ballBottom = ball.position.x;


    float paddleLeft = position.y;
    float paddleRight = position.y + PADDLE_HEIGHT;
    float paddleTop = position.x;
    float paddleBottom = position.x + PADDLE_WIDTH;
    
    // float paddleLeft = position.y;
    // float paddleRight = position.y + PADDLE_HEIGHT;
    // float paddleTop = position.x + PADDLE_WIDTH;
    // float paddleBottom = position.x;
    
    Contact contact{};

    if (ballLeft >= paddleRight)
    {
        return contact;
    }

    if (ballRight <= paddleLeft)
    {
        return contact;
    }

    if (ballTop >= paddleBottom)
    {
        return contact;
    }

    if (ballBottom <= paddleTop)
    {
        return contact;
    }
    
    float paddleRangeUpper = paddleBottom - (2.0f * PADDLE_WIDTH / 3.0f);
    float paddleRangeMiddle = paddleBottom - (PADDLE_WIDTH / 3.0f);

    if (ball.velocity.y < 0)
    {
        // Left paddle
        contact.penetration = paddleRight - ballLeft;
    }
    else if (ball.velocity.y > 0)
    {
        // Right paddle
        contact.penetration = paddleLeft - ballRight;
    }

    if ((ballBottom > paddleTop)
        && (ballBottom < paddleRangeUpper))
    {
        contact.type = CollisionType::Top;
    }
    else if ((ballBottom > paddleRangeUpper)
        && (ballBottom < paddleRangeMiddle))
    {
        contact.type = CollisionType::Middle;
    }
    else
    {
        contact.type = CollisionType::Bottom;
    }

    return contact;

}

void Paddle::Reset(){
    position = defaultPosition;
    velocity = defaultVelocity;
    rect.x = static_cast<int>(position.x);
    rect.y = static_cast<int>(position.y);
    rect.w = PADDLE_WIDTH;
    rect.h = PADDLE_HEIGHT;
    
}