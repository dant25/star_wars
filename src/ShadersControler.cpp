#include "ShadersControler.h"
#include<iostream>


ShadersControler::ShadersControler()
{
    this->gVAO = 0;
    this->gVBO = 0;
}

ShadersControler::~ShadersControler()
{
    //dtor
}

void ShadersControler::LoadShaders(std::string vertexShader, std::string fragmentShader) {
    std::vector<tdogl::Shader> shaders;
    shaders.push_back(tdogl::Shader::shaderFromFile(vertexShader, GL_VERTEX_SHADER));
    shaders.push_back(tdogl::Shader::shaderFromFile(fragmentShader, GL_FRAGMENT_SHADER));
    gProgram = new tdogl::Program(shaders);
}

tdogl::Texture* ShadersControler::LoadTexture(std::string texture, bool perspective, glm::vec2 SCREEN_SIZE) {
    tdogl::Bitmap bmp = tdogl::Bitmap::bitmapFromFile(texture);
    bmp.flipVertically();
    tdogl::Texture* gTexture = new tdogl::Texture(bmp);

    if(perspective == true)
    {
        gProgram->use();

        //set the "projection" uniform in the vertex shader, because it's not going to change
        glm::mat4 projection = glm::perspective((50.0f), SCREEN_SIZE.x/SCREEN_SIZE.y, 0.1f, 10.0f);
        gProgram->setUniform("projection", projection);

        //set the "camera" uniform in the vertex shader, because it's also not going to change
        glm::mat4 camera = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
        gProgram->setUniform("camera", camera);

        gProgram->stopUsing();
    }


    return gTexture;
}

void ShadersControler::LoadTriangle(GLfloat vertexData[], int tam) {
    // make and bind the VAO
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    // make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    glBufferData(GL_ARRAY_BUFFER, tam*sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(gProgram->attrib("vert"));
    glVertexAttribPointer(gProgram->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), NULL);

    // connect the RGB
    glEnableVertexAttribArray(gProgram->attrib("color"));
    glVertexAttribPointer(gProgram->attrib("color"), 3, GL_FLOAT, GL_TRUE,  6*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ShadersControler::LoadTexTriangle(GLfloat vertexData[], int tam) {
    // make and bind the VAO
    glGenVertexArrays(1, &gVAO);
    glBindVertexArray(gVAO);

    // make and bind the VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);

    glBufferData(GL_ARRAY_BUFFER, tam*sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(gProgram->attrib("vert"));
    glVertexAttribPointer(gProgram->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);

    // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
    glEnableVertexAttribArray(gProgram->attrib("vertTexCoord"));
    glVertexAttribPointer(gProgram->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

    // unbind the VAO
    glBindVertexArray(0);
}
