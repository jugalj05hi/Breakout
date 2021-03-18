#ifndef CONTACT
#define CONTACT

/**
 * Represents the type of Collision between Paddle, Ball and Walls. 
 */

enum class CollisionType
{
    None,
    Top,
    Middle,
    Bottom,
    Left,
    Right
};
/**
 * Represents the contact when the ball hits paddle or wall
 */
struct Contact
{
    CollisionType type;
    float penetration;
};


#endif