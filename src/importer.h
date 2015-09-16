#ifndef IMPORTER_H
#define IMPORTER_H

#include <fstream>
#include <iostream>

//#include <stdlib.h>
#include <cstdlib>
#include <cstring>
#include <glm/glm.hpp>

#include <vector>
#define Ponto glm::vec3
#define Face glm::vec3
#define Textura glm::vec2

using namespace std;

class ObjImporter
{
    public:
        ObjImporter(const char* file_path, bool haveTexture) { this->haveTexture=haveTexture; loadData(file_path);};
        ObjImporter() {};
        ~ObjImporter() {};

        void loadData(const char* &file_path);

        std::vector<Ponto*> vertices;
        std::vector<Textura> texturas;
        std::vector<Ponto> normals;
        std::vector<Face> faces;

        std::vector<Ponto> normals_faces;
        std::vector<Ponto> textura_faces;
        bool haveTexture;


};

#endif // IMPORTER_H
