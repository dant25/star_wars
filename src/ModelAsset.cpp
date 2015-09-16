#include "ModelAsset.h"

ModelAsset::ModelAsset() :
        shaders(NULL),
        texture(NULL),
        vbo(0),
        vao(0),
        drawType(GL_TRIANGLES),
        drawStart(0),
        drawCount(0),
        shininess(0.0f),
        specularColor(1.0f, 1.0f, 1.0f)
{
    //ctor
}

ModelAsset::~ModelAsset()
{
    //dtor
}

void ModelAsset::LoadShaders(const std::string vertFilename, const std::string fragFilename) {
    std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(vertFilename, GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(fragFilename, GL_FRAGMENT_SHADER));
    this->shaders = new tdogl::Program(shaders);
}

void ModelAsset::LoadTexture(const char* filename) {
    tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(filename);
    bmp.flipVertically();
    this->texture = new tdogl::Texture(bmp);
}
