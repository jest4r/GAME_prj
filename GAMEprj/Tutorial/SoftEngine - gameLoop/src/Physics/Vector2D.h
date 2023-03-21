#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class vector2D
{
    public:
        float X, Y;
    public:
        vector2D(float x=0, float y=0): X(x), Y(y) {}
    public:
        //addition +
        inline vector2D operator+(const vector2D& v2) const
        {
            return vector2D(X+v2.X, Y+v2.Y);
        }
        //subtraction-
        inline vector2D operator-(const vector2D& v2) const
        {
            return vector2D(X-v2.X, Y-v2.Y);
        }
        //multiplication*
        inline vector2D operator*(const float scalar) const
        {
            return vector2D(X*scalar, Y*scalar);
        }
        void Log(std::string mag = "")
        {
            std::cout << mag << "(X Y) = (" << X <<" " << Y <<  ")" <<std::endl;
        }
};

#endif // VECTOR2D_H
