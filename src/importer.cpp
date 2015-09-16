#include "importer.h"

void ObjImporter::loadData(const char* &file_path)
{
/*
    ifstream file(file_path);
    if(!file){
        cout << "\nFile " << file_path << " doesn't exist!" << endl;
        exit(1);
    }

    int max_line_size = 2048;;
    char line_data[max_line_size];

    while(!file.eof())
    {
        file.getline(line_data, max_line_size);

        if(!strncmp(line_data, "v ", 2))
        {
            double x, y, z;
cout << "tam:" << sizeof(double) << endl;
            sscanf(line_data+2, "%lf %lf %lf", &x, &y, &z);
cout << "PONTOS " << x << " " << y << " " << z << endl;
            vertices.push_back(new Ponto(x, y, z));

            continue;
        }

        if(!strncmp(line_data, "vn ", 3))
        {
            string v1, v2, v3;

            sscanf(line_data+3, "%s %s %s", &v1, &v2, &v3);

            cout << "NORMAIS " << v1 << " " << v2 << " " << v3 << endl;

            //double x = atof (v1.c_str());
            //double y = atof (v2.c_str());
            //double z = atof (v3.c_str());

            cout << "NORMAIS " << v1 << " " << v2 << " " << v3 << endl;
            //cout << "NORMAIS = " << x << " " << y << " " << z << endl;



            //normals.push_back( Ponto(x, y, z) );

            continue;
        }

        if(!strncmp(line_data, "f ", 2))
        {
            Face face;
            Ponto normal;
            //sscanf(line_data+2, "%d %d %d", &face.x, &face.y, &face.z);
            sscanf(line_data+2, "%f %f %f %f %f %f ", &face.x, &normal.x, &face.y, &normal.y, &face.z, &normal.z);

            face.x--;
            face.y--;
            face.z--;
            normal.x--;
            normal.y--;
            normal.z--;

            faces.push_back(face);
            normals_faces.push_back(normal);

            continue;
        }
    }

    file.close();
*/



    std::ifstream file( file_path, std::ifstream::in);
    if( !file ){
        printf("Impossible to open the file !\n");
    }
    string tipo;

    while (file.good())
    {
        tipo = "_";
        file >> tipo;
        if (tipo == "v" ) {
            float v1, v2, v3;

            file >> v1;
            file >> v2;
            file >> v3;
//            float x = atof (v1.c_str());
//            float y = atof (v2.c_str());
//            float z = atof (v3.c_str());
//            x = (double)strtod( v1.c_str(), NULL );
//            y = (double)strtod( v2.c_str(), NULL );
//            z = (double)strtod( v3.c_str(), NULL );
//            cout << "PONTOS " << x << " " << y << " " << z << endl;
//            cout << "PONTOS == " << v1 << " " << v2 << " " << v3 << endl;

            vertices.push_back(new Ponto(v1, v2, v3));

            continue;
        }

        if (tipo == "vt" ) {        ///TEXTURAS
            float u, v;

            file >> u;
            file >> v;

            //cout << "Textura == " << u << " " << v << endl;

            texturas.push_back(Textura(u, v));

            continue;
        }

        if (tipo == "vn" ) {
            float x, y, z;

            file >> x;
            file >> y;
            file >> z;
//            double x = atof (v1.c_str());
//            double y = atof (v2.c_str());
//            double z = atof (v3.c_str());
            //cout << "NORMAIS " << x << " " << y << " " << z << endl;

            normals.push_back( Ponto(x, y, z) );

            continue;
        }

        if (tipo == "f" ) {
            Face face;
            Ponto normal;

            if( !this->haveTexture )
            {
                file >> face.x; file >> normal.x;
                file >> face.y; file >> normal.y;
                file >> face.z; file >> normal.z;
            }
            else
            {
                Ponto textura;
                file >> face.x; file >> textura.x; file >> normal.x;
                file >> face.y; file >> textura.y; file >> normal.y;
                file >> face.z; file >> textura.z; file >> normal.z;

                textura.x--;
                textura.y--;
                textura.z--;

                textura_faces.push_back(textura);
            }

            face.x--;
            face.y--;
            face.z--;
            normal.x--;
            normal.y--;
            normal.z--;

            //cout << "FACES = " << face.x << " " << face.y << " " << face.z << endl;
            //cout << "NORMS = " << normal.x << " " << normal.y << " " << normal.z << endl;

            faces.push_back(face);
            normals_faces.push_back(normal);

            continue;
        }
    }

    file.close();
}
