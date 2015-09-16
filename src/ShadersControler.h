#ifndef SHADERSCONTROLER_H
#define SHADERSCONTROLER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// tdogl classes
#include "Program.h"
#include "Texture.h"


class ShadersControler
{
    public:
        ShadersControler();
        virtual ~ShadersControler();

        GLuint get_gVAO() {return gVAO;};
        GLuint get_gVBO() {return gVBO;};
        tdogl::Program*  get_Program() {return gProgram;};

        void LoadShaders(std::string vertexShader, std::string fragmentShader);
        tdogl::Texture* LoadTexture(std::string texture, bool perspective, glm::vec2 SCREEN_SIZE);
        void LoadTriangle(GLfloat vertexData[], int tam);
        void LoadTexTriangle(GLfloat vertexData[], int tam);
    protected:
        std::vector<tdogl::Shader> shaders;
        tdogl::Program* gProgram;
        GLuint gVAO;
        GLuint gVBO;
    private:
};

#endif // SHADERSCONTROLER_H
