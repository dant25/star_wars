#ifndef MODELINSTANCE_H
#define MODELINSTANCE_H

#include "ModelAsset.h"

class ModelInstance
{
    public:
        ModelInstance();
        ModelInstance(ModelAsset* model);
        ModelInstance(ModelAsset* model, glm::mat4 mat);
        virtual ~ModelInstance();

        void setTransform(glm::mat4 mat) {this->transform = mat;};

        ModelAsset* asset;
        glm::mat4 transform;
    protected:
    private:
};

#endif // MODELINSTANCE_H
