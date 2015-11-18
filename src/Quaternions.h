#ifndef QUATERNIONSS_H
#define QUATERNIONSS_H

//#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef struct Quaternion{
    double x;
    double y;
    double z;
    double w;
}quat;

quat Multqq(const quat q2, const quat q1);

quat Multqv(const quat q, const glm::vec3 v);

glm::vec3 rotateQuat(glm::vec3 vecToRotate, glm::vec3 axis, float angle);

glm::mat4x4 QuatToMatriz( glm::vec3 axis, float angle);

#endif // QUATERNIONSS_H
