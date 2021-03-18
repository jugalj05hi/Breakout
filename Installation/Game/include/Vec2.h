#ifndef VEC2
#define VEC2
/**
 *Vec2 will abstract X&Y position for ball and paddle. 
*/
class Vec2 {

public:
    /**
     * Default constructor for Vec2() class
     */
    Vec2();
    /**
    *Overloaded constructor that takes in two arguments
    * @param x The x Coordinate
    * @param y The Y Coordinate
    */
    Vec2(float x, float y);
    /**
    * This method is overloading the + operator to make it easier for us to calculate in certain scenario
    * @param rhs The right hand side of the calculation
    * @return returns a Vec2 object
    */
    Vec2 operator+(Vec2 const& rhs);
    /**
    * This method is overloading the += operator to make it easier for us to calculate in certain scenario
    * @param rhs The right hand side of the calculation
    * @return returns a reference to a Vec2 object
    */
    Vec2& operator+= (Vec2 const& rhs);
    /**
    * This method is overloading the * operator to make it easier for us to calculate in certain scenario
    * @param rhs The right hand side of the calculation
    * @return returns a Vec2 object
    */
    Vec2 operator*(float);
    /**
     *The X coordinate
    */
    float x;
    /**
     * The Y coordinate
    */
    float y;
};

#endif