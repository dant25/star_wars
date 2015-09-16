#include "ModelInstance.h"

ModelInstance::ModelInstance()  :
        asset(NULL),
        transform()
{

}

ModelInstance::ModelInstance(ModelAsset* model)
{
    this->asset = model;
}

ModelInstance::ModelInstance(ModelAsset* model, glm::mat4 mat)
{
    this->asset = model;
    this->transform = mat;
}

ModelInstance::~ModelInstance()
{
    //dtor
}
