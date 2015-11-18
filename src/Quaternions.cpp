#include "Quaternions.h"

quat Multqq(const quat q2, const quat q1) {
    quat temp;
    temp.x = q2.y*q1.z - q2.z*q1.y + q2.w*q1.x + q2.x*q1.w;
    temp.y = q2.z*q1.x - q2.x*q1.z + q2.w*q1.y + q2.y*q1.w;
    temp.z = q2.x*q1.y - q2.y*q1.x + q2.w*q1.z + q2.z*q1.w;
    temp.w = q2.w*q1.w - q2.x*q1.x - q2.y*q1.y - q2.z*q1.z;
    return temp;
}


quat Multqv(const quat q, const glm::vec3 v) {
    quat res;
    res.w = -(q.x*v.x) - (q.y* v.y) - (q.z*v.z);
    res.x = (q.w*v.x) + (q.y*v.z) - (q.z*v.y);
    res.y = (q.w*v.y) + (q.z*v.x) - (q.x*v.z);
    res.z = (q.w*v.z) + (q.x*v.y) - (q.y*v.x);

    return res;
}


glm::vec3 rotateQuat(glm::vec3 vecToRotate, glm::vec3 axis, float angle){

    float radAngle = (angle * 0.5)* 3.1456/180;
    glm::normalize(axis);
    //Point3D::normalize(axis);

    quat q;
    q.x = axis.x * sin(radAngle);
    q.y = axis.y * sin(radAngle);
    q.z = axis.z * sin(radAngle);
    q.w = cos(radAngle);

    quat qConjugate;
    qConjugate.x = -q.x,
    qConjugate.y = -q.y,
    qConjugate.z = -q.z;
    qConjugate.w = q.w;


    quat qTemp, qRes;

    qTemp = Multqv(q, vecToRotate);
    qRes = Multqq(qTemp, qConjugate);

    glm::vec3 res(qRes.x,qRes.y,qRes.z);

    return res;
}

glm::mat4x4 QuatToMatriz( glm::vec3 axis, float angle)
{
    float radAngle = (angle * 0.5)* M_PI / 180.0;
    glm::normalize(axis);

    Quaternion q;
    q.x = axis.x * sin(radAngle);
    q.y = axis.y * sin(radAngle);
    q.z = axis.z * sin(radAngle);
    q.w = cos(radAngle);

    glm::mat4x4 matriz;
    matriz[0][0] = 1.0 - 2.0*q.y*q.y - 2.0*q.z*q.z;
    matriz[0][1] = 2.0*q.x*q.y - 2.0*q.z*q.w;
    matriz[0][2] = 2.0*q.x*q.z + 2.0*q.y*q.w;
    matriz[0][3] = 0.0;

    matriz[1][0] = 2.0*q.x*q.y + 2.0*q.z*q.w;
    matriz[1][1] = 1.0 - 2.0*q.x*q.x - 2.0*q.z*q.z;
    matriz[1][2] = 2.0*q.y*q.z - 2.0*q.x*q.w;
    matriz[1][3] = 0.0;

    matriz[2][0] = 2.0*q.x*q.z - 2.0*q.y*q.w;
    matriz[2][1] = 2.0*q.y*q.z + 2.0*q.x*q.w;
    matriz[2][2] = 1.0 - 2.0*q.x*q.x - 2.0*q.y*q.y;
    matriz[2][3] = 0.0;

    matriz[3][0] = 0.0;
    matriz[3][1] = 0.0;
    matriz[3][2] = 0.0;
    matriz[3][3] = 1.0;

    ///  1 - 2*qy2 - 2*qz2	2*qx*qy - 2*qz*qw	2*qx*qz + 2*qy*qw
    ///  2*qx*qy + 2*qz*qw	1 - 2*qx2 - 2*qz2	2*qy*qz - 2*qx*qw
    ///  2*qx*qz - 2*qy*qw	2*qy*qz + 2*qx*qw	1 - 2*qx2 - 2*qy2

    return matriz;
}
