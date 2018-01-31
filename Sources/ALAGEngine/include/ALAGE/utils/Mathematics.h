#ifndef MATHEMATICS_H
#define MATHEMATICS_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "ALAGE/Types.h"

const GLfloat IdMat3X3[9] = {1,0,0,0,1,0,0,0,1};

float ComputeDotProduct(sf::Vector3f v, sf::Vector3f w);
float ComputeDotProduct(sf::Vector2f v, sf::Vector2f w);
float ComputeSquareDistance(sf::Vector3f v, sf::Vector3f w);
float ComputeSquareDistance(sf::Vector2f v, sf::Vector2f w);

sf::Vector2f Normalize(sf::Vector2f v);
sf::Vector3f Normalize(sf::Vector3f v);

void SfColorToGlColor(const sf::Color&, float glColor[4]);

namespace alag {

class Mat3x3
{
    public:
        Mat3x3();
        Mat3x3(sf::Vector3f u, sf::Vector3f v, sf::Vector3f w);
        Mat3x3( float, float, float,
                float, float, float,
                float, float, float);

        ~Mat3x3();

        Mat3x3 operator+(Mat3x3 const& m);
        Mat3x3 operator*(Mat3x3 const& m);
        Mat3x3 operator*(float const& k);
        sf::Vector3f operator*(sf::Vector3f const& v);
        sf::Vector2f operator*(sf::Vector2f const& v);

        GLfloat values[9];
};

}


#endif // MATHEMATICS_H