#include "GLWidget.h"

#include <QtGui>
#include <iostream>
//#include <GL/glu.h>

#include <QKeyEvent>
#include <QLabel>
#include <QtGui/qgridlayout.h>
#include <QGridLayout>
#include <sys/time.h>

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::DoubleBuffer  | QGL::SampleBuffers | QGL::StencilBuffer), parent)
{
    Phonon::MediaSource fundo = Phonon::MediaSource(":/sounds/resources/Star Wars Battle Theme FULL.mp3");
    Phonon::MediaSource tiros = Phonon::MediaSource(":/sounds/resources/Space Battle Background.mp3");
    Phonon::MediaSource xWingSound = Phonon::MediaSource(":/sounds/resources/X Wing Ambient Engine Sound.mp3");
    Phonon::MediaSource tieFighterSound = Phonon::MediaSource(":/sounds/resources/TIE Fighter roar.mp3");
    Phonon::MediaSource tieFighterEngine = Phonon::MediaSource(":/sounds/resources/TIE Fighter Engine.mp3");
    Phonon::MediaSource empireAlertSound = Phonon::MediaSource(":/sounds/resources/Imperial Alert - Siren Sound.mp3");
    Phonon::MediaSource laserSound = Phonon::MediaSource(":/sounds/resources/X wing blaster sound.mp3");


    music = Phonon::createPlayer(Phonon::MusicCategory, fundo);

    war = Phonon::createPlayer(Phonon::MusicCategory, tiros);

    xWing_Sound = Phonon::createPlayer(Phonon::MusicCategory, xWingSound);

    tieFighter_Sound = Phonon::createPlayer(Phonon::MusicCategory, tieFighterSound);

    empire_Alert_Sound = Phonon::createPlayer(Phonon::MusicCategory, empireAlertSound);

    tieFighter_Engine = Phonon::createPlayer(Phonon::MusicCategory, tieFighterEngine);

    laser_Sound = Phonon::createPlayer(Phonon::MusicCategory, laserSound);

    // setup gCamera
    gCamera.setPosition(glm::vec3(9,20,108));
    gCamera.setVerticalAngle(0.0);
    gCamera.setHorizontalAngle(0.0);
    gCamera.setViewportAspectRatio(screen_size.x / screen_size.y);
    gCamera.setNearAndFarPlanes(0.1f, 800.0f);
    gCamera.lookAt(glm::vec3(10,7,0));
    //gCamera.setHorizontalAngle(0);
    //gCamera.setHorizontalAngle(0);


    // setup lights
    Light spotlight;
    spotlight.position = glm::vec4(-4,0,10,1);
    spotlight.intensities = glm::vec3(1,1,1); //strong white light
    spotlight.attenuation = 0.1f;
    spotlight.ambientCoefficient = 0.0f; //no ambient light
    spotlight.coneAngle = 15.0f;
    spotlight.coneDirection = glm::vec3(0,0,-1);

    Light directionalLight;
    directionalLight.position = glm::vec4(150, 80, 30, 0); //w == 0 indications a directional light
    directionalLight.attenuation = 0.1f;
    directionalLight.intensities = glm::vec3(0.9, 0.9, 1.0);
    directionalLight.ambientCoefficient = 0.3;

    gLights.push_back(spotlight);
    gLights.push_back(directionalLight);

    setFocus();
    //setMouseTracking(false);

    rotLua = 0.0;
    fix_cam = false;

    srand( time(NULL) );
}

GLWidget::~GLWidget()
{
    delete music;
    delete war;
    delete xWing_Sound;
    delete tieFighter_Sound;
    delete tieFighter_Engine;
    delete empire_Alert_Sound;
}

// convenience function that returns a translation matrix
glm::mat4 translate(GLfloat x, GLfloat y, GLfloat z) {
    return glm::translate(glm::mat4(), glm::vec3(x,y,z));
}

// convenience function that returns a scaling matrixa
glm::mat4 scale(GLfloat x, GLfloat y, GLfloat z) {
    return glm::scale(glm::mat4(), glm::vec3(x,y,z));
}

// convenience function that returns a scaling matrix
glm::mat4 rotate(GLfloat x, GLfloat y, GLfloat z, GLfloat ang) {
    return glm::rotate(glm::mat4(), (ang), glm::vec3(x,y,z));
}

template <typename T>
void SetLightUniform(tdogl::Program* shaders, const char* propertyName, size_t lightIndex, const T& value) {
    std::ostringstream ss;
    ss << "allLights[" << lightIndex << "]." << propertyName;
    std::string uniformName = ss.str();

    shaders->setUniform(uniformName.c_str(), value);
}

void GLWidget::initializeGL()
{
    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");

    // GLEW throws some errors, so discard all the errors so far
    while(glGetError() != GL_NO_ERROR) {}

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // make sure OpenGL version 3.2 API is available
    if(!GLEW_VERSION_3_2)
        throw std::runtime_error("OpenGL 3.2 API is not available.");

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    LoadOBJ( "../../resources/Nave.obj", "../../resources/silver.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 100.0, glm::vec3(0.5f, 0.5f, 0.5f), true );

    LoadOBJ( "../../resources/Rebelde.obj", "../../resources/metal2.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 800.0, glm::vec3(1.0f, 1.0f, 1.0f), true );

    LoadOBJ( "../../resources/Tie.obj", "../../resources/dark.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 1.0, glm::vec3(1.0f, 1.0f, 1.0f), true );

    LoadOBJ( "../../resources/Xwing.obj", "../../resources/xwing.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 500.0, glm::vec3(0.5f, 0.5f, 0.5f), true );

    LoadOBJ( "../../resources/DeathStar.obj", "../../resources/metal5.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 500.0, glm::vec3(0.5f, 0.5, 0.5f), true );

    LoadOBJ( "../../resources/Executor.obj", "../../resources/executor.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 100.0, glm::vec3(1.0f, 1.0f, 1.0f), true );

    LoadOBJ( "../../resources/Frigate.obj", "../../resources/metal5.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 200.0, glm::vec3(0.6f, 0.6f, 0.6f), true );

    LoadOBJ( "../../resources/Lua.obj", "../../resources/terra.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 800.0, glm::vec3(0.3f, 0.3f, 0.3f), true );

    LoadOBJ( "../../resources/Globo.obj", "../../resources/galaxia.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 100.0, glm::vec3(1.0f, 1.0f, 1.0f), true );

    LoadOBJ( "../../resources/Laser.obj", "../../resources/laser_emp.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 100.0, glm::vec3(1.0f, 1.0f, 1.0f), true );

    LoadOBJ( "../../resources/Laser.obj", "../../resources/laser_rebel.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 100.0, glm::vec3(1.0f, 1.0f, 1.0f), true );

    LoadOBJ( "../../resources/Falcon.obj", "../../resources/falcplan.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 100.0, glm::vec3(0.7f, 0.7f, 0.7f), true );

    LoadOBJ( "../../resources/Lua.obj", "../../resources/lua.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 800.0, glm::vec3(0.3f, 0.3f, 0.3f), true );

    LoadOBJ( "../../resources/SuperTie.obj", "../../resources/vaderTex.png", "../../resources/vertex-shader.txt", "../../resources/fragment-shader.txt",
             0, 800.0, glm::vec3(0.3f, 0.3f, 0.3f), true );

    CreateInstances();

    CalculaLaser();


    //inicialização QTIMER

    simTimer = new QTimer(this);
    connect(simTimer, SIGNAL(timeout()), this, SLOT(simStep()));
    simTimer->start(0);
    simTimer->setInterval(0);

}

void GLWidget::paintGL()
{
    // clear everything
    glClearColor(0, 0, 0, 1); // black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render all the instances
    std::list<ModelInstance>::const_iterator it;
    for(it = gInstances.begin(); it != gInstances.end(); ++it)
    {
        RenderInstance(*it);
    }

    std::list<Raio>::const_iterator iter;
    for(iter = lasers.begin(); iter != lasers.end(); ++iter)
    {
        RenderInstance( (*iter).laser );
    }

    for(it = imp.begin(); it != imp.end(); ++it)
    {
        RenderInstance( (*it) );
    }

    for(it = reb.begin(); it != reb.end(); ++it)
    {
        RenderInstance( (*it) );
    }


    ///Nave do Dart Vader
    if(!fix_cam)
    {
            float angF = ( glm::acos( glm::dot({0.0, 0.0, -1.0}, gCamera.forward() ) ) );
            float angR = ( glm::acos( glm::dot({0.0, 1.0, 0.0}, gCamera.up() ) ) );

            if(gCamera.forward().x > 0.00001)
                angF = -angF;

            if(gCamera.up().z < 0.00001)
                angR = -angR;

            if(gCamera.forward().z > 0.00001)
                angR = -angR;

            vader.transform =  translate(gCamera.position().x + gCamera.forward().x*5,
                                         gCamera.position().y + gCamera.forward().y*5 - 1,
                                         gCamera.position().z + gCamera.forward().z*5 )
                                * scale(2.5, 2.5, 2.5)
                                * rotate( 0, 1, 0, angF)
                                * rotate( 1, 0, 0, angR)
                                * rotate(0.0, 1.0, 0.0, M_PI);

    }

    RenderInstance( vader );
}

void GLWidget::simStep()
{
    double ti,tf,tempo; // ti = tempo inicial // tf = tempo final
    ti = tf = tempo = 0;
    timeval tempo_inicio,tempo_fim;
    gettimeofday(&tempo_inicio,NULL);

    ///ATUALIZANDO OS LASERS
    AtualizaLaser();


    ///ROTACIONANDO OBJETOS
    rotLua += 0.005;

    if(rotLua > 2.0*M_PI)
        rotLua = 0.00;

    rotNave += 0.0025;
    if(rotNave > 2.0*M_PI)
        rotNave = 0.00;

    gInstances.front().transform =  translate(100,0,-90) * scale(20.0, 20.0, 20.0) * rotate(0.0, 1.0, 0.0, rotLua);

    float count = 0.0;
    std::list<ModelInstance>::iterator it;
    for(it = imp.begin(); it != imp.end(); ++it)
    {
        if( (int)count % 2 == 0)
            (*it).transform = translate(-40.0 - count,0.0 - count,-110 - count) * rotate(0.0, 0.0, 1.0, rotNave) * rotate(0.5, 1.0, 0.5, 2*rotLua) * translate(-90.0 - count,0 - count,10 - count)
                                * scale(1.5, 1.5, 1.5) * rotate(0.0, 0.0, 1.0, 10*rotLua);
        else
            (*it).transform = translate(-40 - count/2.0,0 - count/2.0,-110 - count/2.0) * rotate(0.0, 0.0, 1.0, rotNave) * rotate(0.5, 1.0, 0.5, 2*rotLua) * translate(-90.0 - count/2.0,0 - count/2.0,10 - count/2.0)
                                * scale(1.5, 1.5, 1.5) * rotate(0.0, 0.0, 1.0, 10*rotLua);
        count += 5.0;
    }

    count = 0.0;
    for(it = reb.begin(); it != reb.end(); ++it)
    {
//        (*it).transform = translate(-40 - count,0 - count,-110 - count) * rotate(0.0, 0.0, 1.0, rotNave) * rotate(0.0, 1.0, 0.0, 2*rotLua) * translate(-90 - count,0 - count,0 - count)
//                                * scale(0.8, 0.8, 0.8) * rotate(0.0, 1.0, 0.0, 3.1415) * rotate(0.0, 0.0, 1.0, rotNave);
        if( (int)count%2 == 0 )
            (*it).transform = translate(-40 - count,0 - count,-110 - count) * rotate(0.0, 0.0, 1.0, rotNave) * rotate(0.5, 1.0, 0.5, 2*rotLua) * translate(-90.0 - count,0 - count,0 - count)
                                * scale(0.8, 0.8, 0.8) * rotate(0.0, 1.0, 0.0, 3.1415) * rotate(0.0, 0.0, 1.0, rotNave);
        else
        {
            (*it).transform = translate(-40 - count/2.0,0 - count/2.0,-110 - count/2.0) * rotate(0.0, 0.0, 1.0, rotNave) * rotate(0.5, 1.0, 0.5, 2*rotLua) * translate(-90.0 - count/2.0,0 - count/2.0,0 - count/2.0)
                                * scale(0.8, 0.8, 0.8) * rotate(0.0, 1.0, 0.0, 3.1415) * rotate(0.0, 0.0, 1.0, rotNave);
        }

        count += 5.0;
    }

//std::cout << "POS: " << gCamera.position().x << " " << gCamera.position().y << " " << gCamera.position().z << std::endl;
//std::cout << "LOOK AT: " << gCamera.forward().x << " " << gCamera.forward().y << " " << gCamera.forward().z << std::endl;


    ///REPOSICIONANDO A CAMERA
    if(fix_cam)
    {
        double t = 1.5;
        glm::vec3 pos(t*( reb.front().transform[3][0] - imp.front().transform[3][0] ),
                3+t*( reb.front().transform[3][1] - imp.front().transform[3][1] ),
                t*( reb.front().transform[3][2] - imp.front().transform[3][2] ) );

//gCamera.setPosition( glm::vec3(reb.front().transform[3][0] + pos.x, reb.front().transform[3][1] + pos.y, reb.front().transform[3][2]) + pos.z);

        gCamera.setPosition( glm::vec3(reb.front().transform[3][0], reb.front().transform[3][1], reb.front().transform[3][2]) + pos );
        gCamera.lookAt( glm::vec3(imp.front().transform[3][0], imp.front().transform[3][1], imp.front().transform[3][2]) );
    }


    ///SONS DA ANIMAÇÂO
    {
        glm::vec3 posReb = glm::vec3(reb.front().transform[3][0], reb.front().transform[3][1], reb.front().transform[3][2]);
        glm::vec3 posEmp = glm::vec3(imp.back().transform[3][0], imp.back().transform[3][1], imp.back().transform[3][2]);

        if( glm::abs(posEmp.x - posReb.x) < 8.0 && glm::abs(posEmp.y - posReb.y) < 8.0 && glm::abs(posEmp.z - posReb.z) < 8.0 &&
            fix_cam )
        {
            tieFighter_Sound->play();
        }

        glm::vec3 posVader = glm::vec3(vader.transform[3][0], vader.transform[3][1], vader.transform[3][2]);
        for(it = reb.begin(); it != reb.end(); ++it)
        {
            glm::vec3 posReb = glm::vec3((*it).transform[3][0], (*it).transform[3][1], (*it).transform[3][2]);

            if( glm::abs(posVader.x - posReb.x) < 8.0 && glm::abs(posVader.y - posReb.y) < 8.0 && glm::abs(posVader.z - posReb.z) < 8.0 &&
                !fix_cam )
            {
                tieFighter_Sound->play();
            }
        }
        for(it = imp.begin(); it != imp.end(); ++it)
        {
            glm::vec3 posImp = glm::vec3((*it).transform[3][0], (*it).transform[3][1], (*it).transform[3][2]);

            if( glm::abs(posVader.x - posImp.x) < 8.0 && glm::abs(posVader.y - posImp.y) < 8.0 && glm::abs(posVader.z - posImp.z) < 8.0 &&
                !fix_cam )
            {
                tieFighter_Sound->play();
            }
        }


        glm::vec3 posExecutor = glm::vec3(imperio.back().transform[3][0], imperio.back().transform[3][1], imperio.back().transform[3][2]);
        glm::vec3 distan = posExecutor - gCamera.position();

        if( glm::abs(distan.x) < 60.0 && glm::abs(distan.y) < 60.0 && glm::abs(distan.z) < 60.0 )
            empire_Alert_Sound->play();
        else
            empire_Alert_Sound->stop();

        if(fix_cam)
            xWing_Sound->play();
        //else
            //tieFighter_Engine->play();

        war->play();
        music->play();
    }


    gettimeofday(&tempo_fim,NULL);
    tf = (double)tempo_fim.tv_usec + ((double)tempo_fim.tv_sec * (1000000.0));
    ti = (double)tempo_inicio.tv_usec + ((double)tempo_inicio.tv_sec * (1000000.0));
    tempo = (tf - ti) / 1000;
    //printf("Tempo gasto em milissegundos para desenhar %.3f\n",tempo);

    double tempoFalta = (33.33 - tempo);
    if (tempoFalta>0)
      simTimer->setInterval(tempoFalta);
}

void GLWidget::RenderInstance(const ModelInstance& inst) {
    if (inst.asset == NULL )
        return;

    ModelAsset* asset = inst.asset;
    tdogl::Program* shaders = asset->shaders;

    //bind the shaders
    shaders->use();

    glm::mat3 mat_normais = glm::transpose( glm::inverse(  glm::mat3(inst.transform) ) );


    //set the shader uniforms
    shaders->setUniform("camera", gCamera.matrix());
    shaders->setUniform("model", inst.transform);
    shaders->setUniform("matNormalTransf", mat_normais);
    shaders->setUniform("materialTex", 0); //set to 0 because the texture will be bound to GL_TEXTURE0
    shaders->setUniform("materialShininess", asset->shininess);
    shaders->setUniform("materialSpecularColor", asset->specularColor);
    shaders->setUniform("cameraPosition", gCamera.position());
    shaders->setUniform("numLights", (int)gLights.size());

    for(size_t i = 0; i < gLights.size(); ++i){
        SetLightUniform(shaders, "position", i, gLights[i].position);
        SetLightUniform(shaders, "intensities", i, gLights[i].intensities);
        SetLightUniform(shaders, "attenuation", i, gLights[i].attenuation);
        SetLightUniform(shaders, "ambientCoefficient", i, gLights[i].ambientCoefficient);
        SetLightUniform(shaders, "coneAngle", i, gLights[i].coneAngle);
        SetLightUniform(shaders, "coneDirection", i, gLights[i].coneDirection);
    }

    //bind the texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, asset->texture->object());

    //bind VAO and draw
    glBindVertexArray(asset->vao);
    glDrawArrays(asset->drawType, asset->drawStart, asset->drawCount);

    //unbind everything
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    shaders->stopUsing();

    GLenum err = GL_NO_ERROR;
    while((err = glGetError()) != GL_NO_ERROR)
    {
      //Process/log the error.
      std::cout << "ERRRORR" << std::endl;
    }
}

void GLWidget::LoadOBJ(const char*  arquivo, const char*  textura, const char*  vertex_shader, const char*  fragment_shader,
                         int drawStart, float shininess, glm::vec3 specularColor, bool haveTexture)
{
    ModelAsset modelo;
    ObjImporter leitor = ObjImporter(arquivo, haveTexture);


    // set all the elements of modelo
    modelo.LoadShaders(vertex_shader, fragment_shader);
    modelo.drawType = GL_TRIANGLES;
    modelo.drawStart = drawStart;
    modelo.drawCount = leitor.faces.size() * 3;
    modelo.LoadTexture(textura);
    modelo.shininess = shininess;
    modelo.specularColor =  glm::vec3(specularColor);
    glGenBuffers(1, &modelo.vbo);
    glGenVertexArrays(1, &modelo.vao);


    // bind the VAO
    glBindVertexArray(modelo.vao);

    // bind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, modelo.vbo);

    // Make a cube out of triangles (two triangles per side)
    GLfloat vertexData[ leitor.faces.size() * 3 * 8 ];

    int pos = 0;
    for(unsigned int i=0; i<leitor.faces.size(); i++)
    {
        vertexData[pos++] = ( leitor.vertices[ leitor.faces[i].x ]->x );
        vertexData[pos++] = ( leitor.vertices[ leitor.faces[i].x ]->y );
        vertexData[pos++] = ( leitor.vertices[ leitor.faces[i].x ]->z );

//haveTexture=false;
        if( haveTexture )
        {
            vertexData[pos++] = ( leitor.texturas[ leitor.textura_faces[i].x ].x );
            vertexData[pos++] = ( leitor.texturas[ leitor.textura_faces[i].x ].y );
        } else
        {
            vertexData[pos++] = ( 0.0f );
            vertexData[pos++] = ( 0.0f );
        }

        vertexData[pos++] = ( leitor.normals[ leitor.normals_faces[i].x ].x );
        vertexData[pos++] = ( leitor.normals[ leitor.normals_faces[i].x ].y );
        vertexData[pos++] = ( leitor.normals[ leitor.normals_faces[i].x ].z );
//---------------------
        vertexData[pos++] = ( leitor.vertices[ leitor.faces[i].y ]->x );
        vertexData[pos++] = ( leitor.vertices[ leitor.faces[i].y ]->y );
        vertexData[pos++] = ( leitor.vertices[ leitor.faces[i].y ]->z );

        if( haveTexture )
        {
            vertexData[pos++] = ( leitor.texturas[ leitor.textura_faces[i].y ].x );
            vertexData[pos++] = ( leitor.texturas[ leitor.textura_faces[i].y ].y );
        } else
        {
            vertexData[pos++] = ( 1.0f );
            vertexData[pos++] = ( 0.0f );
        }

        vertexData[pos++] = ( leitor.normals[ leitor.normals_faces[i].y ].x );
        vertexData[pos++] = ( leitor.normals[ leitor.normals_faces[i].y ].y );
        vertexData[pos++] = ( leitor.normals[ leitor.normals_faces[i].y ].z );
//---------------------
        vertexData[pos++] = ( leitor.vertices[ leitor.faces[i].z ]->x );
        vertexData[pos++] = ( leitor.vertices[ leitor.faces[i].z ]->y );
        vertexData[pos++] = ( leitor.vertices[ leitor.faces[i].z ]->z );

        if( haveTexture )
        {
            vertexData[pos++] = ( leitor.texturas[ leitor.textura_faces[i].z ].x );
            vertexData[pos++] = ( leitor.texturas[ leitor.textura_faces[i].z ].y );
        } else
        {
            vertexData[pos++] = ( 0.5f );
            vertexData[pos++] = ( 1.0f );
        }

        vertexData[pos++] = ( leitor.normals[ leitor.normals_faces[i].z ].x );
        vertexData[pos++] = ( leitor.normals[ leitor.normals_faces[i].z ].y );
        vertexData[pos++] = ( leitor.normals[ leitor.normals_faces[i].z ].z );
    }

    glBufferData(GL_ARRAY_BUFFER, leitor.faces.size() * 3 * 8 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    // connect the xyz to the "vert" attribute of the vertex shader
    glEnableVertexAttribArray(modelo.shaders->attrib("vert"));
    glVertexAttribPointer(modelo.shaders->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), NULL);

    // connect the uv coords to the "vertTexCoord" attribute of the vertex shader
    glEnableVertexAttribArray(modelo.shaders->attrib("vertTexCoord"));
    glVertexAttribPointer(modelo.shaders->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  8*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

    // connect the normal to the "vertNormal" attribute of the vertex shader
    glEnableVertexAttribArray(modelo.shaders->attrib("vertNormal"));
    glVertexAttribPointer(modelo.shaders->attrib("vertNormal"), 3, GL_FLOAT, GL_TRUE,  8*sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));

    // unbind the VBO and VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    modelos.push_back(modelo);
}

void GLWidget::CreateInstances() {

    ModelInstance terra;
    terra.asset = &this->modelos[7];
    terra.transform =  translate(100,0,-90) * scale(20.0, 20.0, 20.0);// * rotate(0,1,0, 135) ;
    gInstances.push_back(terra);

    ModelInstance lua;
    lua.asset = &this->modelos[12];
    lua.transform =  translate(100,40,-90) * scale(3.0, 3.0, 3.0);// * rotate(0,1,0, 135) ;
    gInstances.push_back(lua);

    ModelInstance blobo;
    blobo.asset = &this->modelos[8];
    blobo.transform =  translate(0,0,0) * scale(300.0, 300.0, 300.0) * rotate(0,1,0, 1.8) ;
    gInstances.push_back(blobo);

    ModelInstance deathStar;
    deathStar.asset = &this->modelos[4];
    deathStar.transform =  translate(-40,0,-110) * scale(14.0, 14.0, 14.0) * rotate(0,1,0, 0.3) ;
    gInstances.push_back(deathStar);

    ModelInstance crusader01;
    crusader01.asset = &this->modelos[0];
    crusader01.transform = translate(-7,-3,0) * scale(4, 4, 4);// * rotate(0,1,0, -1);
    gInstances.push_back(crusader01);
    imperio.push_back(crusader01);

    ModelInstance crusader02;
    crusader02.asset = &this->modelos[0];
    crusader02.transform = translate(25,-3,0) * scale(4, 4, 4) * rotate(0,1,0, 0.9);
    gInstances.push_back(crusader02);
    imperio.push_back(crusader02);

    ModelInstance crusader03;
    crusader03.asset = &this->modelos[0];
    crusader03.transform = translate(10,20,0) * scale(4, 4, 4) * rotate(0,1,0, 0.5);
    gInstances.push_back(crusader03);
    imperio.push_back(crusader03);

    ModelInstance rebel_cursader01;
    rebel_cursader01.asset = &this->modelos[1];
    rebel_cursader01.transform =  translate(10,0,35) * scale(2.0, 2.0, 2.0) * rotate(0,1,0, 3.1415) ;
    gInstances.push_back(rebel_cursader01);
    rebeldes.push_back(rebel_cursader01);

    ModelInstance rebel_cursader02;
    rebel_cursader02.asset = &this->modelos[1];
    rebel_cursader02.transform =  translate(20,-5,45) * scale(2.0, 2.0, 2.0) * rotate(0,1,0, 3.1415) ;
    gInstances.push_back(rebel_cursader02);
    rebeldes.push_back(rebel_cursader02);

    ModelInstance rebel_cursader03;
    rebel_cursader03.asset = &this->modelos[1];
    rebel_cursader03.transform =  translate(-10,-5,45) * scale(2.0, 2.0, 2.0) * rotate(0,1,0, 3.1415) ;
    gInstances.push_back(rebel_cursader03);
    rebeldes.push_back(rebel_cursader03);

    ModelInstance tie0; //== ANIMAÇÃO
    tie0.asset = &this->modelos[2];
    tie0.transform =  translate(-70,0,0) * scale(1.5, 1.5, 1.5);
    imp.push_back(tie0);

    ModelInstance tie00; //== ANIMAÇÃO
    tie00.asset = &this->modelos[2];
    tie00.transform =  translate(-70,0,0) * scale(1.5, 1.5, 1.5);
    imp.push_back(tie00);

    ModelInstance tie000; //== ANIMAÇÃO
    tie000.asset = &this->modelos[2];
    tie000.transform =  translate(-70,0,0) * scale(1.5, 1.5, 1.5);
    imp.push_back(tie000);

    ModelInstance tie0000; //== ANIMAÇÃO
    tie0000.asset = &this->modelos[2];
    tie0000.transform =  translate(-70,0,0) * scale(1.5, 1.5, 1.5);
    imp.push_back(tie0000);

    ModelInstance tie01;
    tie01.asset = &this->modelos[2];
    tie01.transform =  translate(0,-2,0) * scale(1.5, 1.5, 1.5);
    gInstances.push_back(tie01);
    imperio.push_back(tie01);

    ModelInstance tie02;
    tie02.asset = &this->modelos[2];
    tie02.transform =  translate(5,-2,0) * scale(1.5, 1.5, 1.5);
    gInstances.push_back(tie02);
    imperio.push_back(tie02);

    ModelInstance tie03;
    tie03.asset = &this->modelos[2];
    tie03.transform =  translate(10,-2,0) * scale(1.5, 1.5, 1.5);
    gInstances.push_back(tie03);
    imperio.push_back(tie03);

    ModelInstance tie04;
    tie04.asset = &this->modelos[2];
    tie04.transform =  translate(15,-2,0) * scale(1.5, 1.5, 1.5);
    gInstances.push_back(tie04);
    imperio.push_back(tie04);

    ModelInstance tie05;
    tie05.asset = &this->modelos[2];
    tie05.transform =  translate(2.5,2,0) * scale(1.5, 1.5, 1.5);
    gInstances.push_back(tie05);
    imperio.push_back(tie05);

    ModelInstance tie06;
    tie06.asset = &this->modelos[2];
    tie06.transform =  translate(7.5,2,0) * scale(1.5, 1.5, 1.5);
    gInstances.push_back(tie06);
    imperio.push_back(tie06);

    ModelInstance tie07;
    tie07.asset = &this->modelos[2];
    tie07.transform =  translate(12.5,2,0) * scale(1.0, 1.0, 1.0);
    gInstances.push_back(tie07);
    imperio.push_back(tie07);

    ModelInstance xWing0; //== ANIMAÇÃO
    xWing0.asset = &this->modelos[3];
    xWing0.transform =  translate(5,-6,35) * scale(0.8, 0.8, 0.8);
    reb.push_back(xWing0);

    ModelInstance xWing00; //== ANIMAÇÃO
    xWing00.asset = &this->modelos[3];
    xWing00.transform =  translate(5,-6,35) * scale(0.8, 0.8, 0.8);
    reb.push_back(xWing00);

    ModelInstance xWing000; //== ANIMAÇÃO
    xWing000.asset = &this->modelos[3];
    xWing000.transform =  translate(5,-6,35) * scale(0.8, 0.8, 0.8);
    reb.push_back(xWing000);

    ModelInstance xWing0000; //== ANIMAÇÃO
    xWing0000.asset = &this->modelos[3];
    xWing0000.transform =  translate(5,-6,35) * scale(0.8, 0.8, 0.8);
    reb.push_back(xWing0000);

    ModelInstance xWing01;
    xWing01.asset = &this->modelos[3];
    xWing01.transform =  translate(5,-6,35) * scale(0.8, 0.8, 0.8);
    gInstances.push_back(xWing01);
    rebeldes.push_back(xWing01);

    ModelInstance xWing02;
    xWing02.asset = &this->modelos[3];
    xWing02.transform =  translate(9,-10,35) * scale(0.8, 0.8, 0.8);
    gInstances.push_back(xWing02);
    rebeldes.push_back(xWing02);

    ModelInstance xWing03;
    xWing03.asset = &this->modelos[3];
    xWing03.transform =  translate(5,-14,35) * scale(0.8, 0.8, 0.8);
    gInstances.push_back(xWing03);
    rebeldes.push_back(xWing03);

    ModelInstance xWing04;
    xWing04.asset = &this->modelos[3];
    xWing04.transform =  translate(13,-6,35) * scale(0.8, 0.8, 0.8);
    gInstances.push_back(xWing04);
    rebeldes.push_back(xWing04);

    ModelInstance xWing05;
    xWing05.asset = &this->modelos[3];
    xWing05.transform =  translate(17,-10,35) * scale(0.8, 0.8, 0.8);
    gInstances.push_back(xWing05);
    rebeldes.push_back(xWing05);

    ModelInstance xWing06;
    xWing06.asset = &this->modelos[3];
    xWing06.transform =  translate(13,-14,35) * scale(0.8, 0.8, 0.8);
    gInstances.push_back(xWing06);
    rebeldes.push_back(xWing06);

    ModelInstance executor;
    executor.asset = &this->modelos[5];
    executor.transform =  translate(0,10,-12) * scale(4.5, 4.5, 4.5) * rotate(0,1,0, 1.6) ;
    gInstances.push_back(executor);
    imperio.push_back(executor);

    ModelInstance frigate01;
    frigate01.asset = &this->modelos[6];
    frigate01.transform =  translate(30,5,60) * scale(9.0, 9.0, 9.0) * rotate(0,1,0, 135);
    gInstances.push_back(frigate01);
    rebeldes.push_back(frigate01);

    ModelInstance frigate02;
    frigate02.asset = &this->modelos[6];
    frigate02.transform =  translate(0,-5,63) * scale(9.0, 9.0, 9.0) * rotate(0,1,0, 135);
    gInstances.push_back(frigate02);
    rebeldes.push_back(frigate02);    

    ModelInstance falcon;
    falcon.asset = &this->modelos[11];
    falcon.transform =  translate(20,15, 50) * scale(0.5, 0.5, 0.5) * rotate(0,1,0, 135);
    gInstances.push_back(falcon);
    rebeldes.push_back(falcon);

    vader.asset = &this->modelos[13];
    vader.transform =  translate(gCamera.position().x, gCamera.position().y - 1.5, gCamera.position().z - 6) * scale(2.5, 2.5, 2.5) * rotate(0,1,0, M_PI);
}

void GLWidget::CalculaLaser()
{
    int esc = rand()%15 + 1;

    for( int val=1; val<=esc; val++ )
    {
        glm::vec3 delta, posReb, posEmp;

        int fonte = rand()%2;
        if( fonte == 0 )
        {
            int pos = rand()%imperio.size();
            posEmp = {imperio[pos].transform[3][0], imperio[pos].transform[3][1], imperio[pos].transform[3][2]};
            pos = rand()%rebeldes.size();
            posReb = {rebeldes[pos].transform[3][0], rebeldes[pos].transform[3][1], rebeldes[pos].transform[3][2]};

            delta.x = posReb.x - posEmp.x;
            delta.y = posReb.y - posEmp.y;
            delta.z = posReb.z - posEmp.z;


        }
        else
        {
            int pos = rand()%rebeldes.size();
            posReb = {rebeldes[pos].transform[3][0], rebeldes[pos].transform[3][1], rebeldes[pos].transform[3][2]};
            pos = rand()%imperio.size();
            posEmp = {imperio[pos].transform[3][0], imperio[pos].transform[3][1], imperio[pos].transform[3][2]};

            delta.x = posEmp.x - posReb.x ;
            delta.y = posEmp.y - posReb.y;
            delta.z = posEmp.z - posReb.z;
        }

        glm::vec3 pos = {0.0, 1.0, 0.0};

        delta = glm::normalize(delta);
        float dot = glm::dot(delta, pos);
        float ang = glm::acos(dot);


        pos = {1,0,0};
        dot = glm::dot(delta, pos);
        float ang2 = glm::acos(dot);

        int ajusteX;
        int ajusteY;

        if(fonte == 1)
        {
            ajusteY = -1;
            ajusteX = 1;
        }
        else
        {
            ajusteY = -1;
            ajusteX = -1;
        }



        ModelInstance laser;
        if( fonte == 0 )
        {
            laser.asset = &this->modelos[9];
            laser.transform =  translate(posEmp.x, posEmp.y, posEmp.z)* rotate(0,ajusteX,0, ang2) * rotate(0,0,ajusteY, ang) * scale(0.4, 4.0, 0.4) ;
        }
        else
        {
            laser.asset = &this->modelos[10];
            laser.transform =  translate(posReb.x, posReb.y, posReb.z)* rotate(0,ajusteX,0, ang2) * rotate(0,0,ajusteY, ang) * scale(0.4, 4.0, 0.4) ;
        }

        Raio r;
        r.laser = laser;
        r.delta = ( glm::vec3(delta.x*2.0, delta.y*2.0, delta.z*2.0) );
        if( fonte == 0 )
        {
            r.chegada = posReb;
        }
        else
        {
            r.chegada = posEmp;
        }

        lasers.push_back(r);
    }

///NAVES PEQUENAS


    esc = rand()%8 + 1;
    for( int val=1; val<=esc; val++ )
    {
        glm::vec3 delta, posReb, posEmp;

        int qual = rand() % imp.size();
        int count = 0;

        ModelInstance imp, reb;

        std::list<ModelInstance>::iterator it;
        for(it = this->imp.begin(); it != this->imp.end(); ++it)
        {
            if(qual == count)
            {
                imp = (*it);
                break;
            }
            count ++;
        }
        count =0;
        for(it = this->reb.begin(); it != this->reb.end(); ++it)
        {
            if(qual == count)
            {
                reb = (*it);
                break;
            }
            count++;
        }

        double t = 10.0;
        posEmp = {reb.transform[3][0] + t*(imp.transform[3][0] - reb.transform[3][0])
                , reb.transform[3][1] + t*(imp.transform[3][1] - reb.transform[3][1])
                , reb.transform[3][2] + t*(imp.transform[3][2] - reb.transform[3][2]) };


        posReb = {reb.transform[3][0], reb.transform[3][1], reb.transform[3][2]};

        delta.x = posEmp.x - posReb.x;
        delta.y = posEmp.y - posReb.y;
        delta.z = posEmp.z - posReb.z;


        glm::vec3 pos = {0.0, 1.0, 0.0};

        delta = glm::normalize(delta);
        float dot = glm::dot(delta, pos);
        float ang = glm::acos(dot);

        int ajusteZ = 1.0;

        if( glm::cross(pos, delta).z < 0 )
        {
            //cout << "NEG____" << endl;
            ajusteZ = -1;
        }


        pos = {1,0,0};
        dot = glm::dot(delta, pos);
        float ang2 = glm::acos(dot);

        int ajusteX = 1.0;

        if( glm::cross(pos, delta).y < 0.0 )
        {
            ajusteX = -1.0;
            //cout << "NEG " << endl;

            if( glm::cross({0,1,0}, delta).z > 0.0 )
            {
                ajusteZ = -1.0;
            }

        }
        else
        {
            //cout << "POS " << endl;

            if( glm::cross({0,1,0}, delta).z > 0.0 )
            {
                ajusteZ = -1.0;
            }

        }



        ModelInstance laser;
        laser.asset = &this->modelos[10];
        laser.transform =  translate(posReb.x, posReb.y, posReb.z)* rotate(0,ajusteX,0, ang2) * rotate(0,0,ajusteZ, ang) * scale(0.4, 4.0, 0.4) ;


        Raio r;
        r.laser = laser;
        r.delta = ( glm::vec3(delta.x*2.3, delta.y*2.3, delta.z*2.3) );
        {
            r.chegada = posEmp;
        }


        lasers.push_back(r);
    }

}

void GLWidget::AtualizaLaser()
{
    std::list<Raio> temp;

    while( lasers.size() > 0 )
    {
        Raio r = lasers.front();

        r.laser.transform = translate(r.delta.x, r.delta.y, r.delta.z) * r.laser.transform;

        if( glm::distance( r.chegada, glm::vec3( r.laser.transform[3][0], r.laser.transform[3][1], r.laser.transform[3][2] ) ) <= 7.0 )
        {
            lasers.pop_front();
            continue;
        }
        temp.push_back( r );
        lasers.pop_front();

    }

    lasers = temp;

    if(lasers.size() <= 12 || rand()%10 < 1 )
    {
        CalculaLaser();
    }

    updateGL();
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    screen_size[0] = width;
    screen_size[1] = height;

    gCamera.setViewportAspectRatio(screen_size.x / screen_size.y);

}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    posX =  event->x();
    posY =  event->y();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    //rotate camera based on mouse movement
    const float mouseSensitivity = 4.0f;
    double mouseX = event->x();
    double mouseY = event->y();

    angY = glm::radians( ( ( (float)mouseY - (float)posY ) ) );
    angX = glm::radians( ( ( (float)mouseX - (float)posX ) ) );

    gCamera.offsetOrientation( mouseSensitivity * angY, mouseSensitivity * angX );

    posX =  mouseX;
    posY =  mouseY;

    updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * event)
{
    //posX =  event->x();
    //posY =  event->y();

}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    const float zoomSensitivity = -0.05f;
    float fieldOfView = gCamera.fieldOfView() + zoomSensitivity * event->delta();
    if(fieldOfView < 5.0f) fieldOfView = 5.0f;
    if(fieldOfView > 130.0f) fieldOfView = 130.0f;
    gCamera.setFieldOfView(fieldOfView);


    updateGL();
}

void GLWidget::keyReleaseEvent(QKeyEvent *keyEvent)
{

}

void GLWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    const float moveSpeed = 1.0; //units per second

    switch(keyEvent->key())
    {
        case Qt::Key_S:
        {
            gCamera.offsetPosition( moveSpeed * -gCamera.forward());
            break;
        }
        case Qt::Key_W:
        {
            gCamera.offsetPosition( moveSpeed * gCamera.forward());
            break;
        }
        case Qt::Key_A:
        {
            gCamera.offsetPosition( moveSpeed * -gCamera.right());
            break;
        }
        case Qt::Key_D:
        {
            gCamera.offsetPosition( moveSpeed * gCamera.right());
            break;
        }
        case Qt::Key_Z:
        {
            gCamera.offsetPosition(moveSpeed * -glm::vec3(0,1,0));
            break;
        }
        case Qt::Key_X:
        {
            gCamera.offsetPosition(moveSpeed * glm::vec3(0,1,0));
            break;
        }

    case Qt::Key_Space:
    {
        if( fix_cam )
            break;

        laser_Sound->play();

        glm::vec3 posVader = {vader.transform[3][0], vader.transform[3][1], vader.transform[3][2]};
        glm::vec3 posFinal = {posVader.x + 30*(gCamera.forward().x)
                            , posVader.y + 30*(gCamera.forward().y)
                            , posVader.z + 30*(gCamera.forward().z) };
        glm::vec3 delta = posFinal - posVader;

        glm::vec3 pos = {0.0, 1.0, 0.0};

        delta = glm::normalize(delta);
        float dot = glm::dot(pos, gCamera.forward());
        float ang = glm::acos(dot);

        ModelInstance laser;
        laser.asset = &this->modelos[9];
        laser.transform =  translate( posVader.x, posVader.y, posVader.z) * rotate( gCamera.right().x, gCamera.right().y, gCamera.right().z, -ang)  * scale(0.4, 4.0, 0.4) ;


        Raio r;
        r.laser = laser;
        r.delta = ( glm::vec3(delta.x*2.3, delta.y*2.3, delta.z*2.3) );
        {
            r.chegada = posFinal;
        }


        lasers.push_back(r);

        break;
    }




        case Qt::Key_1:
        {
            gLights[0].position = glm::vec4(gCamera.position(), 1.0);
            gLights[0].coneDirection = gCamera.forward();
            break;
        }
        case Qt::Key_2:
        {
            gLights[0].intensities = glm::vec3(2,0,0); //red
            break;
        }
        case Qt::Key_3:
        {
            gLights[0].intensities = glm::vec3(0,2,0); //green
            break;
        }
        case Qt::Key_4:
        {
            gLights[0].intensities = glm::vec3(2,2,2); //white
            break;
        }

        case Qt::Key_5:
        {
            fix_cam = !fix_cam;

            if(fix_cam)
                tieFighter_Engine-> stop();
            else
                xWing_Sound-> stop();


            break;
        }

    case Qt::Key_6:
    {
        fix_cam = false;
        xWing_Sound-> stop();

        gCamera.setPosition(glm::vec3(9,20,108));

        gCamera.lookAt(glm::vec3(10,7,0));
        //gCamera.setHorizontalAngle(0);
        //gCamera.setHorizontalAngle(0);

        break;
    }

        case Qt::Key_Escape:
        {
            QApplication::quit();
            break;
        }

    }

    updateGL();
}
