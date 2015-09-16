#ifndef MODELASSET_H
#define MODELASSET_H

#include "Program.h"
#include "Texture.h"

class ModelAsset
{
    public:
        ModelAsset();
        virtual ~ModelAsset();

        void LoadShaders(const std::string vertFilename, const std::string fragFilename);
        void LoadTexture(const char* filename);

        tdogl::Program* shaders;
        tdogl::Texture* texture;
        GLuint vbo;
        GLuint vao;
        GLenum drawType;
        GLint drawStart;
        GLint drawCount;
        GLfloat shininess;
        glm::vec3 specularColor;
    protected:
    private:
};

#endif // MODELASSET_H
