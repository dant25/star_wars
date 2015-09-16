#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>

class Light
{
    public:
        Light();
        virtual ~Light();

        glm::vec4 position;
        glm::vec3 intensities; //a.k.a. the color of the light
        float attenuation;
        float ambientCoefficient;
        float coneAngle;
        glm::vec3 coneDirection;
};

#endif // LIGHT_H


