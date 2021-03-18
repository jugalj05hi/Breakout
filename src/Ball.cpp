#include "Ball.h"
#include <SDL2/SDL_image.h>

Ball::Ball(Vec2 position, Vec2 velocity, int WINDOW_HEIGHT, int WINDOW_WIDTH, SDL_Renderer* ren)
    : position(position), velocity(velocity), WINDOW_HEIGHT(WINDOW_HEIGHT), WINDOW_WIDTH(WINDOW_WIDTH)
    {   
        defaultPosition = position;
        defaultVelocity = velocity;
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);
        rect.w = BALL_WIDTH;
        rect.h = BALL_HEIGHT;
        height = BALL_HEIGHT;
        width = BALL_WIDTH;
        renderer = ren;

        spriteSheet = resourceManager.loadTexture("./assets/images/ball.png");
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

    void Ball::Draw()
    {
        rect.x = static_cast<int>(position.x);
        rect.y = static_cast<int>(position.y);

        // SDL_RenderFillRect(renderer, &rect);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
    void Ball::Update(float dt)
    {
        position += velocity * dt;
    }
    
    void Ball::CollideWithPaddle(Contact const& contact)
    {
        position.y += contact.penetration;
        velocity.y = -velocity.y;

        if (contact.type == CollisionType::Top)
        {
            velocity.x = -0.75f * BALL_SPEED;
            
        }
        else if (contact.type == CollisionType::Bottom)
        {
            velocity.x = 0.75f * BALL_SPEED;
            
        }
    }
    
    Contact Ball::CheckWallCollision()
    {
        float ballLeft = position.x;
        float ballRight = position.x + BALL_WIDTH;
        float ballTop = position.y;
        float ballBottom = position.y + BALL_HEIGHT;

        Contact contact{};

        if (ballLeft < 0.0f)
        {
            contact.type = CollisionType::Left;
            contact.penetration = -ballLeft;
        }
        else if (ballRight > WINDOW_WIDTH)
        {
            contact.type = CollisionType::Right;
            contact.penetration = WINDOW_WIDTH - ballRight;
        }
        else if (ballTop < 0.0f)
        {
            contact.type = CollisionType::Top;
            contact.penetration = -ballTop;
        }
        else if (ballBottom > WINDOW_HEIGHT)
        {
            contact.type = CollisionType::Bottom;
            contact.penetration = WINDOW_HEIGHT - ballBottom;
        }

        return contact;
    }
    
    void Ball::CollideWithWall(Contact const& contact)
    {
        if ((contact.type == CollisionType::Top))
        {
            // position.x += contact.penetration;
            // velocity.x = -velocity.x;
            position.y += contact.penetration;
            velocity.y = -velocity.y;
        } 
        else if ((contact.type == CollisionType::Left)
            || (contact.type == CollisionType::Right))
        {
            position.x += contact.penetration;
            velocity.x = -velocity.x;    
        }
    }
    
    void Ball::Reset(){
        position = defaultPosition;
        velocity = defaultVelocity;
        rect.x = static_cast<int>(defaultPosition.x);
        rect.y = static_cast<int>(defaultPosition.y);
        rect.w = BALL_WIDTH;
        rect.h = BALL_HEIGHT;
        height = BALL_HEIGHT;
        width = BALL_WIDTH;
    }

    void Ball::FlipDirectionX() {

        velocity.x = -velocity.x;
    }

    void Ball::FlipDirectionY() {

        velocity.y = -velocity.y;
    }




